// Cross Reference Generator
// Troy Veldhuizen
// queue.c

typedef struct nodeq {
    int line;
    struct nodeq * next;
} node_q;



typedef struct queue {
    node_q * head;
} queue_t;

void enqueue(queue_t* queue, int line){
	node_q * current = queue->head;


	if(current == NULL){
		
		node_q *new1 = malloc(sizeof(node_q));
		queue->head = new1;

		node_q *new2 = malloc(sizeof(node_q));
		new2->line = line;
		queue->head->next = new2;
		return;
	} 

	//loop to base of queue
	while(current->next != NULL){
		//check for duplicates
		if(current->next->line == line){ 
			return;
		}
	
		current = current->next;
	}
	
	current->next = malloc(sizeof(node_q));
    	current->next->line = line;
    	current->next->next = NULL;
	return;
}

void print_queue(queue_t * queue){
	
    node_q * current = queue->head;
   

    while (current->next != NULL) {
	printf("%-3d ", current->next->line );
	current = current->next;
    }

    printf("\n");
}
