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

    Stack *s = create_stack(char*);

    push_stack(s, (char*)"HEllo");
    push_stack(s, (char*)"Hi");
    push_stack(s, (char*)"Hola");

    while(!empty_stack(s)){
        printf("%s\n", top_stack(s, char*));
        pop_stack(s);
    }

    return 0;
}
