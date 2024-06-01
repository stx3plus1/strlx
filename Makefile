SRC=src
BUILD=build
CC=gcc
CFLAGS=-std=c99 
USERDIR=${HOME}

.PHONY: clean strfetch

strfetch: $(SRC)/strfetch.c $(SRC)/memup.c $(SRC)/random.c
	@echo Compiling...
	@mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$@ $^ $(CFLAGS)
	strip $(BUILD)/$@
	@echo Done!

install: $(BUILD)/strfetch
	@echo Installing...
	@mkdir -p /usr/local/bin
	@cp $< /usr/local/bin/
	@echo Done!

install-config: conf
	@echo Installing configuration file...
	@mkdir -p $(USERDIR)/.config/strfetch
	@cp conf $(USERDIR)/.config/strfetch/
	@echo Done!

clean: 
	rm -rf build/
