// strfetch 1.1
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// contains definitions and includes for other headers, required
#include "strfetch.h"

int main(int argc, char **argv) {
	time_t randomiser;
	uname(&kernel);
    // strings
	if (argc < 2) {
		srand((unsigned) time(&randomiser));
		printf("\x1b[31m[!] %s\n", strings[rand() % istrings]);
	} else {
		printf("[!] ");
		int i;
		for( i=1; i<argc; i++ ) {
        	printf("%s ", argv[i]);
		}
		printf("\n");
	}
	// hostname
	printf("\x1b[33m[&] Host: %s\n", kernel.nodename);
	// kernel version
	printf("\x1b[32m[*] Kernel: %s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
	// uptime
	long uptime_seconds = 0;
	if (get_system_uptime(&uptime_seconds)) {
        printf("\x1b[34m[*] Uptime: ");
        format_uptime(uptime_seconds);
    }
	// memory
    printf("\x1b[35m[*] Memory: ");
	get_memory_info();
	// exit
	return 0; 
}