
typedef enum type_t {
  
}type_t;


typedef struct StackElement {
  double value;
  int priority;
  type_t type;
  struct StackElement *next;
} StackElement;