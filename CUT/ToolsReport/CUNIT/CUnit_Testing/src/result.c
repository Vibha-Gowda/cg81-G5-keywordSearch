#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include "../include/result.h"


int result_Valid(char *key)
{
    FILE *fptr = fopen("data/result.txt","r");
    
    if(!fptr)
    {
       printf("\nError: Result file not found");
       exit(0);
    }
    
    int flag=0, count=0;
    char str[SIZE], *token;
    //reading line by line
    while(fgets(str, SIZE, fptr)){
        
        token = strtok(str, "-");
        if(flag==1){
            if(strcmp(token, "Keyword")==0)
                break;
            count+=1;
        }

        if(strcmp(token, "Keyword")==0){

            while(token!=NULL && flag!=1){
                
                if(strcmp(key, token)==0){
                    flag=1;
                }
                token = strtok(NULL, "-");
            }
        }

    }
    return count/2;
}
