#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "../Header/header.h"



void keywordSearch(sp *p1, char *token, skw **keywordll)
{
    token[strlen(token)-1]='\0';

    if((*keywordll)==NULL){
        skw* newNode = (skw*) calloc(1, sizeof(skw));
        strcpy(newNode->key, token);
        newNode->index=0;
        strcpy(newNode->projectIds[newNode->index], p1->projectId);
        strcpy(newNode->projectTitle[newNode->index], p1->projectTitle);
        newNode->index+=1;
        newNode->next= NULL;
        
        //Initialize Mutex
        if(pthread_mutex_init(&(newNode->lock), NULL)!=0){
            printf("\nError! Mutex init has failed\n");
            cleanFunc();
            exit(0);
        }
        (*keywordll) = newNode;
    }
    else{
        skw* temp = *keywordll;
        if(strcmp(temp->key, token)==0){
            //Lock Mutex
            pthread_mutex_lock(&(temp->lock));

            strcpy(temp->projectIds[temp->index], p1->projectId);
            strcpy(temp->projectTitle[temp->index], p1->projectTitle);
            temp->index+=1;

            //unlock Mutex
            pthread_mutex_unlock(&(temp->lock));
            return;
        }
        else{
            while(temp->next!=NULL){
                if(strcmp(temp->next->key, token)==0){
                    //Lock Mutex
                    pthread_mutex_lock(&(temp->next->lock));

                    strcpy(temp->next->projectIds[temp->next->index], p1->projectId);
                    strcpy(temp->next->projectTitle[temp->next->index], p1->projectTitle);
                    temp->next->index+=1;

                    //Unlock Mutex
                    pthread_mutex_unlock(&(temp->next->lock));
                    return;
                }
                temp=temp->next;
            }
            temp->next = (skw*) calloc(1, sizeof(skw));
            strcpy(temp->next->key, token);
            strcpy(temp->next->projectIds[temp->next->index], p1->projectId);
            strcpy(temp->next->projectTitle[temp->next->index], p1->projectTitle);
            temp->next->index+=1;

            //Initialize Mutex
            if(pthread_mutex_init(&(temp->next->lock), NULL)!=0){
                printf("\nError! Mutex init has failed\n");
                cleanFunc();
                exit(0);
            }
            temp->next->next = NULL;
        }
    }

    return;
}


void* extract_project_details(void *tempfile){

    FILE* fptr = fopen((char*)tempfile, "r");

    //to do validations
    if(!validation((char*)tempfile)){
        printf("\nError! File invalid <%s>\n", (char*)tempfile);
    }
    else if(!fptr){
        printf("\nError! file not found: %s\n", (char*)tempfile);
    }
    else{

        printf("\nExtracting.. %s", (char*)tempfile);

        sp *new_pro_node = (sp*) calloc(1, sizeof(sp));
        new_pro_node->next = NULL;

        skw *new_key_node = NULL;
        skw *temp;

        int proID, proT, keyw;
        proID=proT=keyw=0;
        
        char str[SIZE], *token, keySearch[SIZE];
        while(fgets(str, SIZE, fptr)){

            token = strtok(str, "-");
            while(token!=NULL){
                
                if(strcmp(token, project_id_str)==0)
                    proID+=1;

                else if(proID==1){
                    token[strlen(token)-1]='\0';
                    strcpy(new_pro_node->projectId, token);
                    proID=0;

                    if(projectll==NULL)
                        projectll=new_pro_node;
                    else{
                        sp *temp = projectll;

                        while(temp->next!=NULL){
                            temp=temp->next;
                        }
                        temp->next=new_pro_node;
                        new_pro_node->next = NULL;
                    }
                }	

                else if(strcmp(token, project_title_str)==0)
                    proT+=1;

                else if(proT==1){
                    token[strlen(token)-1]='\0';
                    strcpy(new_pro_node->projectTitle, token);
                    proT=0;
                }

                else if(strcmp(token, keyword_str)==0)
                    keyw+=1;

                else if(keyw==1){
                    strcpy(keySearch, token);
                    keywordSearch(new_pro_node, keySearch, &keywordll);
                    keyw=0;
                }

                

                token=strtok(NULL, "-");
            }
        }

    }

    fclose(fptr);
}


int validation(char* tempfile){

    FILE* fptr = fopen((char*)tempfile, "r");

    int proID, proT, keyw;
    proID=proT=keyw=0;

    char str[SIZE], *token;
    while(fgets(str, SIZE, fptr)){

        token = strtok(str, "-");
        // while(token!=NULL){

            if(strcmp(token, project_id_str)==0)
                proID+=1;
            else if(strcmp(token, project_title_str)==0)
                proT+=1;
            else if(strcmp(token, keyword_str)==0)
                keyw+=1;
            
            // token=strtok(NULL, "-");
        // }
    }

    fclose(fptr);

    if(proID && proT && keyw)
        return 1;

    return 0;
}




int result_Valid(char *key)
{
    FILE *fptr = fopen("../data/result.txt","r");
    if(!fptr)
        printf("\nError: Result file not found");

    int flag=0, count=0;
    char str[SIZE], *token;

    //reading line by line
    while(fgets(str, SIZE, stdin)){

        token = strtok(str, " ");

        if(flag==1){
            if(strcmp(token, "Keyword:")==0)
                break;

            count+=1;
        }

        while(token!=NULL && flag!=1){
            if(strcmp(key, token)==0){
                flag=1;
            }

            token = strtok(NULL, " ");
        }
    }

    return count;
}


void cleanFunc(){
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
}


