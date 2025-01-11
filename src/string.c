/*
 * Safe string concatenation.
 * by stx3plus1
 */ 

#include "include/string.h"

/*
 * This function concatenates 2 strings. Really.
 * Strings outputted by this function should be free()'d on exit!
 *
 * str1 - first string
 * str2 - second string
 * RETURNS - concatenated strings
 */

char* concat_strings(char* str1, char* str2) {
	char* ret = malloc(strlen(str1) + strlen(str2) + 1);
	sprintf(ret, "%s%s", str1, str2);
	return ret;
}
