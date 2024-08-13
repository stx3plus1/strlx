// strlx
// by stx3plus1

#include "main.h"

int returnrand(int lower, int upper) {
	srand(time(0));
	int number = rand() % (upper - lower + 1) + lower;
	return number;
}
int main(int argc, char **argv) {
	if (argc > 1) {
		if (strcmp(argv[1], "--version") == 0) {
			// if you fork, please don't remove my name. but i can't make you so well...
			printf("strlx %s\nby stx3plus1.\n", VERSION);
			return 0;
		}
		if (strstr(argv[1], "--help")) {
			printf("usage: %s [STRING] \nstrlx is a simple program for getting system stats.\n", argv[0]);
			return 0;
		}
	}
	struct utsname kernel;
	int ascline = 0;
	int asctype = 0;
	int ascii_i;
	uname(&kernel);
	char* HOME = getenv("HOME");
	char HOMEARRAY[64];
	strcpy(HOMEARRAY, HOME);
	char PATH[] = "/.config/strlx/conf";
	char CONFPATH[128];
	sprintf(CONFPATH, "%s%s", HOMEARRAY, PATH);
	FILE* CONFIG = fopen(CONFPATH, "r");	
	if (!CONFIG) {
		system("mkdir -p $HOME/.config/strlx");
		FILE* CONFIGWRT = fopen(CONFPATH, "w");
		if (!CONFIGWRT) {
			printf("strlx could not create a configuration file. Check permissions on your home directory. (ERROR 0x1)\n");
			return 0;
		}
		int write = 0;
		while (write < (conf_len)) {
			fprintf(CONFIGWRT, "%s", conf[write]);
			fprintf(CONFIGWRT, "\n");
			write++;
		}
		fclose(CONFIGWRT);
		printf("strlx has created a configuration file successfully.\n");
		return 0;
	} else {
		char word[32];
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
			if(strstr(word, "bold")) {
				printf("\x1b[1m");
			}
			if(strstr(word, "basics")) {
				struct passwd *p = getpwuid(getuid());
				printf("%s@%s\n", p->pw_name, kernel.nodename);

			}
			if(strstr(word, "string")) { 
				if (argc < 2) {
					int rand = returnrand(0, istrings);
					printf("%s\n", strings[rand]);
				} else {
					int i = 0;
					while (i < (argc - 1)) {
						i++;
						printf("%s ", argv[i]);
					}
					printf("\n");
				}
			}
			if(strstr(word, "distro")) {
				char* distro;
				printf("OS: \x1b[0m");
				FILE* bedrockrelease = fopen("/bedrock/etc/bedrock-release", "r");
				if (bedrockrelease) {
					fgets(distro, 63, bedrockrelease);
					printf("%s", distro);
					fclose(bedrockrelease);
					goto cont;
				}
				FILE* osrelease = fopen("/etc/os-release", "r");
				if (!osrelease) {
					printf("%s\n", kernel.sysname);
					goto cont; 
				}
				char osline[256];
				while (fgets(osline, 128, osrelease)) {
					if (strstr(osline, "PRETTY_NAME")) {
						distro = strtok(osline, "\"");
						distro = strtok(NULL, "\"");
						printf("%s\n", distro);
						fclose(osrelease);
						goto cont; 
					}
				}
			}
			cont:
			if(strstr(word, "hostname")) { 
				printf("Host: \x1b[0m%s\n", kernel.nodename);
			}
			if(strstr(word, "kernel")) { 
				printf("Kernel: \x1b[0m%s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
			}
			if(strstr(word, "shell")) { 
				printf("Shell: \x1b[0m%s\n", getenv("SHELL"));
			}
			if(strstr(word, "cpu")) {
				char* cpuinfo;
				long int cores = sysconf(_SC_NPROCESSORS_ONLN);
				#ifdef LINUX
				int set = 0;
				FILE* prccpuinfo = fopen("/proc/cpuinfo", "r");
				if (!prccpuinfo) {
					printf("CPU: \x1b[0m(%ld)\n", cores);
					goto cont2;
				}
				char cpuline[256];
				char* cpuinf;
				while(fgets(cpuline, 255, prccpuinfo)) {
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
					fclose(prccpuinfo);
					goto cont2;
				}
				printf("CPU: \x1b[0m%s (%ld)\n", cpuinf, cores);
				fclose(prccpuinfo);
				#elif defined(MACOS)
				char cpuin[256];
			 	size_t cpuini = 256;
				sysctlbyname("machdep.cpu.brand_string", &cpuin, &cpuini, NULL, 0);
				printf("CPU: \x1b[0m%s (%ld)\n", cpuin, cores);
				#endif
				goto cont2;
			}
			cont2:
			if(strstr(word, "uptime")) { 
				long uptime_seconds = 0;
				printf("Uptime: \x1b[0m");
				if (get_system_uptime(&uptime_seconds)) {
   					format_uptime(uptime_seconds); 
			 	} else {
					printf("Not long enough :P (ERROR 0xHUH)\n");
				}
			}
			if(strstr(word, "memory")) { 
				 	printf("Memory: \x1b[0m");
 					get_memory_info();
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