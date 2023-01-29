#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define OK 0
#define ERR 1


typedef enum type_t {
  Num,
  X,
  OpenBrace,
  CloseBrace,
  Sin,
  Cos,
  Tan,
  Asin,
  Acos,
  Atan,
  Sqrt,
  Ln,
  Log,
  UnPlus,
  UnMinus,
  Mod,
  Pow,
  Plus,
  Minus,
  Mult,
  Div,
}type_t;


typedef struct stack_t{
  double value;
  int priority;
  type_t type;
  struct stack_t*next;
} stack_t;

int expression_to_list(char *str, stack_t **stack);
void push(stack_t **element, double value, int priority, type_t type);
void print_stack(stack_t *list);
stack_t *reverse(stack_t **stack);
void pop(stack_t **top_element);
int to_polish_notation(stack_t *stack, stack_t **polish_notation);
int peek_type(stack_t *stack);
int more_priority(stack_t *stack, int priority);
void del_stack(stack_t **stack);
void del_averege_element(stack_t **result, stack_t *tmp);
void function_calc(stack_t **stack, stack_t *tmp2, stack_t *tmp3);
void arithmetic_calc(stack_t **stack, stack_t *tmp1, stack_t *tmp2, stack_t *tmp3);
double calculation(stack_t **stack);

#endif