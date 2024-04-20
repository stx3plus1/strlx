// strfetch 0.3 by cirkul
// you may distribute and modify this code provided you give credit
// i worked hard on this 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "strfetch.h"

int main(int argc, char **argv) {
	time_t randomiser;
	
	char hostname[128];
	hostname[127] = '\0';
        gethostname(hostname, 127);

	if (argc < 2) {
		srand((unsigned) time(&randomiser));
		printf("[!] %s\n[&] Host: %s\n", strings[rand() % 20], hostname);
	} else {
		printf("[!] %s\n[&] Host: %s\n", argv[1], hostname);
	}

	printf("[*] Kernel: ");
	fflush(stdout);
	system("uname -rm");
	
	printf("[*] Uptime: ");
	fflush(stdout);
	system("uptime | cut -c 11- | cut -c -7");

	printf("[*] Memory: "); 
	fflush(stdout);
	#ifdef __linux__
		system("echo $(free -m | awk '/^Mem:/{printf(\"%.0fMB\",$3)}'; echo \" /\"; free -m | awk '/^Mem:/{printf(\"%.0fMB\",$2)}')");
        #else
		system("echo Unknown, support for this OS may come sometime!");
		return 1;
	#endif
	return 0; 
}
