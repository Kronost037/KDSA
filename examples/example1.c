#include <stdio.h>
#include "list.h"

int main(){
    toggle_debug_mode(Debug_On);

    Stack box;
    init_stack(&box);

    push_stack(&box, -100);
    push_stack(&box, 00);
    push_stack(&box, INT_MIN);
    push_stack(&box, 101);
    push_stack(&box, 110);

    while(!empty_stack(&box)){
        printf("%d ", top_stack(&box));
        pop_stack(&box);
    }

    // Bad usage. Peeking can fail and print garbage value.
    printf("%d ", top_stack(&box));
    if(status_err()){
        printf("Last value is garbage.\n");
    }
    // Does nothing. Sets Status and gives err log in debug_mode
    pop_stack(&box);
    if(status_err()){
        printf("Popped nothing.\n");
    }
    
    return 0;
}
