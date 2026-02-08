// A Linked list, Stack, Queue Library


// Avoids header duplication
#ifndef LIST_123
#define LIST_123

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>


// Debug_mode toggle 
typedef enum {
    Debug_On = 1,
    Debug_Off
} Debug_Mode;


// Custom simple errno
typedef enum {
    status_ok = 1,
    status_out_of_bounds,    // Trying to access unasigned memory
    status_memory_crash,     // Malloc failed
    status_illegal_access,   // Trying to delete/free unassigned memory
} Status;


typedef struct Node Node;
typedef struct List List;
typedef struct Queue Queue; 
typedef struct Stack Stack; 


void toggle_debug_mode(Debug_Mode mode);
void log_error(int line, const char *func_name, const char *file_name);
bool status_err(void);
Status get_status(void);

/*
||  Function declarations / Macros
||  Macros exapnd to functions of the same name with an added argument of __LINE__, used internally when DEBUG is defined, for better error logs
*/

// Linked List functions
void init_list(List *list);
void (push_list_head)(List *list, int val, int LINE);
void (push_list_tail)(List *list, int val, int LINE);
int (view_list_head)(const List *list, int LINE);
int (view_list_tail)(const List *list, int LINE);
void (pop_list_head)(List *list, int LINE);
void (pop_list_tail)(List *list, int LINE);
bool empty_list(const List *list);
void clear_list(List *list);

// Linked List macros
#define push_list_head(list, val) (push_list_head)((list), (val), __LINE__)
#define push_list_tail(list, val) (push_list_tail)((list), (val), __LINE__)
#define view_list_head(list) (view_list_head)((list), __LINE__)
#define view_list_tail(list) (view_list_tail)((list), __LINE__)
#define pop_list_head(list) (pop_list_head)((list), __LINE__)
#define pop_list_tail(list) (pop_list_tail)((list), __LINE__)

// Stack functions
void init_stack(Stack *box);
int (top_stack)(const Stack *box, int LINE);
void (push_stack)(Stack *box, int val, int LINE);
void (pop_stack)(Stack *box, int LINE);
bool empty_stack(const Stack *box);
void clear_stack(Stack *box);

// Stack macros
#define top_stack(box) (top_stack)((box), __LINE__)
#define push_stack(box, val) (push_stack)((box), (val), __LINE__)
#define pop_stack(box) (pop_stack)((box), __LINE__)


// Queue functions
void init_queue(Queue *line);
void (push_queue)(Queue *line, int val, int LINE);
int (front_queue)(const Queue *line, int LINE);
void (pop_queue)(Queue *line, int LINE);
bool empty_queue(const Queue *line);
void clear_queue(Queue *line);

// Queue macros
#define front_queue(line) (front_queue)((line), __LINE__)
#define push_queue(line, val) (push_queue)((line), (val), __LINE__)
#define pop_queue(line) (pop_queue)((line), __LINE__)

#endif // LIST_123
