SRC=src
BUILD=build
CC=gcc
CFLAGS=-std=c99

strfetch: $(SRC)/strfetch.c $(SRC)/func.c
	mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$@ $^ $(CFLAGS)
	strip $(BUILD)/$@

install: $(BUILD)/strfetch
	@mkdir -p /usr/local/bin
	@cp $< /usr/local/bin/ 

clean: 
	rm -rf build/