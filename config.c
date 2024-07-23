#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Function to trim leading and trailing whitespace characters
static char* trim(char* str) {
	char* end;

	// Trim leading space
	while (isspace((unsigned char)*str)) str++;

	// All spaces?
	if (*str == 0) {
		return str;
	}

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	// Write new null terminator
	*(end + 1) = 0;
	return str;
}

/**
 * Return numeric value of possible variations of boolean
 * - on/off
 * - yes/no
 * - true/false
 * - enabled/disabled
 */
static bool config_bool_variations(const char* str) {
	if (_stricmp(str, "on") == 0 || _stricmp(str, "yes") == 0 || _stricmp(str, "true") == 0 || _stricmp(str, "enabled") == 0)
		return true;
	if (_stricmp(str, "off") == 0 || _stricmp(str, "no") == 0 || _stricmp(str, "false") == 0 || _stricmp(str, "disabled") == 0)
		return false;
	return false;
}


/**
 * Commented lines
 */
static bool is_valid_line(char* line) {
	int i = 0;
	// Start with # so... is commented
	if ('#' == line[0]) {
		return false;
	}

	if ('/' == line[0] && '/' == line[1]) {
		return false;
	}

	// Empty line, skip it
	 // Check if the line is empty or contains only whitespace characters
	while (line[i] != '\0') {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
			break;
		}
		i++;
	}
	if (line[i] == '\0') {
		return false;
	}

	// Reset i for the next check
	i = 0;

	// Skip leading spaces to find if the line contains a comment starting with //
	while (line[i] == ' ' || line[i] == '\t') {
		i++;
	}

	if (line[i] == '/' && line[i + 1] == '/') {
		return false;
	}

	// No comment found
	return true;
}


/**
 * Init configs and set the default value
 */
void config_set_defaults(struct s_config_data configurations[], int config_arr_size) {
	int i;
	for (i = 0; i < config_arr_size; ++i) {
		config_set_value(&configurations[i], configurations[i].default_value);
	}
}

/**
 * Reads config file
 * 
 * import: makes it open again
 */
int config_read_file(const char* file_name, struct s_config_data configurations[], int config_arr_size) {
	char line[1024], w1[1024], w2[1024];
	char *key, *value;
	static int run_count = 0;
	FILE *fp;
	int i;

	// First execution
	if( run_count == 0 ) {
		config_set_defaults(configurations, config_arr_size);
	}

	run_count++;

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		return CONF_ERR_FILE_NOT_FOUND;
	}
	while (fgets(line, sizeof(line), fp)) {
		if (!is_valid_line(line)) {
			continue;
		}
		
		// Try to match ':' first
		if (sscanf(line, "%1023[^:]:%1023[^\n]", w1, w2) != 2) {
			continue;
		}
		
		key	  = trim(w1);
		value = trim(w2);
		// Handle import directive (new file)
		if (_stricmp(key, "import") == 0) {
			config_read_file(value, configurations, config_arr_size);
			continue;
		}

		for (i = 0; i < config_arr_size; ++i) {
			if (_stricmp(key, configurations[i].name) == 0) {
				config_set_value(&configurations[i], value);
				break;
			}
		}
	}
	fclose(fp);

	run_count--;
	// Is the main execution
	if( run_count == 0 ) {
		// Adjusts configs
	}
	return CONF_SUCCESS;
}

/**
 * Set value of config specif configuration entry, does the type parsing
 */
int config_set_value(struct s_config_data *config, const char* value)
{
	// Invalid config or value
	if (config == NULL || config->value == NULL) {
		return CONF_NULL_POINTER;
	}

	// Invalid string
	if (value == NULL) {
		return CONF_NULL_POINTER;
	}
	switch( config->type ) {
	case CDT_BOOL:
		*((bool*)config->value) = config_bool_variations(value);
		break;

	case CDT_STRING:
		strncpy((char*)config->value, value, config->size);
		// Ensure null-termination.
		((char*)(config->value))[config->size - 1] = '\0';
		break;

	case CDT_INT:
		*((int*)config->value) = atoi(value);
		break;

	case CDT_FLOAT:
		*((float*)config->value) = atof(value);
		break;

	case CDT_SHORT:
		*((short*)config->value) = (short)atoi(value);
		break;

	default:
		return CONF_INVALID_TYPE;
	}
	return CONF_SUCCESS;
}

const char* config_get_error_message(config_result_code code) {
	switch (code) {
	case CONF_SUCCESS: return "Success";
	case CONF_ERR_FILE_NOT_FOUND: return "File not found";
	case CONF_INVALID_TYPE: return "Invalid type";
	case CONF_NULL_POINTER: return "Null pointer or not provided";
	default: return "Unknown error";
	}
}