#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "parse.h"
#include "lush_helper.h"

int main(int argc, char **argv){

    char buff[256];
    //reads one line at a time
    while(fgets(buff, sizeof(buff), stdin) != NULL){
        rid_new_line(buff);
        printf("%s\n", buff);
        //copies command to a temp
        char temp_buff[256]; 
        strcpy(temp_buff, buff);
        //parses
        char **args = parse_args(buff);

        int pipe_check = count_tokens(temp_buff, '|');
        if(strcmp(args[0], "cd") == 0 ){
            my_cd(args);
        }
        else if(strcmp(args[0], "exit") == 0){
            my_exit(args);
        }
        else if(pipe_check > 1){
            my_pipe(temp_buff);
        }
        else{
            fork_exec(args, temp_buff);
        }
        free(args); 
    }
    
    return 0; 
}
