#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <adc.h>
#include <system.h>
#include <tick.h>
#include <project.h>
#include <mp5475.h>
#include <isl68224.h>
#include <dbgi2c.h>
#include <chip.h>
#include <timer.h>
#include <common.h>

#ifndef __maybe_unused
#define __maybe_unused __attribute__((unused))
#endif

// #define FILTER_DISABLE

#define MCU_SW_VER	0

#define BROADCAST_INTERVAL	100
#define COLLECT_INTERVAL	10

#define FILTER_DEPTH_SHIFT	6
#define FILTER_DEPTH		(1 << FILTER_DEPTH_SHIFT)
#define FILTER_DEPTH_MASK	(FILTER_DEPTH - 1)

struct filter {
	unsigned short data[FILTER_DEPTH];
	unsigned long total;
	unsigned long value;
	int p;
};

static unsigned long filter_init(struct filter *f, unsigned long d)
{
	int i;

	f->p = 0;
	f->total = 0;
	for (i = 0; i < FILTER_DEPTH; ++i) {
		f->data[i] = d;
		f->total += d;
	}
	return d;
}

static unsigned long filter_in(struct filter *f, unsigned long d)
{
	f->total -= f->data[f->p];
	f->total += d;
	f->data[f->p] = d;
	f->p = (f->p + 1) & FILTER_DEPTH_MASK;
	f->value = f->total >> FILTER_DEPTH_SHIFT;

#ifdef FILTER_DISABLE
	return d;
#else
	return f->value;
#endif
}

static unsigned long last_time_broadcast;
static unsigned long last_time_collect;
static int mon_verbose_mode;
static struct filter i12v;
static struct filter mp5475_current[4][4];
static struct filter mp5475_voltage[4][4];
static struct filter isl68224_current[4][3];
static struct filter isl68224_voltage[4][3];
static struct filter isl68224_power[4][3];

static struct {
	uint8_t id;
	uint8_t type;
	uint8_t sw_ver;
	uint8_t hw_ver;
	uint32_t i12v;

	struct {
		struct {
			uint32_t voltage;
			uint32_t current;
		} buck[4];
	} mp5475[4];

	struct {
		struct {
			uint32_t voltage;
			uint32_t current;
			uint32_t power;
		} rail[3];
	} isl68224[4];
} __attribute__((packed)) __attribute__((aligned(4))) pkg;

static struct dbgi2c_info __attribute__((aligned(4))) dbgi2c_pkg;

void mon_init(void)
{
	int i, j;

	filter_init(&i12v, 0);

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			filter_init(&(mp5475_current[i][j]), 0);
			filter_init(&(mp5475_voltage[i][j]), 0);
		}
	}

	pkg.type = SC5PRO;
	pkg.sw_ver = MCU_SW_VER;
	pkg.hw_ver = adc_get_hw_ver();

	dbgi2c_pkg.tag = 0xdeadbeef;
	dbgi2c_pkg.type = pkg.type;
	dbgi2c_pkg.sw_ver = pkg.sw_ver;
	dbgi2c_pkg.hw_ver = pkg.hw_ver;

	last_time_collect = last_time_broadcast = tick_get();
}

static void __maybe_unused
collect_mp5475(void)
{
	int i, j;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {

			pkg.mp5475[i].buck[j].current =
				filter_in(&(mp5475_current[i][j]),
					  mp5475_output_current(i, j));

			pkg.mp5475[i].buck[j].voltage =
				filter_in(&(mp5475_voltage[i][j]),
					  mp5475_output_voltage(i, j));
		}
	}
}

static void __maybe_unused
collect_isl68224(void)
{
	int i, j;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 3; ++j) {

			pkg.isl68224[i].rail[j].current =
				filter_in(&(isl68224_current[i][j]),
					  isl68224_output_current(i, j));

			pkg.isl68224[i].rail[j].voltage =
				filter_in(&(isl68224_voltage[i][j]),
					  isl68224_output_voltage(i, j));

			pkg.isl68224[i].rail[j].power =
				filter_in(&(isl68224_power[i][j]),
					  isl68224_output_power(i, j));
		}
	}
}

static void __maybe_unused
collect_tpu(void)
{
	int i, j;

	j = 0;

	for (i = 0; i < 4; ++i) {
		pkg.isl68224[i].rail[j].current =
			filter_in(&(isl68224_current[i][j]),
				  isl68224_output_current(i, j));

		pkg.isl68224[i].rail[j].voltage =
			filter_in(&(isl68224_voltage[i][j]),
				  isl68224_output_voltage(i, j));

		pkg.isl68224[i].rail[j].power =
			filter_in(&(isl68224_power[i][j]),
				  isl68224_output_power(i, j));
	}
}

