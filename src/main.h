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
char ascii_tux[][16] = {
	"\x1b[0m        ",
	"  .-.   ",
	"  oo|   ",
	" /`'\\   ",
	"(\\_;/)  "
};
int tux_i = sizeof(ascii_tux) / sizeof(ascii_tux[0]);
char ascii_apple[][16] = {
	"\x1b[0m          ",
	"     .    ",
	"    /|    ",
	"/######/  ",
	"######<   ",
	"\\######\\  ",
	" \\#####/  "
};
int apple_i = sizeof(ascii_apple) / sizeof(ascii_apple[0]);