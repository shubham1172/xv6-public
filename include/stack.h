#include <user.h>
// stack for xv6
#define MAX_BUFF_SIZE 512
#define MAX_STACK_SIZE 20
#define NULL 0

// node definition
struct node{
    char buf[MAX_BUFF_SIZE];
    struct node* prev;
};

// top of stack
struct node* TOP;
// number of nodes
int num_nodes = 0;

struct node* stack_new_node(char* data, struct node* nodeptr){
    struct node* new_node = malloc(sizeof(struct node));
    strcpy(new_node->buf,data);
    new_node->prev = nodeptr;
    return new_node;
}

// push in stack
int stack_push(char* data){
    if(num_nodes>=MAX_STACK_SIZE) // stack overflow
        return -1;
    struct node* new_node = stack_new_node(data, TOP);
    TOP = new_node;
    num_nodes++;
    return 1;
}

// pop from stack
char* stack_pop(){
    if(num_nodes<1) // stack underflow
        return "";
    char* data = TOP->buf;
    TOP = TOP->prev;
    num_nodes--;
    return data;
}
