#ifdef LINUX
#define ascii_ln 5
char ascii_tux[ascii_ln][16] = {
	"       ",
	"  .-.  ",
	"  oo|  ",
	" /`'\\  ",
	"(\\_;/) "
};
#endif
#ifdef MACOS
#define ascii_ln 7
char ascii_apple[ascii_ln][16] = {
	"         ",
	"     .   ",
	"    /|   ",
	"/######/ ",
	"######<  ",
	"\\######\\ ",
	" \\#####/ "
};
#endif