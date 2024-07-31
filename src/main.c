// strlx
// by cirkulx also known as stx3plus1 or stx4

// contains definitions and includes for other headers, required
#include "main.h"

void basics() {
	struct passwd *p = getpwuid(getuid());
	printf("%s@%s\n", p->pw_name, kernel.nodename);
}

void pstrings(int count, int type, char **value) {
	int rand = returnrandomnumber(0, istrings);
	if (type == 1) {
		printf("...%s\n", strings[rand]);
	} else {
		if (count < 2) {
			printf("%s\n", strings[rand]);
		} else {
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
	printf("OS: \x1b[0m");
	// correct bedrock linux release info
	bedrockrelease = fopen("/bedrock/etc/bedrock-release", "r");
	if (bedrockrelease) {
		char distro[64];
		fgets(distro, 63, bedrockrelease);
		printf("%s", distro);
		return;
	}
	osrelease = fopen("/etc/os-release", "r");
	if (!osrelease) {
		sysname = kernel.sysname;
		printf("%s\n", sysname);
		return; 
	}
	while (fgets(osline, 128, osrelease)) {
		if (strstr(osline, "PRETTY_NAME")) {
			distro = strtok(osline, "\"");
			distro = strtok(NULL, "\"");
			printf("%s\n", distro);
			return; 
		}
	}
}
void hostname() {
	printf("Host: \x1b[0m%s\n", kernel.nodename);
}
void kernel_ver() {
	printf("Kernel: \x1b[0m%s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
}
void shell() {
	printf("Shell: \x1b[0m%s\n", getenv("SHELL"));
}     
void cpu() {
	cores = sysconf(_SC_NPROCESSORS_ONLN);
	#ifdef LINUX
	int set = 0;
	cpuinfo = fopen("/proc/cpuinfo", "r");
	if (!cpuinfo) {
		printf("CPU: \x1b[0m%(ld)\n", cores);
		return;
	}
	while(fgets(cpuline, 255, cpuinfo)) {
		if (strstr(cpuline, "model name")) {
			set = 1;
			cpuinf = strtok(cpuline, ":");
			cpuinf = strtok(NULL, ":");
			cpuinf++;
			cpuinf[strlen(cpuinf)-1] = '\0';
			break;
		}
	}
	if (set == 0) {
		printf("CPU: \x1b[0m(%ld)\n", cores);
		return;
	}
	printf("CPU: \x1b[0m%s (%ld)\n", cpuinf, cores);
	#elif defined(MACOS)
	char cpuin[256];
	size_t cpuini = 256;
    sysctlbyname("machdep.cpu.brand_string", &cpuin, &cpuini, NULL, 0);
	printf("CPU: \x1b[0m%s (%ld)\n", cpuin, cores);
	#endif
}
void uptime() {
	long uptime_seconds = 0;
	printf("Uptime: \x1b[0m");
	if (get_system_uptime(&uptime_seconds)) {
   		format_uptime(uptime_seconds); 
 	} else {
		printf("\n");
	}
}
void memory() {
 	printf("Memory: \x1b[0m");
 	get_memory_info();
}

int main(int argc, char **argv) {
	if (argc > 1) {
		if (strcmp(argv[1], "--version") == 0) {
			printf("strlx %s\nBy cirkulx.\n", VERSION);
			return 0;
		}
		if (strstr(argv[1], "-u") || strstr(argv[1], "--help") || strstr(argv[1], "--usage")) {
			printf("usage: %s [your string here]\nstrlx is a simple yet silly C fetch application for getting system stats.\nExtremely silly...", argv[0]);
			pstrings(argc, 1, argv);
			return 0;
		}
	}
	uname(&kernel);
	CONFIG = fopen(strcat(getenv("HOME"), "/.config/strlx/conf"), "r");	
	if (!CONFIG) {
		basics();
		pstrings(argc, 0, argv);
		os();
		hostname();
		shell();
		kernel_ver();
		cpu();
		uptime();
		memory();
		return 0;
	} else {
		while(fscanf(CONFIG, "%s", word) != EOF) { 
			if (strstr(word, "ascii-tux")) {
				ascii_i = tux_i;
				asctype = 0;
			} else if (strstr(word, "ascii-apple")) {
				ascii_i = apple_i;
				asctype = 1;
			} else {
				if (!asctype) {
					ascii_i = tux_i;
					asctype = 0;
				}
			}
			if (strstr(word, "inf")) {
				ascline++;
				if (ascline >= ascii_i) {
						if (asctype == 0) {
							printf("%s", ascii_tux[0]);	
						} else if (asctype == 1) {
							printf("%s", ascii_apple[0]);	
						} else {
							printf("%s", ascii_tux[0]);	
						}
				} else {
					if (asctype == 0) {
						printf("\x1b[0m%s", ascii_tux[ascline]);
					} else if (asctype == 1) {
						printf("\x1b[0m%s", ascii_apple[ascline]);
					} else {
						printf("\x1b[0m%s", ascii_tux[ascline]);
					}
				}
			}
			if (strstr(word, "color-true")) {
				color = 1;
			}
			if (strstr(word, "color-false")) {
				color = 0;
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
			if(strstr(word, "basics")) {
				basics();
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
			if(strstr(word, "cpu")) {
				cpu();
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
	if (ascline < ascii_i) {
		while (ascline < ascii_i - 1) {
			ascline++;
			if (asctype == 0) {
				printf("\x1b[0m%s", ascii_tux[ascline]);
			} else if (asctype == 1) {
				printf("\x1b[0m%s", ascii_apple[ascline]);
			} else {
				printf("\x1b[0m%s", ascii_tux[ascline]);
			}
			printf("\n");
		}
	}
	printf("\x1b[0m"); 
	if (CONFIG) {
		fclose(CONFIG);
	}
	return 0;
}
