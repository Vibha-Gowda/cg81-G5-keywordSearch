#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "../Header/header.h"

sp* projectll=NULL;
skw *keywordll=NULL;

int main(int argc, char** argv){

    if(argc<2){
        printf("Please provide  filename as argument!\n");
        printf("Usage ./main <Research Papaer file1> <Research Papaer file2> ...\n");
        exit(0);
    }

    pthread_t pthreads[argc-1];
    for(int i=1 ; i<argc; i++){
        int ret = pthread_create(&pthreads[i-1], NULL, extract_project_details, (void*)(argv[i]) );
        
        //check if thread created for return value
        if(ret){
            printf("\nError! Thread creation falied! Return code from is: %d", ret);
            exit(0);
        }
    }

    for(int i=1; i<argc; i++){
        pthread_join(pthreads[i-1], NULL);
    }

    
    FILE *fptr2;
    fptr2 = fopen("/home/Code/data/result.txt", "w");

    skw *temp2 = keywordll;
    while(temp2!=NULL){
        printf("Key: %s", temp2->key);
        fprintf(fptr2, "\nKeyword: %s", temp2->key);

        for(int i=0; i<temp2->index; i++){
            printf("\n%s", temp2->projectIds[i]);
            printf(" :%s", temp2->projectTitle[i]);
            
            fprintf(fptr2, "\n%s", temp2->projectIds[i]);
            fprintf(fptr2, " :%s", temp2->projectTitle[i]);

        }
        printf("\n\n\n");
        fprintf(fptr2,"\n\n\n");

        temp2=temp2->next;
    }

    fclose(fptr2);

    cleanFunc();
    return 0;
}
