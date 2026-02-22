#include <stdio.h>
#include "list.h"

int main(){
    toggle_debug_mode(Debug_On);

    Queue *box = create_queue(float);

    push_queue(box, 10.10f);
    push_queue(box, 10.5f);
    float x = front_queue(box, float);
    pop_queue(box);

    float y = front_queue(box, float);
    unsigned int IEEE754  = front_queue(box, unsigned int);
    
    printf("%f %f %x\n", x, y, IEEE754);
    
    printf("Queue size : %d\n", (int)size_queue(box));

    push_queue(box, 100);
    printf("Queue size : %d\n", (int)size_queue(box));
    clear_queue(box);
    pop_queue(box); // Testing error handling

    Stack *s = create_stack(char*);

    push_stack(s, (char*)"HEllo");
    push_stack(s, (char*)"Hi");
    push_stack(s, (char*)"Hola");

    printf("Stack size : %d\n", (int)size_stack(s));

    while(!empty_stack(s)){
        printf("%s\n", top_stack(s, char*));
        pop_stack(s);
    }    
    
    printf("Queue size : %d\n", (int)size_queue(box));
    printf("Stack size : %d\n", (int)size_stack(s));
    
    destroy_queue(box);
    destroy_stack(s);

    // Does Not Exist
   // printf("Queue size : %d", (int)size_queue(box));
    //printf("Stack size : %d", (int)size_stack(s));
    
    return 0;
}
