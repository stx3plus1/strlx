SRC=src
CC=cc
CFLAGS=-std=c99 

.PHONY: clean strlx

strlx: $(SRC)/main.c $(SRC)/memup.c
	@echo Compiling...
	$(CC) -o $@ $^ $(CFLAGS)
	strip $@
	@echo Done!

install: strlx
	@echo Installing...
	@mkdir -p /usr/local/bin
	@cp $< /usr/local/bin/
	@echo Done!

clean: 
	rm strlx