#ifndef __TMP451_H__
#define __TMP451_H__

void tmp451_init(struct i2c01_slave_ctx *i2c_slave_ctx);
void tmp451_get_temp(int *board, int *soc);

#endif /* DS1307_H_ */