static void collect(void)
{
	/* get 12v current from adc */
	pkg.i12v = filter_in(&i12v, adc_read_i12v());

	if (mon_verbose_mode) {
		collect_mp5475();
		collect_isl68224();
	} else {
		collect_tpu();
	}

	++pkg.id;
}

static inline void mon_putc(int c)
{
	if (c == '\n')
		usart_send_blocking(MON_UART, '\r');
	usart_send_blocking(MON_UART, c);
}

int mon_printf(const char *fmt, ...)
{
	va_list ap;
	char p[128];
	int len;

	va_start(ap, fmt);
	len = vsnprintf(p, sizeof(p), fmt, ap);
	va_end(ap);

	char *q;

	for (q = p; *q; ++q)
		mon_putc(*q);

	return len;
}

static void mon_put_normal(void)
{
	int i;

	mon_printf("software version %u\n", pkg.sw_ver);
	mon_printf("hardware version %u\n", pkg.hw_ver);
	mon_printf("12v current(mA): %lu\n", pkg.i12v);

	mon_printf("tpu information\n");
	mon_printf("%12s %12s %12s\n",
		   "voltage(mV)", "current(mA)", "power(mW)");
	for (i = 0; i < 4; ++i) {
		mon_printf("%12lu %12lu %12lu\n",
			   pkg.isl68224[i].rail[0].voltage,
			   pkg.isl68224[i].rail[0].current,
			   pkg.isl68224[i].rail[0].power);
	}
}

static void mon_put_verbose(void)
{
	int i, j;

	mon_printf("id: %u\n", pkg.id);
	mon_printf("type: %u\n", pkg.type);
	mon_printf("software version %u\n", pkg.sw_ver);
	mon_printf("hardware version %u\n", pkg.hw_ver);

	mon_printf("12v current(mA): %lu\n", pkg.i12v);

	mon_printf("{\n");
	for (i = 0; i < 4; ++i) {
		mon_printf("\tmp5475%d:\n", i);
		for (j = 0; j < 4; ++j) {
			mon_printf("\t\tbuck%d ", j);
			mon_printf("%lu (mV) %lu (mA)\n",
			       pkg.mp5475[i].buck[j].voltage,
			       pkg.mp5475[i].buck[j].current);
		}
	}
	mon_printf("}\n");

	mon_printf("{\n");
	for (i = 0; i < 4; ++i) {
		mon_printf("\tisl68224%d:\n", i);
		for (j = 0; j < 3; ++j) {
			mon_printf("\t\trail%d ", j);
			mon_printf("%lu (mV) %lu (mA) %lu (mW)\n",
			       pkg.isl68224[i].rail[j].voltage,
			       pkg.isl68224[i].rail[j].current,
			       pkg.isl68224[i].rail[j].power);
		}
	}
	mon_printf("}\n");
}

void mon_put_text(void)
{
	if (mon_verbose_mode)
		mon_put_verbose();
	else
		mon_put_normal();
}

static void __maybe_unused broadcast(void)
{
	int isl68224_idx, isl68224_rail;

	static int soc_idx;

	/* broadcast to one soc per-timer */
	/* broadcast to all soc contigurous may cause soc hangup */

	if (!chip_is_enabled()) {
		soc_idx = 0;
		return;
	}

	isl68224_rail = 0;
	isl68224_idx = soc_idx / 2;

	dbgi2c_pkg.id = pkg.id;
	dbgi2c_pkg.i12v = pkg.i12v;
	dbgi2c_pkg.tpu.voltage =
		pkg.isl68224[isl68224_idx].rail[isl68224_rail].voltage;
	dbgi2c_pkg.tpu.current =
		pkg.isl68224[isl68224_idx].rail[isl68224_rail].current;
	dbgi2c_pkg.tpu.power =
		pkg.isl68224[isl68224_idx].rail[isl68224_rail].power;

	dbgi2c_broadcast(soc_idx, &dbgi2c_pkg);

	soc_idx = (soc_idx + 1) & 0x07;
}

void mon_set_verbose(int verbose)
{
	mon_verbose_mode = verbose;
}

int mon_get_verbose(void)
{
	return mon_verbose_mode;
}

void mon_process(void)
{
	unsigned long current_time;

	current_time = tick_get();

	if (current_time - last_time_collect > COLLECT_INTERVAL) {
		collect();
		last_time_collect = current_time;
	}

	if (current_time - last_time_broadcast > BROADCAST_INTERVAL) {
		broadcast();
		last_time_broadcast = current_time;
	}
}
