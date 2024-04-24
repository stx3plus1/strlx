// strfetch 1.2
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// contains definitions and includes for other headers, required
#include "strfetch.h"

void pstrings(int count, char **value) {
	if (count < 2) {
		time_t randomiser;
		srand((unsigned) time(&randomiser));
		printf("[!] %s\n", strings[rand() % istrings]);
	 } else {
		printf("[!] ");
		int i = 0;
		while (i < (count - 1)) {
			i++;
			printf("%s ", value[i]);
		}
		printf("\n");
	}
}
void hostname() {
	printf("[&] Host: %s\n", kernel.nodename);
}
void kernel_ver() {
	printf("[*] Kernel: %s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
}
void uptime() {
	long uptime_seconds = 0;
	if (get_system_uptime(&uptime_seconds)) {
   		printf("[*] Uptime: ");
   		format_uptime(uptime_seconds);
 	}
}
void memory() {
 	printf("[*] Memory: ");
 	get_memory_info();
}

int main(int argc, char **argv) {
	uname(&kernel);
	// color on/off
	CONFIG = fopen(strcat(getenv("HOME"), "/.config/strfetch/conf"), "r");	
	if (!CONFIG) {
		system("mktodir -p ~/.config/strfetch/");
	        pstrings(argc, argv);
		hostname();
		kernel_ver();
		uptime();
		memory();
		return(0);
	} else {
	    while(fscanf(CONFIG, "%s", word) != EOF) { 
		if (strcmp(word, "true")) {
		    color = 1;
		}
	        if (color) {
			if (strstr(word, "red")) {
		            printf("\x1b[31m");
			} 
			if (strstr(word, "yellow")) {
		            printf("\x1b[33m");
			} 
			if (strstr(word, "green")) {
    			    printf("\x1b[32m");
			} 
		        if (strstr(word, "blue")) {
			    printf("\x1b[34m");
			} 
			if (strstr(word, "purple")) {
			    printf("\x1b[35m");
			}
		}
			if(strcmp(word, "string") == 0) { 
				pstrings(argc, argv);
			}
			if(strcmp(word, "hostname") == 0) { 
				hostname();
			}
			if(strcmp(word, "kernel") == 0) { 
				kernel_ver();
			}
			if(strcmp(word, "uptime") == 0) { 
				uptime();
			}
			if(strcmp(word, "memory") == 0) { 
				memory();
			}
			if(strcmp(word, "quit") == 0) {
				printf("\x1b[0m"); // 1.1 broke people's shells.
				if (color == 1) {
					fclose(CONFIG);
				}
				return 0;
			}
	    } 
 	}
	printf("Malformed config. Please add \"quit\" to the last line of ~/.config/strfetch/conf!\n");
	return 1; // we should not get here.
}