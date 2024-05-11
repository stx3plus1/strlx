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
// these functions would be inside main but they are called multiple times, hence printf is embedded.
void os() {
	printf("[*] OS:     ");
	osrelease = fopen("/etc/os-release", "r");
	if (!osrelease) {
		printf("%s %s OS\n", kernel.sysname, kernel.release);
		return; 
	}
	while (fgets(osline, 128, osrelease)) {
		if (strstr(osline, "PRETTY_NAME")) {
			char* distro = strtok(osline, "\"");
			distro = strtok(NULL, "\"");
			printf("%s\n", distro);
			return; 
		}
	}
}
void hostname() {
	printf("[*] Host:   %s\n", kernel.nodename);
}
void kernel_ver() {
	printf("[*] Kernel: %s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
}
void shell() {
	printf("[*] Shell:  %s\n", getenv("SHELL"));
}
void cores() {
	long int cores = sysconf(_SC_NPROCESSORS_ONLN);
	printf("[*] Cores:  %ld\n", cores);
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
			printf("usage: strfetch [your string here]\nstrfetch is a simple yet silly C fetch application for getting system stats.\nExtremely silly...");
			pstrings(argc, 1, argv);
			return 0;
		}
	}
	uname(&kernel);
	CONFIG = fopen(strcat(getenv("HOME"), "/.config/strfetch/conf"), "r");	
	if (!CONFIG) {
		pstrings(argc, 0, argv);
		os();
		hostname();
		shell();
		kernel_ver();
		cores();
		uptime();
		memory();
		return 0;
	} else {
		int ascline = 0;
		while(fscanf(CONFIG, "%s", word) != EOF) { 
			if (strstr(word, "inf")) {
				ascline++;
				if (ascline >= ascii_ln) {
						#ifdef LINUX
						printf("%s", ascii_tux[0]);	
						#elif defined (MACOS)
						printf("%s", ascii_apple[0]);	
						#endif
				} else {
					#ifdef LINUX
					printf("\x1b[0m%s", ascii_tux[ascline]);
					#elif defined (MACOS)
					printf("\x1b[0m%s", ascii_apple[ascline]);
					#endif
				}
			}
			if (strstr(word, "color-")) {
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
				if (strstr(word, "dr")) {
					printf("\x1b[38;5;9m");
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
			if(strstr(word, "bold")) {
				printf("\x1b[1m");
			}
			if(strstr(word, "string")) { 
				pstrings(argc, 0, argv);
			}
			if(strstr(word, "distro")) {
				os();
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
			if(strstr(word, "cores")) {
				cores();
			}
			if(strstr(word, "uptime")) { 
				uptime();
			}
			if(strstr(word, "memory")) { 
				memory();
			}
			if(strstr(word, "reset")) {
				printf("\x1b[0m");
			}
		} 
 	} 
	printf("\x1b[0m"); 
	if (CONFIG) {
		fclose(CONFIG);
	}
	return 0;
}
