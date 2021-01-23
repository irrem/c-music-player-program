#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50


struct node
{
    struct node *prev;
    struct node *next;
    int data;
    char songame[50];
};
struct node *head;

int main()
	{
    	char *place, *command, *name, *yon, *referenceName; 
    	char l[100];
    	struct node *ptr;

		FILE *f = fopen("input.txt", "r");
		    if (f == NULL)
		    {
		        return 0;
		    }

		    while (fgets(l, 100, f) != NULL)
		    {
			        command = strtok(l, "\t");
			        
			        if (!strcmp("InsertSong", command))
			        {   
			            place = strtok(NULL, "\t"); //tab gelene kadar olan kýsm
			            name = strtok(NULL, "\n");  //satýr sonu kontrol
			            //printf("%s\n",name);
			           // printf("%s\n",place);
			            
			            if (!strcmp("H", place))
			            {
						   ptr = (struct node *)malloc(sizeof(struct node));
						   if(ptr == NULL)
						   {
						       printf("\nOVERFLOW");
						   }
						   else
						   {			
							   if(head==NULL)
							   {
							       ptr->next = NULL;
							       ptr->prev=NULL;
							       strcpy(ptr->songame,name);
							       head=ptr;
							   }
							   else
							   {
							       strcpy(ptr->songame,name);
							       ptr->prev=NULL;
							       ptr->next = head;
							       head->prev=ptr;
							       head=ptr;
							   }
							   printf("\nNode inserted\n");
							}
			            }
			            else if(!strcmp("T", place)){
							struct node *temp;
						   ptr = (struct node *) malloc(1*sizeof(struct node));
						   if(ptr == NULL)
						   {
						       printf("\nOVERFLOW");
						   }
						   else
						   {
						        strcpy(ptr->songame,name);
						       if(head == NULL)
						       {
						           ptr->next = NULL;
						           ptr->prev = NULL;
						           head = ptr;
						       }
						       else
						       {
						          temp = head;
						          while(temp->next!=NULL)
						          {
						              temp = temp->next;
						          }
						          temp->next = ptr;
						          ptr ->prev=temp;
						          ptr->next = NULL;
						        }
						    }   //	printf("\nnode inserted\n");
						} 						
					}
					
					else if(!strcmp("PrintPlaylist", command))
			        { 	
						yon = strtok(NULL, "\n");
						ptr = head;
			           
			            if(ptr==NULL){
			            	printf("No Song To Print\n");
						}
						else{
							if(!strcmp("F", yon)){
							printf("PrintPlaylist\n");
							while(ptr!= NULL)
					    	{
							printf("%s\n",ptr->songame);
							ptr=ptr->next;
					   		}
							}
							
						}
						printf("\n*****\n");
					    
			        } 
			        
					else if(!strcmp("RemoveSong", command)){
			            name = strtok(NULL, "\n"); 
			            struct node *temp;
					    ptr = head;
					    while(strcmp(ptr ->next->songame,name) != 0)
					    ptr = ptr -> next;
					    if(ptr -> next == NULL)
					    {
					        printf("\nCan't delete\n");
					    }
					    else if(ptr -> next -> next == NULL)
					    {
					        ptr ->next = NULL;
					    }
					    else
					    {
					        temp = ptr -> next;
					        ptr -> next = temp -> next;
					        temp -> next -> prev = ptr;
					        free(temp);
					        printf("\nnode deleted\n");
					    }
			            printf("RemoveSong\n");
			        }
			        /*
			        else if(!strcmp("MoveSong", command))
			        {
			            place = strtok(NULL, "\t"); //tab gelene kadar olan kýsm
			            name = strtok(NULL, "\t");
						referenceName = strtok(NULL, "\n");  //satýr sonu kontrol
			            printf("MoveSong\n");
			            struct node *ptr, *temp;
						    ptr = head;
						    while(strcmp(ptr ->next->songame,name) != 0)
						    ptr = ptr -> next;
						    if(ptr -> next == NULL)
						    {
						        printf("\nCan't move\n");
						    }
						    else if(ptr -> next -> next == NULL)
						    {
						        ptr ->next = NULL;
						    }
						    else
						    {
						        temp = ptr -> next;
						        ptr -> next = temp -> next;
						        temp -> next -> prev = ptr;
						        free(temp);
						        printf("\nnode deleted\n");
						    }
			        }
			        */
			        else if(!strcmp("PlaySong", command)){
					
			            yon = strtok(NULL, "\n");  //satýr sonu kontrol
			            //printf("PlaySong\n");
			            if(!strcmp("N",yon)){
			            	if(ptr==NULL)
			            		printf("No Song To Play\n");
							else{
						    ptr = head;
						    while(ptr->next!= NULL)
					    	{
							printf("%s\n",ptr->songame);
							ptr=ptr->next;
					   		};
						    if (ptr->next==NULL)
						        printf("No songs to play\n");
						    else{
						        printf("Playing : %s\n",ptr->next->songame);
						        printf("----------------------\n");
						    }
							}
						    
						}
						printf("*****\n");
			        }
					else if(!strcmp("ReversePlaylist", strtok(l, "\n")))
			        {
			        	yon = strtok(NULL, "\n"); 
			            printf("ReversePlaylist\n");
			        	struct node* prev = NULL;
					    struct node* current = head;
					    struct node* next = NULL;
					    while (current != NULL) {
					        // Store next
					        next = current->next;
					
					        // Reverse current node's pointer
					        current->next = prev;
					
					        // Move pointers one position ahead.
					        prev = current;
					        current = next;
					    }
					    head = prev;
			        }
		  	}
		
		fclose(f);
		free(ptr);
		return 0;
	}
