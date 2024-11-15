// strlx 
// by stx3plus1
#define VERSION "3.0"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fnc.h"
#include "json.h"
#include "string.h"
#include "strings.h"
#if defined(__linux__) || defined(__GNU__)
    #define LINUX
#elif defined(__APPLE__)
	#include <CoreFoundation/CoreFoundation.h>
	#include <IOKit/IOKitLib.h>
    #include <sys/sysctl.h>
	#include <mach/mach.h>
    #define MACOS
#elif defined(__FreeBSD__)
	#include <sys/types.h>
	#include <sys/sysctl.h>
	#define FREEBSD
#endif

char* conf[] = {
	"{",
	"    \"ascii\": \"tux\",",
	"    \"color\": \"#fc6712\",",
	"    \"items\": [",
	"        \"inf\": \"syst\",",
	"        \"mis\": \"separator\",",
	"        \"pri\": \"Operating System\",",
	"        \"inf\": \"dist\",",
	"        \"inf\": \"krnl\",",
	"        \"inf\": \"shll\",",
	"        \"mis\": \"separator\",",
	"        \"pri\": \"Hardware\",",
	"        \"inf\": \"proc\",",
	"        \"inf\": \"gpro\",",
	"        \"inf\": \"uptm\",",
	"        \"inf\": \"memr\",",
	"        \"mis\": \"separator\",",
	"        \"str\": \"silly\"",
	"    ]",
	"}"
};
int conf_len = sizeof(conf) / sizeof(conf[0]);

char* ascii_tux[] = {
	"\e[0m          ",
	"\e[1;30m   .-.    \e[0m",
	"\e[0m   oo\e[1;30m|    \e[0m",
	"\e[1;37m  /`'\\    \e[0m",
	"\e[1;33m (\\\e[1;30m_;\e[1;33m/)   \e[0m"
};

char* ascii_bsd[] = {
	"\e[0m          ",
	"\e[1;30m   .-.    \e[0m",
	"\e[0m   oo\e[1;30m|    \e[0m",
	"\e[1;37m  /`'\\    \e[0m",
	"\e[1;33m (\\\e[1;30m_;\e[1;33m/)   \e[0m"
};

/*char* ascii_apple[] = {
	"\e[0m          ",
	"\e[38;5;034m     .    \e[0m",
	"\e[38;5;226m    ..    \e[0m",
	"\e[38;5;208m........  \e[0m",
	"\e[38;5;196m.......   \e[0m",
	"\e[38;5;129m........  \e[0m",
	"\e[38;5;038m ......   \e[0m"
};*/

char* ascii_apple[] = {
"\e[0m                      ",
"\e[0m             &&       ",
"\e[0m            &&&       ",
"\e[0m           &&         ",
"\e[0m     &&&&&   &&&&&    ",
"\e[0m  &&&&&&&&&&&&&&&&&&  ",
"\e[0m &&&&&&&&&&&&&&&&&    ",
"\e[0m &&&&&&&&&&&&&&&&&    ",
"\e[0m &&&&&&&&&&&&&&&&&    ",
"\e[0m &&&&&&&&&&&&&&&&&&   ",
"\e[0m  &&&&&&&&&&&&&&&&&&& ",
"\e[0m   &&&&&&&&&&&&&&&&&  ",
"\e[0m    &&&&&&&&&&&&&&&   ",
"\e[0m     &&&&&& &&&&&&    ",
};

int tux_i = sizeof(ascii_tux) / sizeof(ascii_tux[0]);
int bsd_i = sizeof(ascii_bsd) / sizeof(ascii_bsd[0]);
int apple_i = sizeof(ascii_apple) / sizeof(ascii_apple[0]);
