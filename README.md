## LUSH
by Lucy Hu

### Features: 
- Forks and executes commands
- Parses multiple commands on one line with ; 
- Simple redirction using > and <
- Simple pipes

---

### Attempted: 
- The following did not end up working, but have been left in the code, commented out:
  - I'm not too sure if I did the piping properly but I have another attempt where I used popen to get 
    the ouput of the first command to become the input of second command. However, the problem with 
    that was that it didn't work if the first or second command had more than 1 argument.

---

### Bugs: 
- cd, exit, and piping has to be on separate lines because some commands would repeat when any of 
  those were placed in the fork (the fork is where the parsing multiple commands on one line is taken 
  care of)
- Placing two ;'s next to each other results in seg fault
- Redirecting > (stdout) doesn't work properly when the command before > has more than 1 argument. But 
  redirecting < (stdin) works. I tried setting args[i] = NULL like I did for redirecting stdin but it 
  doesn't work and I don't know why.
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
  /*============char **create_args()=============
  Inputs: char **args
          char *line
          int beg
          int end
  Returns: Array of strings in which each index is a command argument

  Creates a temp array of strings that holds the commands separated by ;
  beg and end are the first and last (respectively) indices of args which determines range/size of the temp array
  end is dependent on find_semi() function
  If there is no ; (end is equal to -1) then end is set as the total number of tokens in args
  =============================================*/
  
  /*=============int *find_semi()===============
  Inputs: char **args
          char *line
  Returns: Int array in which each index is the index of where ; is in args
  
  Locates the index of ; in args
  If there is no ; then the index would be -1
  =============================================*/
  
  /*=============void redirect()================
  Inputs: char **args
  Returns: N/A
  
  Does simple redirection with < and >
  =============================================*/
  
  /*==============void my_cd()==================
  Inputs: char **args 
  Returns: N/A
  
  Executes cd command using chdir   
  =============================================*/
  
  /*==============void my_exit()================
  Inputs: char **args
  Returns: N/A
  
  Prints "Program exited" and frees args
  Executes exit command
  =============================================*/
 
  /*==============void my_pipe()================
  Inputs: char *line
  Returns: N/A
  
  Executes piping using popen
  =============================================*/
  
  /*==============void execute()================
  Inputs: char **args
  Returns: N/A
  
  Calls redirect() to see if it needs to redirect
  Executes commands using execvp
  =============================================*/
  
  /*==============void fork_exec()==============
  Inputs: char **args
          char *line
  Returns: N/A
  
  Forks and executes commands
  =============================================*/
  ```
### lush.c
  * Runs the entire program with all the necessary functions
  ```
  /*=============int main()==================
  Inputs: N/A
  Returns: 0
  
  Reads commands one line at a time
  Executes commands with neccessary functions
  Frees any allocated memory
  =========================================*/
  ```
