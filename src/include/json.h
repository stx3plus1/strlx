/*
 * JSON Parser
 * by stx3plus1
 */

#include <stdio.h>

FILE* generate_open_config(char* file, char* directory, char* conf[], int conf_len);
int parse_json(FILE* config, char* keys[], char* values[]);
