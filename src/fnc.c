/*
 * strlx
 * by stx3plus1
 */ 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifdef __linux__
	#include <sys/stat.h>
	#include <fcntl.h>
#elif defined(__APPLE__)
	#include <sys/sysctl.h>
	#include <mach/mach.h>
#elif defined(__FreeBSD__)
	#include <sys/types.h>
	#include <sys/sysctl.h>
#endif

/*
 * Get raw system uptime information.
 * *uptime_seconds: Pointer to uptime `long` defined in main.
 * RETURNS: failure or success
 */

bool get_system_uptime(long *uptime_seconds) {
#if defined(__linux__) || defined(__GNU__)
    FILE *file = fopen("/proc/uptime", "r");
    if (file == NULL) return false;
    double uptime;
    if (fscanf(file, "%lf", &uptime) != 1) {
        fclose(file);
        return false;
    }
    fclose(file);
    *uptime_seconds = (long)uptime;
    return true;
#elif defined(__APPLE__) 
    int mib[2];
    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;
    struct timeval boottime;
    size_t length = sizeof(boottime);
    if (sysctl(mib, 2, &boottime, &length, NULL, 0) < 0) return false;
    struct timeval now;
    gettimeofday(&now, NULL);
    *uptime_seconds = now.tv_sec - boottime.tv_sec;
    return true;
#elif defined(__FreeBSD__)
	uint64_t out;
	size_t len = sizeof(out);
	sysctlbyname("kern.boottime", &out, &len, NULL, 0);
	printf("%lu - ", out);
	return false;
#else
    return false;
#endif
}

void format_uptime(long uptime_seconds) {
    int days = uptime_seconds / (60 * 60 * 24);
    int hours = (uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int minutes = (uptime_seconds % (60 * 60)) / 60;
    if (days > 0) printf("%dd ", days);
    if (hours > 0) printf("%dh ", hours);
	printf("%dm\n", minutes);
}
void get_memory_info() {    
#ifdef __APPLE__

	// TODO TO FUCKING DO: add working apple memory code idk

#elif defined(__linux__) || defined(__GNU__)
    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
		printf("Memory calculation error (ERROR 0xHMM)\n");
        return;
    }
    char line[256];
    int total_memory = 0;
    int free_memory = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line + 9, "%d", &total_memory);
        } else if (strncmp(line, "MemAvailable:", 8) == 0) {
            sscanf(line + 13, "%d", &free_memory);
        } 
    }
    fclose(file);
    if ((double)total_memory / 1048576 > 1) {
        printf("%.2fGiB / %.2fGiB\n", (double)(total_memory - free_memory) / 1048576, (double)total_memory / 1048576);
    } else {
        printf("%.2fMiB / %.2fMiB\n", (double)(total_memory - free_memory) / 1024, (double)total_memory / 1024);
    }
#elif defined(__FreeBSD__)
	printf("FreeBSD eta s0n\n");
#else
    printf("OS unsupported!\n");
#endif
}
