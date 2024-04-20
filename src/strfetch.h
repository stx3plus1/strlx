// version
#define VERSION "1.01"

// built in headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>

#ifdef __linux__
	#include <sys/stat.h>
	#include <fcntl.h>
    #define LINUX
#elif defined(__APPLE__)
    #include <sys/sysctl.h>
	#include <mach/mach.h>
    #define MACOS
#endif

// uname
struct utsname kernel;

// strings
#define istrings 20
char strings[istrings][40] = {
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
	"i run in 3ms",
	"Segmentation Fault",
	"is your pc case a cardboard box",
	"pour water on me, im thirsty",
	"*** Stop. ***"
};