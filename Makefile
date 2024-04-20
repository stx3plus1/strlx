SRC=src
BUILD=build
CC=gcc

strfetch: $(SRC)/strfetch.c
	mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$@ $< 
	strip $(BUILD)/$@

install: $(BUILD)/strfetch
	mkdir -p /usr/local/bin
	cp $< /usr/local/bin/ 

clean: 
	rm -rf build/