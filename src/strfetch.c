// strfetch
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// contains definitions and includes for other headers, required
#include "strfetch.h"

void pstrings(int count, int type, char **value) {
	if (type == 1) {
		time_t randomiser;
		srand((unsigned) time(&randomiser));
		printf("...%s\n", strings[rand() % istrings]);
	} else {
		if (count < 2) {
			time_t randomiser;
			srand((unsigned) time(&randomiser));
			printf("[!] %s\n", strings[rand() % istrings]);
		} else {
			printf("[!] ");
			i = 0;
			while (i < (count - 1)) {
				i++;
				printf("%s ", value[i]);
			}
				printf("\n");
		}
	}
}
void hostname() {
	printf("[&] Host: %s\n", kernel.nodename);
}
void kernel_ver() {
	printf("[*] Kernel: %s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
}
void shell() {
	printf("[*] Shell: %s\n", getenv("SHELL"));
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
	if (argc > 1) {
		if (strcmp(argv[1], "--version") == 0) {
			printf("strfetch %s\nBy cirkulx.\n", VERSION);
			return 0;
		}
		if (strstr(argv[1], "-u") || strstr(argv[1], "--help") || strstr(argv[1], "--usage")) {
			printf("usage: strfetch [your string here]\n");
			printf("strfetch is a simple yet silly C fetch application for getting system stats.\n");
			printf("Extrememly silly...\n");
			pstrings(argc, 1, argv);
			return 0;
		}
	}
	uname(&kernel);
	CONFIG = fopen(strcat(getenv("HOME"), "/.config/strfetch/conf"), "r");	
	if (!CONFIG) {
		printf("Could not find or create a config.\n");
		pstrings(argc, 0, argv);
		hostname();
		kernel_ver();
		shell();
		uptime();
		memory();
		return 0;
	} else {
		while(fscanf(CONFIG, "%s", word) != EOF) { 
			if (strstr(word, "color=")) {
				if (strstr(word, "true")) {
					color = 1;
				}
				if (strstr(word, "false")) {
					color = 0;
				}
			}
			if (color == 1) {
				if (strstr(word, "white")) {
					printf("\x1b[37m");
				}
				if (strstr(word, "black")) {
					printf("\x1b[30m");
				}
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
				if (strstr(word, "cyan")) {
					printf("\x1b[36m");
				}
				if (strstr(word, "purple")) {
					printf("\x1b[35m");
				}
			}
			if(strstr(word, "string")) { 
				pstrings(argc, 0, argv);
			}
			if(strstr(word, "hostname")) { 
				hostname();
			}
			if(strstr(word, "kernel")) { 
				kernel_ver(); 
			}
			if(strstr(word, "shell")) { 
				shell(); 
			}
			if(strstr(word, "uptime")) { 
				uptime();
			}
			if(strstr(word, "memory")) { 
				memory();
			}
		} 
 	} 
	printf("\x1b[0m"); 
	if (CONFIG) {
		fclose(CONFIG);
	}
	return 0;
}
