// a fetch made in neovim 
// i added some comments to understand
// i should have written this in bash, shouldnt i

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// get arguments, this is basic c
int main(int argc, char **argv) {
	// default messages!
	char strings[15][100] = {
		"i wonder what this button does",
		"the world will end sometime",
		"im gay",
		"del System32",
		"systemd is bloatware",
		"i will delete init rn",
		"whats that behind you",
		"IM PICKLE RICK", // the worst one
		"your pc has a cpu",
		"you shouldnt rm -rf /",
		"i could like memleak rn",
		"hungry for your pcs resources",
		"systemd/linux",
		"one red",
		"wiimote.local" // the best one
	};
	
	printf(">host: ");
	fflush(stdout);
	system("uname -n");

	// be random.
	time_t randomiser;
	
	// did we get a custom message?
	if (argc < 2) {
		// no, use a default
		srand((unsigned) time(&randomiser));
		printf("[!] %s\n[*] Kernel: ", strings[rand() % 15]);
	} else {
		// yes, print it out instead.
		printf("[!] %s\n[*] Kernel: ", argv[1]);
	}
	fflush(stdout); // we want it to print the string before - printf wont flush!
	system("uname -srm"); // kernel info
	printf("[*] Memory: "); 
	fflush(stdout); // flush again, god i hate c
	#ifdef __linux__
		system("echo $(free -m | awk '/^Mem:/{printf(\"%.0fMB\",$3)}'; echo /; free -m | awk '/^Mem:/{printf(\"%.0fMB\",$2)}')");
	#elif __APPLE__ 
		system("echo $(echo $(( $(sysctl hw.memsize | cut -d ':' -f2 | awk '{$1=$1};1') / 1024 / 1024)); echo MB total)");
	#endif
	return 0; 
}
