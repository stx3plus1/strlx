// version
#define VERSION "1.0"

// built in headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/utsname.h>

#ifdef __linux__
	#include <time.h>
    #define LINUX
#elif defined(__APPLE__)
	#include <sys/types.h>
    #include <sys/sysctl.h>
    #define MACOS
#endif

// uname
struct utsname kernel;

// strings
char strings[20][40] = {
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
	"i run in 0.04 seconds",
	"Segmentation Fault",
	"is your pc case a cardboard box",
	"pour water on me, im thirsty",
	"*** Stop. ***"
};