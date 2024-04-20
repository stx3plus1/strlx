SRC=src
BUILD=build
CC=gcc

.PHONY: clean

strfetch: $(SRC)/strfetch.c
	mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$@ $< 
	strip $(BUILD)/$@

clean: 
	rm -rf build/