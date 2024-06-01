// strfetch 
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

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
char ascii_windows[][16] = {
    "\x1b[0m  ___  ___  ",
    " |   ||   | ",
    " |___||___| ",
    " |___||___\\ ",
    " |   ||   \\\\",
    " |___||___\\\\",
    " |___||___/",
    "            "
};
int windows_i = sizeof(ascii_windows) / sizeof(ascii_windows[0]);
