#include "../Utils/error.h"
#include "../Utils/utils.h"


char *
find_shell()
{
	char* binary_paths = {"/bin/bash","/bin/dash","/bin/sh/"}
	struct stat buffer;
	for (int i = 0; i < 3; i++) {
		if (stat(binary_paths[i], buffer) == 0) return binary_paths[i];
	}

	return NULL;
}

int
run_cmd(char *shell_path, char* cmd, char* output)
{

}

int
is_bash_process(int pid)
{
	char exe_path[200];
	int len;

	snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);

	len = readlink(exe_path, exe_path, sizeof(exe_path)-1);
	if (len == -1) return -1;

	exe_path[len] = '\0';

	if (strcmp(exe_path, TARGET_EXE) == 0) return 0;

	return -1;
}

int
find_processes() {
	DIR* dir = opendir(PROC_DIR);

	if (dir == NULL) {
		print_error("SHELL - Failed to find a /bin/bash process");
		return -1;
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
			int pid = atoi(entry->d_name);

			if (is_bash_process(pid) != -1) {
				print_info("SHELL - Found /bin/bash process");
				return pid;
			}
		}
	}
	print_error("SHELL - Loop failed to find a /bin/bash process");
	return -1;
}
