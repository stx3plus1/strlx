# strlx
# by stx3plus1

SRC=src
CC=cc
SOURCE=$(wildcard $(SRC)/*.c)
COMMIT="\"$(shell git rev-parse HEAD | head -c6)\""
CFLAGS=-w -O3 -std=c2x -Dcommit=$(COMMIT) 

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    CFLAGS += -framework CoreFoundation -framework IOKit
endif

.PHONY: strlx

strlx: ${SOURCE}
	@echo "[$(CC)] $^ -> $@"
	@$(CC) -o $@ $^ $(CFLAGS)
	@strip $@

# run install with sudo/doas.
install: strlx
ifeq ($(UNAME), $(filter $(UNAME) Darwin,FreeBSD))
	@echo "[in] $< -> /usr/local/bin/$<"
	@mkdir -p /usr/local/bin
	@cp $< /usr/local/bin/
else
	@echo "[in] $< -> /usr/bin/$<"
	@cp $< /usr/bin
endif

clean: 
	@rm -f strlx
