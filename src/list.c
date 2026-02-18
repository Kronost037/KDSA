#include "list.h"

struct Node_impl {
    size_t size;
	Node* prev;
    Node* next;
    unsigned char val[];
};

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

struct List_impl {
    size_t size;
	Node *head;
	Node *tail;
};

// Primitive functions for List, Stack, Queue APIs
static bool is_empty(const List *list){
    if(list->head == NULL){
        // An invariant assertion
        if(list->tail != NULL){
            fprintf(stderr, "MEMORY CORRUPTION.\n"); // Should not happen.
            exit(EXIT_FAILURE);
        }
        return true;
    }
    return false;
}

static void push_tail(List *list, void *val, size_t size){

    if(size > list->size){
        status = status_type_mismatch;
        return;
    }
    
    Node *node = malloc(sizeof (*node) + size);
    if(node == NULL){
        status = status_memory_crash;
        return;
    }

    memcpy(node->val, val, size);
    node->size = size;
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

static void push_head(List *list, void *val, size_t size){

    if(size > list->size){
        status = status_type_mismatch;
        return;
    }
    
	Node *node = malloc(sizeof (*node) + size);
    if(node == NULL){
        status = status_memory_crash;
        return;
    }
    
    memcpy(node->val, val, size);
    node->size = size;
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

static void view_head(const List *list, void *out){
    if(is_empty(list)){
        status = status_illegal_access;
        return;
    }

    memcpy(out, list->head->val, list->head->size);
    status_clear();
}

static void view_tail(const List *list, void *out){
    if(is_empty(list)){
        status = status_illegal_access;
        return;
    }

    memcpy(out, list->tail->val, list->tail->size);
    status_clear();
}

// Removing / Clearing list and in extension stack, queue are dependent on pop_head func.

static void clear(List *list) {
    while (!is_empty(list)) {
        pop_head(list);
    }
}

static List *create(size_t size) {
    List *list = malloc(sizeof(*list));
    if (!list) {
        status = status_memory_crash;
        return NULL;
    }
    
    *list = (List){0};
    list->size = size;
    status_clear();
    return list;
}


// Linked List

List *(create_list)(size_t size, int LINE){

    List *list = create(size);

    if(Debug_Switch == Debug_On && status_err()) {
        log_error(LINE, __func__, __FILE__);
    }

    return list;
}

void (push_list_head)(List *list, void *val, size_t size, int LINE){
    push_head(list, val, size);

    if(Debug_Switch == Debug_On && status_err()) {
        log_error(LINE, __func__, __FILE__);
    }
}

void (push_list_tail)(List *list, void *val, size_t size, int LINE){
    push_tail(list, val, size);

    if(Debug_Switch == Debug_On && status_err()) {
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_list_head)(List *list, int LINE){
    pop_head(list);

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_list_tail)(List *list, int LINE){
    pop_tail(list);

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

void (view_list_head)(const List *list, void *out, int LINE){
    view_head(list, out);

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

void (view_list_tail)(const List *list, void *out, int LINE){
    view_tail(list, out);
    
    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

bool empty_list(const List *list){
    return is_empty(list);
}

void clear_list(List *list){
    clear(list);
}


struct Queue_impl {
	List *list;
};
    
// Queue Functions (Enters at tail and leaves at head)

Queue *(create_queue)(size_t size, int LINE){
    Queue *line = malloc(sizeof (*line));

    if(line == NULL){
        status = status_memory_crash;
        if(Debug_Switch == Debug_On) {
            log_error(LINE, __func__, __FILE__);
        }
        return NULL;
    }
    
    line->list = create(size);

    if(line->list == NULL){
        if(Debug_Switch == Debug_On) {
            log_error(LINE, __func__, __FILE__);
        }
        free(line);      
        return NULL;
    }

    return line;
}

void (push_queue)(Queue *line, void *val, size_t size, int LINE){
    push_tail(line->list, val, size);	
    
    if(Debug_Switch == Debug_On && status_err()) {
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_queue)(Queue *line, int LINE){
	pop_head(line->list);
    
    if(Debug_Switch == Debug_On && status_err()) {
        log_error(LINE, __func__, __FILE__);
    }
}

bool empty_queue(const Queue *line){
    return is_empty(line->list);
}

void (front_queue)(const Queue *line, void *out, int LINE){
    view_head(line->list, out);

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

void clear_queue(Queue *line){
    clear(line->list);
}

struct Stack_impl {
	List *list;
};

// Stack Functions (Enters at head and also leaves at head)

Stack *(create_stack)(size_t size, int LINE){
    Stack *box = malloc(sizeof(*box));

    if (box == NULL) {
        status = status_memory_crash;
        if (Debug_Switch == Debug_On){
            log_error(LINE, __func__, __FILE__);
        }
        return NULL;
    }

    box->list = create(size);
    
    if(box->list == NULL) {
        if(Debug_Switch == Debug_On){
            log_error(LINE, __func__, __FILE__);
        }
        free(box);
        return NULL;
    }
    
    return box;
}

void (push_stack)(Stack *box, void *val, size_t size, int LINE){
	push_head(box->list, val, size);	

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

void (pop_stack)(Stack *box, int LINE){
	pop_head(box->list);

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

bool empty_stack(const Stack *box){
    return is_empty(box->list);
}

void (top_stack)(const Stack *box, void *out, int LINE){
    view_head(box->list, out);

    if(Debug_Switch == Debug_On && status_err()){
        log_error(LINE, __func__, __FILE__);
    }
}

void clear_stack(Stack *box){
    clear(box->list);
}
