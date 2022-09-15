#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include "../include/valid.h"


int validation(char *filename){

    FILE* fptr = fopen((char*)filename, "r");

    //to do validations

    if(!fptr){
        printf("Error! file not found: %s", (char*)filename);
        exit(0);
    }

    int proID, proT, keyw;
    proID=proT=keyw=0;
     
     

    char str[SIZE], *token;
    while(fgets(str, SIZE, fptr)){

        token = strtok(str, "-");
        while(token!=NULL){

            if(strcmp(token, project_id_str)==0)
                proID+=1;
            else if(strcmp(token, project_title_str)==0)
                proT+=1;
            else if(strcmp(token, keyword_str)==0)
                keyw+=1;
            
            token=strtok(NULL, "-");
        }
    }
     fclose(fptr);
    if(proID && proT && keyw)
        return 1;
    else
        return 0;


}
