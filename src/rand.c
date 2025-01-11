/*
 * better random seed
 * by stx3plus1
 */

#include <unistd.h>
#include <fcntl.h>

/* 
 * A better random function using only POSIX.
 * Takes advantage of urandom, combines the character codes then returns.
 *
 * RETURNS: a pretty random number
 */

int brand() {
	int buf[2];
	int ufd = open("/dev/urandom", O_RDONLY);
	read(ufd, buf, 2);
	close(ufd);
	int random = buf[0] + buf[1];
	return random;
}
