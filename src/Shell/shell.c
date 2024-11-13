
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
