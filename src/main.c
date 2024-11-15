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
	FILE* config = generate_open_config("config.json", confpath, conf, conf_len);
	if (config == NULL) {
		printf("Error generating configuration file.\n");
	} else {
		// if a value of colors is -1, it did not load successfully.
		// this means we should use the default.
		long int colors[3] = { -1, -1, -1 };
		char color[24];
		int asc_i = 0;
		char* ascii[16]; // you better not have a huge ascii!
		int asc_sel_i;
		
		// rand() needs a seed
		int buf[2];
		int ufd = open("/dev/", O_RDONLY);
		read(ufd, buf, 2);
		int random = buf[0] + buf[1];
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
				} else if (!strcmp(value, "freebsd")) {
					memcpy(ascii, ascii_bsd, sizeof(ascii_bsd));
					asc_sel_i = 3;
				}
			}

			if (!strcmp(key, "color")) {
				// set color for stats
				char seg[3];
				long int decimal;
				char* endptr;

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

			if (!strcmp(key, "inf")) {
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
					#if defined(LINUX) || defined(__FreeBSD__)
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
					#elif defined(MACOS)
					// Yea I don't fucking get this either alright?
					CFStringRef path = CFSTR("/System/Library/CoreServices/SystemVersion.plist");
    				CFURLRef url = CFURLCreateWithFileSystemPath(NULL, path, kCFURLPOSIXPathStyle, false);
    				CFDataRef resourceData;
    				SInt32 err;
    				CFURLCreateDataAndPropertiesFromResource(NULL, url, &resourceData, NULL, NULL, NULL);
    				CFPropertyListRef plist = CFPropertyListCreateWithData(NULL, resourceData, kCFPropertyListImmutable, NULL, NULL);
    				CFRelease(resourceData);
    				CFRelease(url);
   					if (CFGetTypeID(plist) == CFDictionaryGetTypeID()) {
        				CFDictionaryRef dict = (CFDictionaryRef)plist;
        				CFStringRef productName = CFDictionaryGetValue(dict, CFSTR("ProductName"));
        				CFStringRef productVersion = CFDictionaryGetValue(dict, CFSTR("ProductVersion"));
        				if (productName && productVersion) {
            				char name[256];
            				char version[256];
            				CFStringGetCString(productName, name, sizeof(name), kCFStringEncodingUTF8);
            				CFStringGetCString(productVersion, version, sizeof(version), kCFStringEncodingUTF8);
            				printf("%s %s\n", name, version);
        				}
					}
    				CFRelease(plist);
					#endif
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
					#ifdef LINUX
					int found;
					FILE* prccpuinfo = fopen("/proc/cpuinfo", "r");
					if (!prccpuinfo) {
						printf("%ld cores\n", cores);
						goto cont2;
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
					if (set != 1) {
						printf("%ld cores\n", cores);
						fclose(prccpuinfo);
					} else {
						printf("%s, %ld cores\n", cpuinf, cores);
						fclose(prccpuinfo);
					}
					#elif defined(MACOS)
					char cpuin[256];
					size_t cpuini = 256;
					sysctlbyname("machdep.cpu.brand_string", &cpuin, &cpuini, NULL, 0);
					printf("%s, %ld cores\n", cpuin, cores);
					#elif defined(FREEBSD)
					printf("bruh. (%ld cores)\n", cores);
					#endif
				} else if (!strcmp(value, "gpro")) {
					printf("GPU: \e[0m");
					#ifdef LINUX
					#elif defined(MACOS)
					CFMutableDictionaryRef matchingDict = IOServiceMatching("IOPCIDevice");
    				io_iterator_t iter;
    				IOServiceGetMatchingServices(kIOMainPortDefault, matchingDict, &iter);
    				io_object_t service;
    				while ((service = IOIteratorNext(iter)) != 0) {
        				CFTypeRef model = IORegistryEntryCreateCFProperty(service, CFSTR("model"), kCFAllocatorDefault, 0);
       					if (model) {
            				const unsigned char *model_str = CFDataGetBytePtr((CFDataRef)model);
            				printf("%s\n", model_str);
            				CFRelease(model);
            				IOObjectRelease(service);
            				break; 
        				}
        				IOObjectRelease(service);
    				}
    				IOObjectRelease(iter);
					#elif defined(FREEBSD)
					printf("\n");
					#endif
				} else if (!strcmp(value, "uptm")) {
					long uptime_seconds = 0;
					printf("Uptime: \e[0m");
					if (get_system_uptime(&uptime_seconds)) {
						format_uptime(uptime_seconds);
					} else { 
						printf("Failure getting uptime info.\n"); 
					}
				} else if (!strcmp(value, "memr")) {
					printf("Memory: \e[0m");
					#ifdef LINUX
					// Not implemented :P
					// TODO Add Linux memory, CPU, GPU
					#elif defined(MACOS)
					uint64_t total_memory;
					size_t len = sizeof(total_memory);
					sysctlbyname("hw.memsize", &total_memory, &len, NULL, 0);

					mach_port_t host_port;
  					mach_msg_type_number_t host_size;
  					vm_size_t pagesize;
  					host_port = mach_host_self();
  					host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
  					host_page_size(host_port, &pagesize);
  					vm_statistics64_data_t vmstat;

					host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vmstat, &host_size);
					uint64_t used_memory = (
						+ vmstat.active_count
        				+ vmstat.inactive_count
        				+ vmstat.speculative_count
        				+ vmstat.wire_count
        				+ vmstat.compressor_page_count
       					- vmstat.purgeable_count
        				- vmstat.external_page_count * pagesize);
					printf("%.2llu MiB / %.2llu MiB\n", used_memory / 1024, total_memory / (1024 * 1024));
					#elif defined(FREEBSD)
					// TODO Add FreeBSD memory, CPU, GPU, uptime
					printf("\n");
					#endif
				}
			} else if (!strcmp(key, "mis")) {
				if (asc_sel_i != 0) {
					if (asc_i < asc_sel_i) {
						printf("%s", ascii[asc_i++]);
					} else {
						printf("%s", ascii[0]);
					}
				}
				// misc
				if (!strcmp(value, "separator")) {
					printf("\e[0m= = = = = = = = = = = = =\n");
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
  					read(0, buf, 256);
					printf("%s", buf);
				} else {
					if (!strcmp(value, "silly")) {
						printf("\"%s\"\n", strings[rand() % istrings]);
					} else if (!strcmp(value, "info-jokes")) {
						printf("%s\n", informationalstrings[rand() % iinfstrings]);
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
	return 0;
}
