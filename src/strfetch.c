// strfetch 1.0 
// by cirkulx also known as stx3plus1 or stx4

// you may distribute and modify this code provided you give credit
// i worked on this, 100%s

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
	// memory (awkward as heck)
	printf("[*] Memory: "); 
	fflush(stdout);
	#ifdef LINUX
		system("echo $(free -m | awk '/^Mem:/{printf(\"%.0fMB\",$3)}'; echo \" /\"; free -m | awk '/^Mem:/{printf(\"%.0fMB\",$2)}')");
    #elif defined (MACOS)
		printf("macOS moment\n");
	#else
		printf("!!! Unknown !!!\n");
	#endif
	// exit
	return 0; 
}