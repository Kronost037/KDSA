// A Linked list, stack, queue Library


// Avoids header duplication
#ifndef LIST_123
#define LIST_123

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    status_type_mismatch,
} Status;

typedef struct Node_impl Node;
typedef struct List_impl List;
typedef struct Queue_impl Queue; 
typedef struct Stack_impl Stack; 


void toggle_debug_mode(Debug_Mode mode);
void log_error(int line, const char *func_name, const char *file_name);
bool status_err(void);
Status get_status(void);

/*
||  Function declarations / Macros
||  Macros exapnd to functions of the same name with an added argument of __LINE__, used internally when DEBUG is defined, for better error logs
*/

// Linked list functions
List *(create_list)(size_t size, int LINE);
void (push_list_head)(List *list, void *val, size_t size, int LINE);
void (push_list_tail)(List *list, void *val, size_t size, int LINE);
void (view_list_head)(const List *list, void *out, int LINE);
void (view_list_tail)(const List *list, void *out, int LINE);
void (pop_list_head)(List *list, int LINE);
void (pop_list_tail)(List *list, int LINE);
bool empty_list(const List *list);
void clear_list(List *list);

// Linked list macros
#define create_list(type) (create_list)(sizeof (type), __LINE__) 
#define push_list_head(list, val) do { __typeof__(val) _tmpKDSA = (val); (push_list_head)((list), &_tmpKDSA, sizeof (_tmpKDSA), __LINE__); } while(0)
#define push_list_tail(list, val) do { __typeof__(val) _tmpKDSA = (val); (push_list_tail)((list), &_tmpKDSA, sizeof (_tmpKDSA), __LINE__); } while(0)
#define view_list_head(list, type) ({ type _tmpKDSA; (view_list_head)((list), &_tmpKDSA, __LINE__); _tmpKDSA;})
#define view_list_tail(list, type) ({ type _tmpKDSA; (view_list_tail)((list), &_tmpKDSA, __LINE__); _tmpKDSA;})
#define pop_list_head(list) (pop_list_head)((list), __LINE__)
#define pop_list_tail(list) (pop_list_tail)((list), __LINE__)

// stack functions
Stack *(create_stack)(size_t size, int LINE);
void (top_stack)(const Stack *box, void *out, int LINE);
void (push_stack)(Stack *box, void *val, size_t size, int LINE);
void (pop_stack)(Stack *box, int LINE);
bool empty_stack(const Stack *box);
void clear_stack(Stack *box);

// stack macros
#define create_stack(type) (create_stack)(sizeof (type), __LINE__) 
#define top_stack(box, type) ({ type _tmpKDSA; (top_stack)((box), &_tmpKDSA, __LINE__); _tmpKDSA;})
#define push_stack(box, val) do { __typeof__(val) _tmpKDSA = (val); (push_stack)((box), &_tmpKDSA, sizeof (_tmpKDSA), __LINE__); } while (0)
#define pop_stack(box) (pop_stack)((box), __LINE__)


// queue functions
Queue *(create_queue)(size_t size, int LINE);
void (push_queue)(Queue *line, void *val, size_t size, int LINE);
void (front_queue)(const Queue *line, void *out, int LINE);
void (pop_queue)(Queue *line, int LINE);
bool empty_queue(const Queue *line);
void clear_queue(Queue *line);

// queue macros
#define create_queue(type) (create_queue)(sizeof (type), __LINE__) 
#define front_queue(line, type) ({ type _tmpKDSA; (front_queue)((line), &_tmpKDSA, __LINE__); _tmpKDSA;})
#define push_queue(line, val) do { __typeof__(val) _tmpKDSA = (val); (push_queue)((line), &_tmpKDSA, sizeof (_tmpKDSA), __LINE__); } while(0)
#define pop_queue(line) (pop_queue)((line), __LINE__)

#endif // LIST_123
