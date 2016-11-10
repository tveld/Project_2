// Cross Reference Generator
// Troy Veldhuizen
// list.c

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

typedef struct node {
	char* id;
	int line;
	queue_t lines;
   	struct node * next;
} node_t;

typedef struct list {
	node_t* head;
} list_t;

int compair_line(int line1, int line2){
	if(line1 > line2){
		return 1;
	} else if(line1 < line2){
		return -1;
	} else {
		return 0;
	}
}

int compair_id(char* ch1, char* ch2){
	return( strcmp(ch1, ch2));
}


void list_insert(list_t* list, int line, char* newId) {

	node_t *temp = list->head;	
	
	if(temp == NULL){
	
		node_t *new1 = malloc(sizeof(node_t));
		list->head = new1;

		node_t *new2 = malloc(sizeof(node_t));
		new2->id = newId;
		new2->line = line;
		enqueue(&(new2->lines), line);
		new2 -> next = NULL;
		list->head->next = new2;
		return;
	}
	

	//check rest of nodes
    	while (temp->next != NULL) {

		// check if duplicate
		if( strcmp(temp->next->id,newId) == 0 ){
			enqueue( &(temp->next->lines), line);
			return;		
        	}

		

		// check if need to insert
		if( compair_line(temp->next->line, line) > 0 ){
			node_t *new = temp->next;
		    	temp->next = malloc(sizeof(node_t));
			temp->next->id = newId;
			temp->next->line = line;
			enqueue(&(temp->next->lines), line);

			temp->next->next = new;	
			return;
		}
		
        temp = temp->next;
    }


    // add to end
    temp->next = malloc(sizeof(node_t));
    temp->next->id = newId;
    temp->next->line = line;
    enqueue(&(temp->next->lines), line);
    temp->next->next = NULL;

}

void print_list(list_t* list) {
    node_t * temp;
    temp = list->head;
	
	    printf("%-20s%s\n", "IDs", "Lines");
	    while (temp->next != NULL) {
		printf("%-20s", temp->next->id);
		print_queue(&(temp->next->lines));
			temp = temp->next;
	    }

}


