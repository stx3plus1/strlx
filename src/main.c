/* 
 * strlx
 * by stx3plus1
 */

#include "include/main.h"

/*
 * This function is... main.
 */

int main(int ac, char **av) {
	// parse arguments.
	for (int i = 1; i < ac; i++) {
	    if (strncmp(av[i], "--", 2) == 0) {
			char* value = av[i] + 2;
			if (strcmp(value, "help") == 0) {
				printf("strlx %s-%s\nby stx3plus1.\n\nusage: %s [string] [--help]\nstrlx is a terminal program for displaying system information.\n", VERSION, commit, av[0]);
	    		return 0;
			} else {
				printf("Ignoring unknown option: %s\n", value);
			}
	    }
	}
	// configuration loading
	char* confpath = concat_strings(getenv("HOME"), "/.config/strlx/");
	// XXX to fix lmao
	FILE* config = generate_open_config("config.json", confpath, conf, conf_len);
	if (config == NULL) {
		printf("Error generating configuration file.\n");
	} else {
		// if a value of colors is -1, it did not load successfully.
		// this means we should use the default.
		long int colors[3] = { -1, -1, -1 };
		char color[24];

		int asc_i = 0;
		char* ascii[ASC_MAX]; // you better not have a huge ascii!
		int asc_sel_i;

		int entered_items;
	
		int random = brand();
		srand(random);

		// equivalent of $(uname -a) but separated
		struct utsname kernel;
		uname(&kernel);

		char* keys[64], *values[64]; // Get some help if your config is 64 lines long.
		char* key, *value;
		int len = parse_json(config, keys, values);
		for (int i = 0; i < len; i++) {
			// set key and value from json
			key = keys[i];
			value = values[i];
			
			// set ascii :>
			if (!strcmp(key, "ascii")) {
				if (!strcmp(value, "tux")) {
					memcpy(ascii, ascii_tux, sizeof(ascii_tux));
					asc_sel_i = tux_i;
				} else if (!strcmp(value, "apple")) {
					memcpy(ascii, ascii_apple, sizeof(ascii_apple));
					asc_sel_i = apple_i;
				} else if (!strcmp(value, "auto")) {
					// distros to come throughout 3.0 maybe?
					memcpy(ascii, ascii_tux, sizeof(ascii_tux));
					asc_sel_i = tux_i;
				}
			}

			if (!strcmp(key, "color")) {
				// set color for stats
				char seg[3];
				long int decimal;
				char* endptr;

				if (strlen(value) < 6) continue;

				// skip # if user has added one
				if (*value == '#') value++;

				// convert string into long ints then store in the array
				for (int i = 0; i < 12 && value[i] != '\0'; i += 2) {
					strncpy(seg, value + i, 2);
					seg[2] = '\0';
					decimal = strtol(seg, &endptr, 16);
					colors[i / 2] = decimal;
				}
				sprintf(color, "\e[0;1;38;2;%ld;%ld;%ldm", colors[0], colors[1], colors[2]);
			}

			if (!strcmp(value, "array")) {	
				if (!strcmp(key, "items")) entered_items = 1;
				// please don't use nested arrays in your config. why.
				if (!strcmp(key, "end") && entered_items) entered_items = 0;
			}
			
			if (!strcmp(key, "inf") && entered_items) {
				if (asc_sel_i != 0) {
					if (asc_i < asc_sel_i) {
						printf("%s", ascii[asc_i++]);
					} else {
						printf("%s", ascii[0]);
					}
				}

				if (colors[0] != -1) printf("%s", color);
				if (!strcmp(value, "syst")) {
					struct passwd *p = getpwuid(getuid());
					printf("\e[0;1;4m%s@%s\n\e[0m", p->pw_name, kernel.nodename);
				} else if (!strcmp(value, "dist")) {
					printf("System: \e[0m");
					char* distro;
					FILE* osrelease = fopen("/etc/os-release", "r");
					if (!osrelease) {
						printf("%s\n", kernel.sysname);
					} else {
						char osline[256];
						while (fgets(osline, 128, osrelease)) {
							if (strstr(osline, "PRETTY_NAME")) {
								distro = strtok(osline, "\"");
								distro = strtok(NULL, "\"");
								printf("%s\n", distro);
								fclose(osrelease);
								break;
							}
						}
					}
				} else if (!strcmp(value, "shll")) {
					char* shell = strrchr(getenv("SHELL"), '/');
					shell++;
					printf("Shell: \e[0m%s\n", shell);
				} else if (!strcmp(value, "krnl")) {
					printf("Kernel: \e[0m%s - version %s on %s\n", kernel.sysname, kernel.release, kernel.machine);
				} else if (!strcmp(value, "proc")) {
					char* cpuinfo;
					long int cores = sysconf(_SC_NPROCESSORS_ONLN);
					printf("CPU: \e[0m");
					int found;
					FILE* prccpuinfo = fopen("/proc/cpuinfo", "r");
					if (!prccpuinfo) {
						printf("%ld cores\n", cores);
						continue;
					}
					char cpuline[256];
					char* cpuinf;
					while(fgets(cpuline, 255, prccpuinfo)) {
						if (strstr(cpuline, "model name")) {
							found++;
							cpuinf = strtok(cpuline, ":");
							cpuinf = strtok(NULL, ":");
							cpuinf++;
							cpuinf[strlen(cpuinf)-1] = '\0';
							break;
						}
					}
					if (found != 1) {
						printf("%ld cores\n", cores);
						fclose(prccpuinfo);
					} else {
						printf("%s, %ld cores\n", cpuinf, cores);
						fclose(prccpuinfo);
					}
				} else if (!strcmp(value, "gpro")) {
					// someone help me with this :sob:
					printf("GPU: \e[0mNot implemented.\n");
				} else if (!strcmp(value, "uptm")) {
					printf("Uptime: \e[0m");
					FILE *file = fopen("/proc/uptime", "r");
    				if (file == NULL) {
						printf("\n");
						continue;
					}
					double uptime;
    				if (fscanf(file, "%lf", &uptime) != 1) {
        				fclose(file);
						printf("\n");
						continue;
    				}
    				fclose(file);
    				long uptime_seconds = (long)uptime;

    				int days = uptime_seconds / (60 * 60 * 24);
    				int hours = (uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    				int minutes = (uptime_seconds % (60 * 60)) / 60;
    				if (days > 0) printf("%dd ", days);
    				if (hours > 0) printf("%dh ", hours);
					printf("%dm\n", minutes);
				} else if (!strcmp(value, "memr")) {
					printf("Memory: \e[0m");
					FILE* meminfo = fopen("/proc/meminfo", "r");
					if (!meminfo) {
						printf("\n");
						continue;
					}
					char line[64];
					char* totstr = "MemTotal:";
					char* availstr = "MemAvailable:";
					long total = -1, avail = -1;
					while (fgets(line, sizeof(line), meminfo)) {
						if (!strncmp(line, totstr, strlen(totstr))) {
							sscanf(line, "MemTotal: %ld kB", &total);
						}
						if (!strncmp(line, availstr, strlen(availstr))) {
							sscanf(line, "MemAvailable: %ld kB", &avail);
						}

					}
					printf("%.2f GiB / %.2f GiB\n", (total - avail)/1048576.0, total/1048576.0);
					fclose(meminfo);
				}
			} else if (!strcmp(key, "mis")) {
				if (asc_sel_i != 0) {
					if (asc_i < asc_sel_i) {
						printf("%s", ascii[asc_i++]);
					} else {
						printf("%s", ascii[0]);
					}
				}
			} else if (!strcmp(key, "str")) {
				if (asc_i < asc_sel_i) {
					printf("%s", ascii[asc_i++]);
				} else {
					printf("%s", ascii[0]);
				}
				// string
				if (ac > 1) {
					for (int i = 1; i < ac; i++) printf("%s ", av[i]);
					printf("\n");
				} else if ((fseek(stdin, 0, SEEK_END), ftell(stdin)) > 0) {
					rewind(stdin);
					char buf[256];
  					(void)read(0, buf, 256);
					printf("%s", buf);
				} else {
					if (!strcmp(value, "silly")) {
						printf("\"%s\"\n", strings[rand() % istrings]);
					} else if (!strcmp(value, "info-jokes")) {
						printf("%s\n", informationalstrings[rand() % iinfstrings]);
					} else {
						printf("invalid selected string type\n");
					}
				} 
			} else if (!strcmp(key, "pri")) {
				if (asc_sel_i != 0) {
					if (asc_i < asc_sel_i) {
						printf("%s", ascii[asc_i++]);
					} else {
						printf("%s", ascii[0]);
					}
				}

				printf("\e[1m%s\n", value);
			}
			// Free from the malloc in parse_json()
			free(keys[i]);
			free(values[i]);
		}
 	}
	printf("\x1b[0m");
	if (config) fclose(config); 
	if (confpath) free(confpath);
	return 0;
}
