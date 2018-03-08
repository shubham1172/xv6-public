#include "types.h"
#include "user.h"
#include "stack.h"

int
main(int argc, char *argv[])
{
    stack_push("hello");
    stack_push("world");
    stack_push("test");
    char* data = stack_pop();
    // print
    printf(1, "%d\n", num_nodes);
    printf(1, "%s\n", data);
    struct node* temp = TOP;
    while(temp!=0){
        printf(1,"%s\n", temp->buf);
        temp = temp->prev;
    }
    exit();
}
