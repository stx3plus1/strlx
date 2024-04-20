// strfetch 0.3 by cirkul

// a fetch made in neovim 
// i added some comments to understand
// i should have written this in bash, shouldnt i

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	char strings[20][40] = {
		"i wonder what this button does",
		"the world will end one day",
		"time for your psu to blow up",
		"del System32",
		"systemd isnt bloatware",
		"i will delete init rn",
		"whats that behind you",
		"mark zuck is the lizard man",
		"your pc has a cpu",
		"you shouldnt rm -rf /",
		"i could like memleak rn",
		"dude feed me",
		"ubuntu makes pcs faster, canonical:",
		"one red",
		"ssh wiimote.local",
		"i run in 0.04 seconds",
		"Segmentation Fault",
		"is your pc case a cardboard box",
		"pour water on me, im thirsty",
		"*** Stop. ***"
	};

	time_t randomiser;
	
	if (argc < 2) {
		srand((unsigned) time(&randomiser));
		printf("[!] %s\n[&] Host: ", strings[rand() % 20]);
	} else {
		printf("[!] %s\n[&] Host: ", argv[1]);
	}

	fflush(stdout);
	system("uname -n"); 

	printf("[*] Kernel: ");
	fflush(stdout);
	system("uname -rm");
	
	printf("[*] Uptime: ");
	fflush(stdout);
	system("uptime -p | cut -c 4-");

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
