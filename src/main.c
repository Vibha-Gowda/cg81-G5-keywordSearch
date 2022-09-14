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

    

    skw *temp2 = keywordll;
    while(temp2!=NULL){
        printf("\nKey: %s", temp2->key);

        for(int i=0; i<temp2->index; i++)
            printf("\n%s:\t%30s", temp2->projectIds[i], temp2->projectTitle[i]);
        printf("\n");

        temp2=temp2->next;
    }
    

    sp* temp;
    while(projectll!=NULL){
        temp=projectll;
        projectll=projectll->next;

        free(temp);
    }

    skw* temp1;
    while(keywordll!=NULL){
        temp1=keywordll;
        keywordll=keywordll->next;

        pthread_mutex_destroy(&(temp1->lock));
        free(temp1);
    }


    return 0;
}
