/*
 * strlx
 * by stx3plus1
 */

#define VERSION "3.0"

#include <pwd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

#include "rand.h"
#include "json.h"
#include "string.h"

char* conf[] = {
	"{",
	"    \"ascii\": \"auto\",",
	"    \"color\": \"#fc6712\",",
	"    \"items\": [",
	"        \"inf\": \"syst\",",
	"        \"pri\": \"= = = = = = = = = = = = =\",",
	"        \"pri\": \"Operating System\",",
	"        \"inf\": \"dist\",",
	"        \"inf\": \"krnl\",",
	"        \"inf\": \"shll\",",
	"        \"pri\": \"= = = = = = = = = = = = =\",",
	"        \"pri\": \"Hardware\",",
	"        \"inf\": \"proc\",",
	"        \"inf\": \"uptm\",",
	"        \"inf\": \"memr\",",
	"        \"pri\": \"= = = = = = = = = = = = =\",",
	"        \"str\": \"silly\"",
	"    ]",
	"}"
};
int conf_len = sizeof(conf) / sizeof(conf[0]);

char* ascii_tux[] = {
	"\e[0m           ",
	"\e[1;30m    .-.    \e[0m",
	"\e[0m    oo\e[1;30m|    \e[0m",
	"\e[1;37m   /`'\\    \e[0m",
	"\e[1;33m  (\\\e[1;30m_\e[0m;\e[1;33m/)   \e[0m"
};

// ok seriously why
char* ascii_apple[] = {
"\e[0m                      ",
"\e[0m             &&       ",
"\e[0m            &&&       ",
"\e[0m           &&         ",
"\e[0m     &&&&&   &&&&&    ",
"\e[0m  &&&&&&&&&&&&&&&&&&  ",
"\e[0m &&&&&&&&&&&&&&&&&    ",
"\e[0m &&&&&&&&&&&&&&&&&    ",
"\e[0m &&&&&&&&&&&&&&&&&    ",
"\e[0m &&&&&&&&&&&&&&&&&&   ",
"\e[0m  &&&&&&&&&&&&&&&&&&& ",
"\e[0m   &&&&&&&&&&&&&&&&&  ",
"\e[0m    &&&&&&&&&&&&&&&   ",
"\e[0m     &&&&&& &&&&&&    ",
};

#define ASC_MAX 16
int tux_i = sizeof(ascii_tux) / sizeof(ascii_tux[0]);
int apple_i = sizeof(ascii_apple) / sizeof(ascii_apple[0]);

char strings[][128] = {
	"i wonder what this button does",
	"the world will end one day",
	"time for your psu to blow up",
	"i will delete init rn",
	"whats that behind you",
	"your pc has a cpu",
	"you probably shouldnt rm -rf /",
	"i could like memleak rn",
	"dude feed me",
	"ssh wiinetbsd.local",
	"ssh wiimote.local",
	"ssh sensorbar.local",
	"dd if=/dev/zero of=/dev/sda",
	"illegal instruction",
	"is your pc case a cardboard box",
	"pour water on me, im thirsty",
	"your specs kinda suck im not gonna lie",
	"is github down again?",
	"dont tell anyone that 1 + 1 = 3",
	"1 + 1 is not 3 dont listen to the other guy",
	"i will allocate all your ram"
};
int istrings = (sizeof(strings) / sizeof(strings[0]))-1;
char informationalstrings[][300] = {
	"Did you know? Command: ls - List directory contents",
	"Why don't some people trust Linux? Because they can't 'window' shop!",
	"Did you know? Command: cd - Change the shell working directory.",
	"Why do programmers always mix up Christmas and Halloween? Because Oct 31 == Dec 25!",
	"Did you know? Command: pwd - Print the name of the current working directory.",
	"What is the best thing about boolean logic? Even if you're wrong, you're only off by a bit!",
	"Did you know? Command: cp - Copy files and directories.",
	"Why did the programmer go broke? Because he used up all his cache!",
	"Did you know? Command: mv - Move or rename files.",
	"Why did the programmer quit his job? Because he didn't get arrays.",
	"Did you know? Git, a popular version control system, was created by Linus Torvalds, also the creator of Linux.",
	"Why do programmers prefer dark mode? Because light attracts bugs!",
	"Did you know? Command: mkdir - Make directories.",
	"What is a database administrator's favorite music genre? SQL (pronounced sequel).",
	"Why don't programmers like nature? It has too many bugs!",
	"Did you know? Command: rmdir - Remove empty directories.",
	"The first computer mouse was made of wood and had only one button.",
	"Why did the scarecrow win an award? Because he was outstanding in his field.",
	"Did you know? The Linux kernel is written in C.",
	"What do you call a lazy kangaroo? A pouch potato.",
	"Linux can run on a wide range of devices, from supercomputers to single-board computers like Raspberry Pi.",
	"Why did the computer scientist get fired? Because he used up all the allocation space.",
	"Did you know? The mascot of the Linux kernel is a penguin named Tux.",
	"The internet was originally developed by the US Department of Defense during the Cold War.",
	"Did you know? Many popular applications like Firefox and LibreOffice are open-source.",
	"The first computer bug was a moth trapped inside a Harvard Mark II computer in 1947.",
	"The world's fastest supercomputers all run on Linux.",
	"Open-source software allows users to see and modify the source code, fostering collaboration and innovation.",
	"The development of the Linux kernel started as a personal project by Linus Torvalds.",
	"The world wide web (www) was invented by Tim Berners-Lee in 1989.",
	"Python is a popular and beginner-friendly programming language often used for data science and web development.",
	"Many of the tools you use everyday, like web browsers and image editing software, have open-source alternatives.",
	"The term 'bug' to refer to a software error originated from the aforementioned moth incident.",
	"There are many online communities where programmers can help each other and learn new skills.",
	"Open-source software often benefits from a larger pool of developers, leading to faster bug fixes and new features.",
	"Did you know? The C programming language is known for being powerful and efficient, but also unforgiving for beginners.",
	"Emojis were first introduced in Japan in the late 1990s.",
	"The first computer program to defeat a human chess grandmaster was developed in the Soviet Union in the 1990s.",
	"Binary code, the language computers understand, consists of only 0s and 1s.",
	"Artificial intelligence (AI) is a branch of computer science focused on creating intelligent machines.",
	"The first commercial personal computer, the IBM PC, was released in 1981.",
	"Charles Babbage, a 19th-century mathematician, is considered the 'father of the computer' for his theoretical designs.",
	"Alan Turing, a British mathematician and computer scientist, is another key figure in the history of computing.",
	"The term 'hack' originally referred to clever solutions or workarounds, but its meaning has evolved over time.",
	"Cybersecurity is the practice of protecting computer systems and networks from unauthorized access, use, disclosure, disruption, modification, or destruction.",
	"The cloud refers to a network of servers that store data and applications accessible from anywhere with an internet connection.",
};
int iinfstrings = (sizeof(informationalstrings) / sizeof(informationalstrings[0]))-1;
