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
- Placing two ;'s next to each results seg fault
- Redirecting > (stdout) doesn't work properly when the command before > has more than 1 argument. 
  For example:
  ```
  $ echo hello > hi
  $ cat hi
  hello > hi
  ```

---

### Files & Function Headers: 
#### parse.c
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
