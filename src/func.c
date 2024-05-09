// strfetch 
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%

// headers we don't have due to separate files
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
#endif

// uptime
bool get_system_uptime(long *uptime_seconds) {
#if defined(__linux__) || defined(__GNU__)
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
#elif defined(__APPLE__)
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

// uptime printing
void format_uptime(long uptime_seconds) {
    int days = uptime_seconds / (60 * 60 * 24);
    int hours = (uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int minutes = (uptime_seconds % (60 * 60)) / 60;
    if (days > 0) {
		printf("%dd ", days);
    }
    if (hours > 0) {
		printf("%dh ", hours);
    }
	printf("%dm\n", minutes);
}

// memory
void get_memory_info() {    
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
        return;
    }
    natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
    int64_t free_memory = physical_memory - mem_used;
    if ((double)physical_memory / (1024 * 1024) > 1) {
        printf("%.2fGiB / %.2fGiB\n", (double)mem_used / 1073741824, (double)physical_memory / 1073741824);
    } else {
        printf("%.2fMiB / %.2fMiB\n", (double)mem_used / 1048576, (double)physical_memory / 1048576);
    }
    #elif defined(__linux__) || defined(__GNU__)
    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
		printf("Memory calculation error");
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
    #else
    printf("Unsupported\n");
    #endif
}