// basics
struct passwd *p = getpwuid(getuid());
printf("%s@%s\n", p->pw_name, kernel.nodename);
// string
if (ac < 2) {
	int rand = returnrand(0, istrings);
	printf("%s\n", strings[rand]);
} else {
	int i = 0;
	while (i < (ac - 1)) {
		i++;
		printf("%s ", av[i]);
	}
	printf("\n");
}
// distro
if(strstr(word, "distro")) {
	char* distro;
	printf("OS: \x1b[0m");
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
// hostname
printf("Host: \x1b[0m%s\n", kernel.nodename);
// kernel
printf("Kernel: \x1b[0m%s %s %s\n", kernel.sysname, kernel.release, kernel.machine);
// shell
printf("Shell: \x1b[0m%s\n", getenv("SHELL"));
// cpu
char* cpuinfo;
long int cores = sysconf(_SC_NPROCESSORS_ONLN);
#ifdef LINUX
int found;
FILE* prccpuinfo = fopen("/proc/cpuinfo", "r");
if (!prccpuinfo) {
	printf("CPU: \x1b[0m(%ld)\n", cores);
	goto cont2;
}
char cpuline[256];
char* cpuinf;
while(fgets(cpuline, 255, prccpuinfo)) {
	if (strstr(cpuline, "model name")) {
		found = 1;
		cpuinf = strtok(cpuline, ":");
		cpuinf = strtok(NULL, ":");
		cpuinf++;
		cpuinf[strlen(cpuinf)-1] = '\0';
		break;
	}
}
if (set != 1) {
	printf("CPU: \x1b[0m(%ld)\n", cores);
	fclose(prccpuinfo);
} else {
	printf("CPU: \x1b[0m%s (%ld)\n", cpuinf, cores);
	fclose(prccpuinfo);
}
#elif defined(MACOS)
char cpuin[256];
size_t cpuini = 256;
sysctlbyname("machdep.cpu.brand_string", &cpuin, &cpuini, NULL, 0);
printf("CPU: \x1b[0m%s (%ld)\n", cpuin, cores);
#endif
// uptime
long uptime_seconds = 0;
printf("Uptime: \x1b[0m");
if (get_system_uptime(&uptime_seconds) == 0) format_uptime(uptime_seconds) else printf("\n");
// memory
printf("Memory: \x1b[0m");
get_memory_info();
// reset
printf("\x1b[0m");

