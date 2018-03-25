#include "log.h"

t_log* log_new(char * log_name) {
	t_log* nl;
	nl = log_create(log_name, log_name, 1, 0);
	return nl;
}

void log_write(t_log * log_file, int msg_type, const char * msg) {
	printf("%s\n", msg);
	switch (msg_type) {
	case TRACE: {
		log_trace(log_file, msg);
		break;
	}
	case DEBUGGING: {
		log_debug(log_file, msg);
		break;
	}
	case INFO: {
		log_info(log_file, msg);
		break;
	}
	case WARNING: {
		log_warning(log_file, msg);
		break;
	}
	case ERROR: {
		log_error(log_file, msg);
		break;
	}
	default:
		break;
	}
}

/*
void log_print(t_log* log_file) {
	printf("%s", log_file->file);
}
*/
