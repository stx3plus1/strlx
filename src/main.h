// strlx 
// by stx3plus1
#define VERSION "2.0"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include "memup.h"
#include "strings.h"
#if defined(__linux__) || defined(__GNU__)
    #define LINUX
#elif defined(__APPLE__)
    #include <sys/sysctl.h>
    #define MACOS
#endif
int conf_len = 13;
char conf[13][64] = {
	"default config for strlx",
	"ascii-tux",
	"inf bold basics",
	"reset",
	"inf string",
	"inf dr distro",
	"inf red hostname",
	"inf yellow shell",
	"inf green kernel",
	"inf cyan cpu",
	"inf blue uptime",
	"inf purple memory"
};
char ascii_tux[][32] = {
	"\x1b[0m        ",
	"\x1b[1;30m  .-.   \x1b[0m]",
	"  oo|   ",
	"\x1b[30m /`'\\   \x1b[0m",
	"\x1b[1;33m(\\_;/)  \x1b[0m"
};
int tux_i = sizeof(ascii_tux) / sizeof(ascii_tux[0]);
char ascii_apple[][32] = {
	"\x1b[0m          ",
	"\033[38;5;034m     .    \x1b[0m",
	"\033[38;5;226m    ..    \x1b[0m",
	"\033[38;5;208m........  \x1b[0m",
	"\033[38;5;196m.......   \x1b[0m",
	"\033[38;5;129m........  \x1b[0m",
	"\033[38;5;038m ......   \x1b[0m"
};
int apple_i = sizeof(ascii_apple) / sizeof(ascii_apple[0]);