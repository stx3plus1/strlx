// strfetch 1.2
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// contains definitions and includes for other headers, required
#include "strfetch.h"

int main(int argc, char **argv) {
	time_t randomiser;
	uname(&kernel);

	// color on/off
	COLS = fopen(strcat(getenv("HOME"), "/.config/strfetch/conf"), "r");

	if (!COLS) {
	    color = 0;
	} else {
	    while(fscanf(COLS, "%s", word) != EOF) { 
	        if(strcmp(word, "true") == 0) { 
	            color = 1;
	        } 
	    } 
 	}
 // strings
	if (argc < 2) {
		srand((unsigned) time(&randomiser));
		if (color == 1) {
		  printf("\x1b[31m");
		}
		printf("[!] %s\n", strings[rand() % istrings]);
	 } else {
		  printf("[!] ");
		  int i = 1;
		  for ( i < argc; i++; ) {
      printf("%s ", argv[i]);
		  }
		printf("\n");
	 }
	// hostname
	if (color == 1) {
	    printf("\x1b[33m");
	}
	printf("[&] Host: %s\n", kernel.nodename);
	// kernel version
	if (color == 1) {
	  printf("\x1b[32m");
	} 
	printf("[*] Kernel: %s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
	// uptime
	long uptime_seconds = 0;
	if (color == 1) {
   printf("\x1b[34m");
	}
	if (get_system_uptime(&uptime_seconds)) {
   printf("[*] Uptime: ");
   format_uptime(uptime_seconds);
 }
	// memory
	if (color == 1) {
	  printf("\x1b[35m");
	}
 printf("[*] Memory: ");
 get_memory_info();
 // exit
 printf("\x1b[0m"); // 1.1 broke people's shells.
	if (color == 1) {
	    fclose(COLS);
	}
	return 0; 
}