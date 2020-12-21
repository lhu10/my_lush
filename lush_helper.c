#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "parse.h"
#include "lush_helper.h"

char **create_args(char **args, char *line, int beg, int end){
    int total = count_tokens(line, ' '); 
    if(end == -1){
        end = total; 
    }
    end = end - beg; 
    end++; 
    char **new_args = malloc(end * sizeof(char *));
    int i = 0; 
    while(i != (end-1)){
        new_args[i] = args[beg];
        beg++; 
        i++; 
    }
    new_args[end-1] = NULL; 

    return new_args; 
}

int *find_semi(char **args, char *line){
    int n = count_tokens(line, ';');
    int *arr = malloc(n * sizeof(int)); 
    int index = 0;
    int i = 0; 
    while(args[index] != NULL){
        if(strcmp(args[index], ";") == 0){
            arr[i] = index; 
            i++;  
        }
        index++; 
    }
    arr[n-1] = -1; 
    return arr; 
}

void redirect(char **args){
    int i = 0; 
    while(args[i] != NULL){
        int fd;
        if(strcmp(args[i], ">") == 0){
            fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            //redirecting stdout to fd
            dup2(fd, STDOUT_FILENO);
            close(fd); 
        }
        if(strcmp(args[i], "<") == 0){
            fd = open(args[i+1], O_RDONLY);
            //redirecting stdin to fd
            dup2(fd, STDIN_FILENO);
            args[i] = NULL;
            close(fd); 
        }
        i++; 
    }
}

void my_cd(char **args){
    int i = 1; 
    char buff[100];
    if(args[i] != NULL){
        chdir(args[i]); 
        i++;
    }
    printf("%s\n\n", getcwd(buff, sizeof(buff)));
}

void my_exit(char **args){
    printf("Program exited\n");
    free(args);
    exit(0);
}

void my_pipe(char *line){
    FILE *fp; 
    fp = popen(line, "w"); 
    pclose(fp);
    printf("\n");
}

/*void my_pipe(char **args){
    FILE *input, *output; 
    int i = 0;
    while(args[i] != NULL){
        if(strcmp(args[i], "|") == 0){
            //output of ls becomes input for wc
            input = popen(args[i-1], "r");
            output = popen(args[i+1], "w");
            char in[256];
            while(fgets(in, sizeof(in), input) != NULL){
                fprintf(output, "%s", in);
            }
        }
        i++; 
    }
    pclose(input);
    pclose(output);
    printf("\n");
}*/

void execute(char **args){
    redirect(args);
    execvp(args[0], args);
}

void fork_exec(char **args, char *line){
    //setting up to fork and execute command
    int f, status; 
    int beg = -1; 
    int end = -1; 
    //helps determine n number of ; 
    int n = count_tokens(line, ';');
    int *semi_arr = find_semi(args, line);
    for(int i = 0; i < n; i++){
        beg = end+1; 
        end = semi_arr[i];
        char **temp_args = create_args(args, line, beg, end);
        f = fork(); 
        if(f == 0){ 
            execute(temp_args);
        }
        else{
            //waits for child to do its execute so parent can free
            wait(&status);
            printf("\n");
            free(temp_args);
        }
    }
    free(semi_arr);
}
