#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "parse.h"

int count_tokens(char *line, char delim){
    char *temp; 
    int count;
    count = 1; 
    temp = line; 
    while(*temp){
        if(*temp == delim) count++; 
        *temp++; 
    }
    return count; 
}

char **parse_args(char *line){
    char *curr, *token;
    int n, i;
    n = count_tokens(line, ' ') +1; 
    char **args = malloc(n * sizeof(char *));
    curr = line; 
    i = 0; 

    while((token = strsep(&curr, " ")) != NULL){
        args[i] = token; 
        //printf("args[%d]: %s\n", i, args[i]);
        i++;
    }
    args[i] = NULL; 

    return args; 
}

void rid_new_line(char *line){
    //gets rid of new line
    char *sp; 
    if((sp = strchr(line, '\n')) != NULL){
        *sp = '\0';
    }
}
