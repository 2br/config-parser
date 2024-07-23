#pragma once

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

// Numbers
#define CONFIG_DEF(name, variable, type, defval) { name, variable, 0, type, defval }
// String
#define CONFIG_DEFS(name, variable, size, defval) { name, variable, size, CDT_STRING, defval }

#define CONFIG_DEFI(name, variable, defval) { name, variable, 0, CDT_INT, defval }

// Setting multiple configs by a file
int config_read_file(const char* file_name, struct s_config_data configurations[], int config_arr_size);
// Set single value
int config_set_value(struct s_config_data* config, const char* value);
