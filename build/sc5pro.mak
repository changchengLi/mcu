APP_ROOT = $(TOP)/SC5PRO
UART_UPGRADER_ROOT = $(TOP)/uart-upgrader
TOOLS = $(TOP)/tools
PACK_ROOT = $(TOOLS)/pack
PACK = $(PACK_ROOT)/pack

$(TARGET): FORCE
	$(Q)rm -rf $(OUTPUT)
	$(Q)mkdir -p $(OUTPUT)
	$(Q)cd $(APP_ROOT) && make clean && make
	$(Q)cd $(UART_UPGRADER_ROOT) && make clean && make
	$(Q)cd $(PACK_ROOT) && make distclean && make
	$(Q)$(PACK) sc5pro-layout.xml $@ $(E) && mv $@ $(OUTPUT)/

clean: FORCE
	$(Q)cd $(APP_ROOT) && make clean
	$(Q)cd $(UART_UPGRADER_ROOT) && make clean
	$(Q)cd $(PACK_ROOT) && make distclean

distclean: clean
	$(Q)rm -rf $(OUTPUT)

burn: FORCE
	st-flash write $(OUTPUT)/$(TARGET) 0x08000000
