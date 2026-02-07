#include "list.h"


inline void log_error(const int line, const char *func_name, const char* file_name){
    fprintf(stderr, "ERR: In %s Line %d: '%s' failed.\n", file_name, line, func_name);
}

// Debug info
static Debug_Mode Debug_Switch = Debug_Off;

void toggle_debug_mode(Debug_Mode mode) {
    if (mode == Debug_On) Debug_Switch = Debug_On;
    else if(mode == Debug_Off) Debug_Switch = Debug_Off;
}


_Thread_local static Status status = status_ok;

// Status functions
static inline void status_clear(void) {
    status = status_ok;
}

// Use for checking if status error occured
bool status_err(void){
    return status != status_ok;
}

Status get_status(void){
    return status;
}


// Primitive functions for List, Stack, Queue APIs
static bool is_empty(const List *list){
    if(list->head == NULL){
        assert(list->tail == NULL);
        return true;
    }
    return false;
}

static void push_tail(List *list, int val){
    
    Node *node = malloc(sizeof (*node));
    if(node == NULL){
        status = status_memory_crash;
        return;
    }
    
	node->val = val;
	node->prev = node->next = NULL;
	
	if(is_empty(list)){
		list->head = list->tail = node;
        status_clear();
		return;
	}
	
	list->tail->next = node;
	node->prev = list->tail;
	list->tail = node;

    status_clear();
}

static void push_head(List *list, int val){
    
	Node *node = malloc(sizeof (*node));
    if(node == NULL){
        status = status_memory_crash;
        return;
    }
    
	node->val = val;
	node->prev = node->next = NULL;
	
	if(is_empty(list)){
		list->head = list->tail = node;
        status_clear();
		return;
	}
	
	list->head->prev = node;
	node->next = list->head;
	list->head = node;

    status_clear();
}

static void pop_head(List *list){
	
	if(is_empty(list)) {
        status = status_out_of_bounds;
        return;
	} 

    Node *tmp = list->head;
    
	if(list->head->next == NULL){
		list->head = list->tail = NULL;
    } else {
	    list->head = list->head->next;
	    list->head->prev = NULL;
    }
    
    free(tmp);
    status_clear();
    return;
}

static void pop_tail(List *list){
	
	if(is_empty(list)) {
        status = status_out_of_bounds;
		return;
	} 

    Node *tmp = list->tail;
	if(list->tail->prev == NULL){
		list->head = list->tail = NULL;
    } else {
	    list->tail = list->tail->prev;
	    list->tail->next = NULL;
	}
    
	free(tmp);
    status_clear();
	return;
}

static int view_head(const List *list){
    if(is_empty(list)){
        status = status_illegal_access;
        return INT_MIN;  // If return is INT_MIN, check status
    }

    status_clear();
    return list->head->val;
}

static int view_tail(const List *list){
    if(is_empty(list)){
        status = status_illegal_access;
        return INT_MIN;  // If return is INT_MIN, check status
    }

    status_clear();
    return list->tail->val;
}

// Removing / Clearing list and in extension stack, queue are dependent on pop_head func.

static void remove_list(List *list) {
    while (!is_empty(list)) {
        pop_head(list);
    }
}

// Linked List
void init_list(List *list){
    *list = (List){0};
}

void (push_list_head)(List *list, int val, int LINE){
    push_head(list, val);

    if(status == status_memory_crash && Debug_Switch == Debug_On) {
        log_error(LINE, __func__, __FILE__);
    }
}

void (push_list_tail)(List *list, int val, int LINE){
    push_tail(list, val);

    if(status == status_memory_crash && Debug_Switch == Debug_On) {
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_list_head)(List *list, int LINE){
    pop_head(list);

    if(status == status_out_of_bounds && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_list_tail)(List *list, int LINE){
    pop_tail(list);

    if(status == status_out_of_bounds && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }
}

int (view_list_head)(const List *list, int LINE){
    int tmp = view_head(list);

    if(status == status_illegal_access && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }

    return tmp;
}

int (view_list_tail)(const List *list, int LINE){
    int tmp = view_tail(list);
    
    if(status == status_illegal_access && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }

    return tmp;
}

bool empty_list(const List *list){
    return is_empty(list);
}

void clear_list(List *list){
    remove_list(list);
} 
    
// Queue Functions (Enters at tail and leaves at head)

void init_queue(Queue *line){
    *line = (Queue){0};
}

void (push_queue)(Queue *line, int val, int LINE){
    push_tail(&(line->list), val);	
    
    if(status == status_memory_crash && Debug_Switch == Debug_On) {
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_queue)(Queue *line, int LINE){
	pop_head(&(line->list));
    
    if(status == status_out_of_bounds && Debug_Switch == Debug_On) {
        log_error(LINE, __func__, __FILE__);
    }
}

bool empty_queue(const Queue *line){
    return is_empty(&line->list);
}

int (front_queue)(const Queue *line, int LINE){
    int tmp =  view_head(&line->list);

    if(status == status_illegal_access && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }

    return tmp;
}

void clear_queue(Queue *line){
    remove_list(&line->list);
}

// Stack Functions (Enters at head and also leaves at head)
    
void init_stack(Stack *box){
    *box = (Stack){0};
}

void (push_stack)(Stack *box, int val, int LINE){
	push_head(&(box->list), val);	

    if(status == status_memory_crash && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_stack)(Stack *box, int LINE){
	pop_head(&(box->list));

    if(status == status_out_of_bounds && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }
}

bool empty_stack(const Stack *box){
    return is_empty(&box->list);
}

int (top_stack)(const Stack *box, int LINE){
    int tmp = view_head(&box->list);

    if(status == status_illegal_access && Debug_Switch == Debug_On){
        log_error(LINE, __func__, __FILE__);
    }

    return tmp;
}

void clear_stack(Stack *box){
    remove_list(&box->list);
}
