SRC=src
BUILD=build
CC=gcc
# i love these flags
CFLAGS=-std=c99 -Ofast -momit-leaf-frame-pointer -fomit-frame-pointer -funroll-loops
USERDIR=${HOME}

strfetch: $(SRC)/strfetch.c $(SRC)/func.c
	@echo Compiling...
	@mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$@ $^ $(CFLAGS)
	@strip $(BUILD)/$@
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
