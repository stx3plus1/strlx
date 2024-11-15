/*
 * JSON configuration Parser
 * by stx3plus1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "include/string.h"

/*
 * This function handles configurations. fclose() should be run on exit.
 * The purpose is to allow a generation and run of a config without
 * having to rerun the program as was done in 2.0.
 *
 * TODO: char* file and char* directory? There's 100% a way to do this.
 *
 * file - input location
 * directory - directory location if a mkdir() is required. - please fix
 * conf - the config to be written if input location is not found
 * RETURNS - file which has been fopen()'d or NULL if all fails
 */

FILE* generate_open_config(char* file, char* directory, char* conf[], int conf_len) {
	FILE* CONFIG = fopen(concat_strings(directory, file), "ro");
	if (!CONFIG) {
		mkdir(directory, 0700);
		CONFIG = fopen(file, "w");
		if (!CONFIG) {
			return NULL;
		}
		int write = 0;
		for (int write = 0; write < conf_len; write++) {
			fprintf(CONFIG, "%s", conf[write]);
			fprintf(CONFIG, "\n");
		}
		fclose(CONFIG);
		CONFIG = fopen(file, "ro");
		return CONFIG;
	} else {
		return CONFIG;
	}
}

/*
 * This function inputs a JSON config and outputs raw tokens that the main 
 * function can strcmp() and show the system information from.
 *
 * config - FILE* which is a JSON configuration for the program
 * keys, values - outputs values parsed by main
 * RETURNS: length of both keys and values.
 */

int parse_json(FILE* config, char* keys[], char* values[]) {
	char line[128];
	char key[64];
	char value[64];
	
	int i = 0;
	int tok_len = 0;
	while (fgets(line, sizeof(line), config)) {
		char* ptr = line;
		while (*ptr == ' ' || *ptr == '\t') ptr++;
		if (*ptr == '{' || *ptr == '}') continue;
		if (*ptr == '\"') {
			ptr++;
			char* key_start = ptr;
			while (*ptr != '\"' && *ptr) ptr++;
			strncpy(key, key_start, ptr - key_start);
			key[ptr - key_start] = '\0';
			
			ptr++;

			while (*ptr && *ptr != '\"' && *ptr != '[') ptr++;
			if (*ptr == '\"') {
				ptr++;
				char* value_start = ptr;
				while (*ptr != '\"') ptr++;
				strncpy(value, value_start, ptr - value_start);
				value[ptr - value_start] = '\0';
			} else if (*ptr == '[') {
				// This is a bit of a hack but it works.
				strncpy(value, "array\0", 6);
			}
			char* keyout = malloc(sizeof(char) * (strlen(key) + 1));
			sprintf(keyout, "%s", key);
			keys[i++] = keyout;
			char* valout = malloc(sizeof(char) * (strlen(value) + 1));
			sprintf(valout, "%s", value);
			values[i - 1] = valout; // for some reason this is correct.
			tok_len++;
		}
	}
	return tok_len;
}
