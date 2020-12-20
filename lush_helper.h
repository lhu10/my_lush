char **create_args(char **args, char *line, int beg, int end);
int *find_semi(char **args, char *line);
void redirect(char **args);
void my_cd(char **args);
void my_exit(char **args);
void my_pipe(char *line);
void execute(char **args);
void fork_exec(char **args, char *line);
