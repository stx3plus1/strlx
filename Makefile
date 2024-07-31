SRC=src
BUILD=build
CC=cc
CFLAGS=-std=c99 
USERDIR=${HOME}

.PHONY: clean prog

prog: $(SRC)/main.c $(SRC)/memup.c $(SRC)/random.c
	@echo Compiling...
	@mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$@ $^ $(CFLAGS)
	strip $(BUILD)/$@
	@echo Done!

install: $(BUILD)/strlx
	@echo Installing...
	@mkdir -p /usr/local/bin
	@cp $< /usr/local/bin/
	@echo Done!

install-config: conf
	@echo Installing configuration file...
	@mkdir -p $(USERDIR)/.config/strlx
	@cp conf $(USERDIR)/.config/strlx/
	@echo Done!

clean: 
	rm -rf build/
