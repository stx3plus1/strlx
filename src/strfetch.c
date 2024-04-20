// strfetch 1.01
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// contains definitions and includes for other headers, required
#include "strfetch.h"
//uptime 
bool get_system_uptime(long *uptime_seconds) {
#ifdef LINUX
    FILE *file = fopen("/proc/uptime", "r");
    if (file == NULL)
        return false;
    double uptime;
    if (fscanf(file, "%lf", &uptime) != 1) {
        fclose(file);
        return false;
    }
    fclose(file);
    *uptime_seconds = (long)uptime;
    return true;
#elif defined(MACOS)
    int mib[2];
    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;
    struct timeval boottime;
    size_t length = sizeof(boottime);
    if (sysctl(mib, 2, &boottime, &length, NULL, 0) < 0)
        return false;
    struct timeval now;
    gettimeofday(&now, NULL);
    *uptime_seconds = now.tv_sec - boottime.tv_sec;
    return true;
#else
    return false;
#endif
}
void format_uptime(long uptime_seconds) {
    int days = uptime_seconds / (60 * 60 * 24);
    int hours = (uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int minutes = (uptime_seconds % (60 * 60)) / 60;
    printf("[*] Uptime: ");
    if (days > 0) {
		printf("%dd ", days);
    }
    if (hours > 0) {
		printf("%dh ", hours);
    }
	printf("%dm\n", minutes);
}
int main(int argc, char **argv) {
	// random strings
	time_t randomiser;
	// get info for some strings
	uname(&kernel);
	if (argc < 2) {
		srand((unsigned) time(&randomiser));
		printf("[!] %s\n", strings[rand() % istrings]);
	} else {
		printf("[!] ");
		int i;
		for( i=1; i<argc; i++ ) {
        	printf("%s ", argv[i]);
		}
		printf("\n");
	}
	// hostname
	printf("[&] Host: %s\n", kernel.nodename);
	// kernel version
	printf("[*] Kernel: %s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
	// uptime
	long uptime_seconds = 0;
	if (get_system_uptime(&uptime_seconds)) {
        format_uptime(uptime_seconds);
    }
	// memory
	#ifdef __APPLE__
    int mib[2];
    int64_t physical_memory;
    size_t len = sizeof(physical_memory);
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    sysctl(mib, 2, &physical_memory, &len, NULL, 0);
    mach_port_t host_port;
    mach_msg_type_number_t host_size;
    vm_size_t pagesize;
    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);
    vm_statistics_data_t vm_stat;
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) {
		printf("Memory calculation error");
        return 1;
    }
    natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
    int64_t free_memory = physical_memory - mem_used;
    printf("[*] Memory: %.2fMB / %.2fMB\n", (double)mem_used / (1024 * 1024), (double)physical_memory / (1024 * 1024));
    #elif defined(__linux__)
    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
		printf("Memory calculation error");
        return 1;
    }
    char line[256];
    int total_memory = 0;
    int free_memory = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line + 9, "%d", &total_memory);
        } else if (strncmp(line, "MemFree:", 8) == 0) {
            sscanf(line + 8, "%d", &free_memory);
        }
    }
    fclose(file);
    printf("[*] Memory: %.2fMB / %.2fMB\n", (double)(total_memory - free_memory) / 1024, (double)total_memory / 1024);
    #else
    printf("Unsupported");
    #endif
	// exit
	return 0; 
}