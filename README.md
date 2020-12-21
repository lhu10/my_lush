## LUSH
by Lucy Hu

### Features: 
- Forks and executes commands
- Parses multiple commands on one line with ; 
- Simple redirction using > and <
- Simple pipes

---

### Attempted: 

---

### Bugs: 
- cd, exit, and piping has to be on separate lines because some commands would repeat when any of those were placed in the fork (the fork is where the parsing multiple commands on one line is taken care of)
- Placing two ;'s next to each other results in seg fault
- Redirecting > (stdout) doesn't work properly when the command before > has more than 1 argument. 
  For example:
  ```
  $ echo hello > hi
  $ cat hi
  hello > hi
  ```

---

### Files & Function Headers: 
### parse.c
  * Handles all line-related functions
  ```
  /*===========int count_tokens()==============
  Inputs: char *line
          char delim
  Returns: Number of tokens in a line separated by delim
  
  Counts the number of times delim appears in line
  The count starts at 1 so if delim does not appear, 1 is returned
  ===========================================*/
  
  /*===========char **parse_args()=============
  Inputs: char *line
  Returns: Array of strings in which each index is a token separated by a single space
  
  Line is parsed into tokens separated by a single space
  Last index of array is set as NULL
  ===========================================*/
  
  /*===========void rid_new_line()=============
  Inputs: char *line
  Returns: N/A
  
  Gets rid of the new line created by fgets
  ===========================================*/
  ```
### lush_helper.c
  * Handles the executing of commands and helper functions for modularity
  ```
  char **create_args(char **args, char *line, int beg, int end);
  int *find_semi(char **args, char *line);
  void redirect(char **args);
  void my_cd(char **args);
  void my_exit(char **args);
  void my_pipe(char *line);
  void execute(char **args);
  void fork_exec(char **args, char *line);
    
  ```
### lush.c
  * Runs the entire program with all the necessary functions
  ```
  /*=============int main()=================
  Inputs: N/A
  Returns: 0
  
  Reads commands one line at a time
  Executes commands with neccessary functions
  ========================================*/
  ```
