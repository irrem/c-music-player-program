#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50


struct node
{
    struct node *prev;
    struct node *next;
    char songame[50];
}node;


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
		FILE *outf = fopen("output.txt", "w");
		    if (outf == NULL)
		    {
		        printf("\nError opening output.txt file");
		        return 1;
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
			            	fprintf(outf, "No Songs To Play\n");
						}
						else{
							if(!strcmp("F", yon)){
							printf("PrintPlaylist\n");
							while(ptr!= NULL)
					    	{
							fprintf(outf,"%s\n",ptr->songame);
							ptr=ptr->next;
					   		}
							}
							
							else if(!strcmp("R", yon)){
							printf("PrintPlaylist\n");
								struct node* prev = NULL;
					    		struct node* current = head;
					    		struct node* next = NULL;
					    		while (current != NULL) {
					       		next = current->next;
					        	current->next = prev;
					        	prev = current;
					        	current = next;
					    	}
					    	head = prev;
					    	ptr=head;
							while(ptr!= NULL)
					    	{
							fprintf(outf,"%s\n",ptr->songame);
							ptr=ptr->next;
					   		}
							}
							
						}
						fprintf(outf, "*****\n");
					    
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
			        
			        else if(!strcmp("MoveSong", command))
			        {
			            place = strtok(NULL, "\t"); //tab gelene kadar olan kýsm
			            name = strtok(NULL, "\t");
						referenceName = strtok(NULL, "\n");  //satýr sonu kontrol
			             	struct node *tmp1 = (struct node*) malloc(sizeof(node)); 
			             	
						    ptr = head;
						    strcpy(tmp1->songame, name);
						    
						    if(!strcmp("A",place)){
							
						     while(ptr != NULL && strcmp(ptr->songame,referenceName) != 0 &&ptr->next != NULL){
							        ptr = ptr->next;
							    }
							
							    if(ptr == NULL){
							        return;
							    }
							
							    if(ptr->next == NULL){
							        ptr->next = tmp1;
							        tmp1->prev = ptr;
							        tmp1->next = NULL;
							        ptr=tmp1;
							        return;
							    }
							
							    ptr->next->prev = tmp1;
							    tmp1->next = ptr->next;
							    ptr->next = tmp1;
							    tmp1->prev = ptr;
							    ptr->next=tmp1->prev->next;
							    head->next=ptr;
						}else{
							
							 if(!strcmp(ptr->songame, referenceName)){
						      
						        return;
						    	}
						    	ptr=head;
								while(ptr!= NULL && strcmp(ptr->next->songame,name)){
							    ptr = ptr->next;
							    }
							    
							    struct node *tmp2;
							    struct node *tasinacak;
							    tasinacak=ptr->next;
							    ptr->next=ptr->next->next;
							    
							    tmp1=head;
							   	while(tmp1!= NULL && strcmp(tmp1->next->songame,referenceName)){
							    tmp1 = tmp1->next;
							    }
							    
							    tasinacak->next=tmp1->next;
							    tmp1->next=tasinacak;
							    
							    if(ptr == NULL){
							        return;
							    }
							   
							    printf("%s",ptr->songame);
							   
							}
					}
			        
			       else if(!strcmp("PlaySong", command)){
			       		
						yon = strtok(NULL, "\n"); 
						ptr = head;
						if(ptr==NULL){
			           	fprintf(outf, "No Songs To Play\n*****\n");
			           
						}
						else{
			            if(!strcmp("N",yon)){	
							if(ptr->next!=NULL){	
								ptr=ptr->next;
								fprintf(outf,"Playing : %s\n",ptr->songame);
							}
							else{
								struct node* prev = NULL;
					    		struct node* current = head;
					    		struct node* next = NULL;
								 while (current != NULL) {
					        		next = current->next;
					        		current->next = prev;
					        		prev = current;
					        		current = next;
					   			 }
					    		head = prev;
					    		ptr=head;
			            		fprintf(outf,"Playing : %s\n",ptr->songame);
							}
			            
						}
						else if(!strcmp("P",yon)){
							
							if(ptr->prev!=NULL){	
								ptr=ptr->prev;
								printf("Playing : %s\n",ptr->songame);
								
							}
							else{
								struct node* prev = NULL;
					    		struct node* current = head;
					    		struct node* next = NULL;
								 while (current != NULL) {
					        		next = current->next;
					        		current->next = prev;
					        		prev = current;
					        		current = next;
					   			 }
					    		head = prev;
					    		ptr=head;
			            		fprintf(outf,"Playing : %s\n",ptr->songame);
							}
							
						}
						fprintf(outf, "*****\n");
						}
						
			        }
					else if(!strcmp("ReversePlaylist", strtok(l, "\n")))
			        {
			        
        				
			        	struct node* prev = NULL;
					    struct node* current = head;
					    struct node* next = NULL;
					    while (current != NULL) {
					        next = current->next;
					        current->next = prev;
					        prev = current;
					        current = next;
					    }
					    head = prev;
			        }
		  	}
		
		fclose(f);
		free(ptr);
		fclose(outf);
		return 0;
	}
