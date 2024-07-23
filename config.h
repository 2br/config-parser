#pragma once
#include <stdlib.h>
typedef enum config_data_type {
	CDT_BOOL,
	CDT_SHORT,
	CDT_INT,
	CDT_FLOAT,
	CDT_STRING
} config_data_type;


typedef enum {
	CONF_SUCCESS = 0,
	CONF_ERR_FILE_NOT_FOUND,
	CONF_INVALID_TYPE,
	CONF_NULL_POINTER
} config_result_code;

struct s_config_data {
	const char* name;
	void* value;
	size_t size;
	config_data_type type;
	const char* default_value;
};

#ifndef ARRAYLENGTH // Size of statis array
#define ARRAYLENGTH(A) ( sizeof(A)/sizeof((A)[0]) )
#endif

/**
 * Macros to simplify setting configs
 */
// Numbers
#define CONFIG_DEF(name, variable, type, defval) { name, variable, 0, type, defval }
// String
#define CONFIG_DEFS(name, variable, size, defval) { name, variable, size, CDT_STRING, defval }
// Integer
#define CONFIG_DEFI(name, variable, defval) { name, variable, 0, CDT_INT, defval }
// Bool
#define CONFIG_DEFB(name, variable, defval) { name, variable, 0, CDT_BOOL, defval }


// Set the default values (will run in first config_read_file anyway)
void config_set_defaults(struct s_config_data configurations[], int config_arr_size);
// Setting multiple configs by a file
int config_read_file(const char* file_name, struct s_config_data configurations[], int config_arr_size);
// Set single value
int config_set_value(struct s_config_data* config, const char* value);
// Return the message from a error code
const char* config_get_error_message(config_result_code code);