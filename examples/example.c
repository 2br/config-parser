
#include "../config.h"
#include <stdio.h>
#include <stdbool.h>

static struct s_server_config {
	bool enable_feature;
	char user_name[256];
	int max_connections;
	float timeout_in_seconds;
	short min_password_length;
} server_config;

//struct _test_conf test_conf;

struct s_config_data config_data[] = {
	CONFIG_DEFB("enable_feature", 		&server_config.enable_feature, 			"false"),
	CONFIG_DEFS("username", 			&server_config.user_name, 256, 			""),
	CONFIG_DEFI("max_connections", 		&server_config.max_connections,			"10"),
	CONFIG_DEFD("timeout", 				&server_config.timeout_in_seconds,		CDT_FLOAT, "3.5"),
	CONFIG_DEF("min_password_length", 	&server_config.min_password_length, 	CDT_SHORT )
};

int main() {

	int config_arr_size = ARRAYLENGTH(config_data);

	config_read_file("config.conf", &config_data[0], config_arr_size);

	
	printf("%d\n", server_config.enable_feature);
	printf("%s\n", server_config.user_name);
	printf("%d\n", server_config.max_connections);
	printf("%.3f\n", server_config.timeout_in_seconds);
	printf("%d\n", server_config.min_password_length);
		
	return 0;
}