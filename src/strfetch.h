// strfetch 
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// version
#define VERSION "1.4"

// built in headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>

#if defined(__linux__)|| defined(__GNU__)
    #define LINUX
#elif defined(__APPLE__)
    #include <sys/sysctl.h>
    #define MACOS
#endif

// strfetch info functions
#include "func.h"

// configuration file
int i;
FILE* CONFIG;
int color = 0;
char word[32];

// os
FILE* osrelease;
char osline[256];

// uname
struct utsname kernel;

// strings
#define istrings 20
// istrings = number of strings in the array
char strings[istrings][128] = {
	"i wonder what this button does",
	"the world will end one day",
	"time for your psu to blow up",
	"del System32",
	"systemd isnt bloatware",
	"i will delete init rn",
	"whats that behind you",
	"mark zuck is the lizard man",
	"your pc has a cpu",
	"you shouldnt rm -rf /",
	"i could like memleak rn",
	"dude feed me",
	"ubuntu makes pcs faster, canonical:",
	"liblzma, xz 5.6.0 and 5.6.1",
	"ssh wiimote.local",
    "dd if=/dev/zero of=/dev/sda",
	"Segmentation Fault",
	"is your pc case a cardboard box",
	"pour water on me, im thirsty",
	"make: *** No rule to make target `src/func.c', needed by `strfetch'. Stop."
};