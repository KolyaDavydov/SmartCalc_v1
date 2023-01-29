
#include "s21_smartcalc.h"
#include <math.h>

int main() {
  char str[] = "1+((0-6)*8)(4)";


  printf("str - %s", str);
  stack_t *stack = NULL;
  int error = expression_to_list(str, &stack);
  printf("error %d\n", error);
  print(stack);
  
  if (error == OK) {
    stack_t *polish_notation = NULL;
    to_polish_notation(stack, &polish_notation);

    print(polish_notation);

    Calc(&polish_notation);
    double result = polish_notation->value;
    printf("result = %f", result);

    del_stack(&polish_notation);
  }

  del_stack(&stack);

  return 0;
}

void to_polish_notation(stack_t *stack, stack_t **polish_notation) {
  stack_t *tmp = {0};
  
  while (stack) {
    if (peek_type(stack) != CloseBrace) {
      if (peek_type(stack) == Num || peek_type(stack) == X) {
        push(polish_notation, stack->value, stack->priority, peek_type(stack));
      } else {
        while (1) {
          if ((CheckSupport(tmp, stack->priority)) || peek_type(stack) == OpenBrace) {
            push(&tmp, stack->value, stack->priority,
                      peek_type(stack));
            break;
          } else {
            push(polish_notation, tmp->value, tmp->priority, tmp->type);
            pop(&tmp);
          }
        }
      }
    } else {
      while (tmp->type != OpenBrace) {
        push(polish_notation, tmp->value, tmp->priority, tmp->type);
        pop(&tmp);
      }
      pop(&tmp);
    }
    stack = stack->next;
  }
  while (tmp) {
    push(polish_notation, tmp->value, tmp->priority, tmp->type);
    pop(&tmp);
  }
    *polish_notation = reverse(polish_notation);
}

/**
 * @brief преобразует выражение-строку в "стэк"
 *
 * @param str выражение строка
 * 
 * @param stack адрес верхнего элемента стэка
 *
 * @returns номер ошибки, OK или ERR
*/
int expression_to_list(char *str, stack_t **stack) {
  int error = OK;

  int expression_len = strlen(str);

  if (str[0] == ')' || str[0] == '^' || str[0] == '*' || str[0] == '/' || str[0] == '.') {
    error = ERR;
  } else {
    for(int i = 0, j = 0; i < expression_len; i++, str++, j++) {
      int num_char = 0;
      
      if (*str >= '0' && *str <= '9') {
        char *end_num_str = str;
        double d = strtod(str, &end_num_str);
        num_char = end_num_str - str - 1;
        str += num_char;
        i += num_char;
        push(stack, d, 0, Num);
      } else if (*str == 'x') {
        push(stack, 0, 0, X);
      } else if (*str == '+') {
        if (i == 0) {
          push(stack, 0, 1, UnPlus);
        } else if (*(str - 1) == '(') {
            push(stack, 0, 1, UnPlus);
        } else if (*(str - 1) == ')' || (*(str - 1) >= '0' && *(str - 1) <= '9')){
          push(stack, 0, 1, Plus);
        } else {
          error = ERR;
        }
      } else if (*str == '-') {
        if (i == 0) {
          push(stack, 0, 1, UnMinus);
        } else if (*(str - 1) == '(') {
            push(stack, 0, 1, UnMinus);
        } else if (*(str - 1) == ')' || (*(str - 1) >= '0' && *(str - 1) <= '9')){
          push(stack, 0, 1, Minus);
        } else {
          error = ERR;
        }
      } else if (*str == '(') {
        push(stack, 0, 0, OpenBrace);
      } else if (*str == ')') {
        push(stack, 0, 0, CloseBrace);
      } else if (*str == '*') {
        push(stack, 0, 2, Mult);
      } else if (*str == '/') {
        push(stack, 0, 2, Div);
      } else if (*str == 'm') {
        push(stack, 0, 2, Mod);
      } else if (*str == '^') {
        push(stack, 0, 3, Pow);
      } else if (*str == 's') { // sin
        push(stack, 0, 4, Sin);
      } else if (*str == 'S') { // asin
        push(stack, 0, 4, Asin);
      } else if (*str == 'c') { // cos
        push(stack, 0, 4, Cos);
      } else if (*str == 'C') { // acos
        push(stack, 0, 4, Acos);
      } else if (*str == 't') { // tan
        push(stack, 0, 4, Tan);
      } else if (*str == 'T') { // atan
        push(stack, 0, 4, Atan);
      } else if (*str == 'q') { // sqrt
        push(stack, 0, 4, Sqrt);
      } else if (*str == 'l') { // ln
        push(stack, 0, 4, Ln);
      } else if (*str == 'L') { // log
        push(stack, 0, 4, Log);
      } else {
        error = ERR;
        break;
      }
    }
  }
  print(*stack);

  if (error == OK) {
    *stack = reverse(stack);
  }
    print(*stack);
  return error;
}

int peek_type(stack_t *list) { 
  return list->type;
}

void push(stack_t **element, double value, int priority, type_t type) {

  stack_t *new_element = calloc(1, sizeof(stack_t));
  if (new_element != NULL) {
    
    new_element->value = value;
    new_element->priority = priority;
    new_element->type = type;
    new_element->next = *element;
    *element = new_element;
  }
}

void pop(stack_t **top_element) {
  if (*top_element != NULL) {
    stack_t *tmp = (*top_element)->next;
    free(*top_element);
    *top_element = tmp;
  }
}

stack_t *reverse(stack_t **stack) {
  stack_t *new_stack = NULL;
  while (*stack != NULL) {
    push(&new_stack, (*stack)->value, (*stack)->priority, (*stack)->type);
    pop(stack);
  }
  return new_stack;
}

void print(stack_t *list) {
  printf("- * - * -\n");
  for (stack_t *p = list; p != NULL; p = p->next) {
    printf("value - %f ", p->value);
    printf("type - %d\n ", (int)p->type);
  }
  printf("- * - * -\n");
}

int CheckSupport(stack_t *help_stack, int priority) {
  int num_stack = 0;
  if (help_stack != NULL) {
    if (priority > help_stack->priority) {
      num_stack = 1;
    }
  } else {
    num_stack = 1;
  }
  return num_stack;
}

void del_stack(stack_t **stack) {
  while (*stack != NULL) {
    stack_t *tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);
  }
}




void Calc(stack_t **stack) {
  while ((*stack)->next != NULL) {
    stack_t *tmp1 = {0}, *tmp2 = {0}, *tmp3 = {0};
    tmp1 = *stack;
    tmp2 = tmp1->next;
    if (tmp2->next != NULL) {
      tmp3 = tmp2->next;
    }
    if (tmp2->type == Num) {
      while (!tmp3->priority) {
        tmp1 = tmp2;
        tmp2 = tmp1->next;
        tmp3 = tmp2->next;
      }
      if (peek_type(tmp3) >= 16 && peek_type(tmp3) <= 21) {
        calculate_lexems(stack, tmp1, tmp2, tmp3);
      } else {
        calculate_functions(stack, tmp2, tmp3);
      }
    } else {
      calculate_functions2(stack, tmp1, tmp2);
    }
  }
}

void calculate_lexems(stack_t **stack, stack_t *tmp1, stack_t *tmp2,
                      stack_t *tmp3) {
  double num_stack = 0;
  double a = tmp1->value;
  double b = tmp2->value;
  if (peek_type(tmp3) == Plus) {
    num_stack = a + b;
  } else if (peek_type(tmp3) == Minus) {
    num_stack = a - b;
  } else if (peek_type(tmp3) == Mult) {
    num_stack = a * b;
  } else if (peek_type(tmp3) == Div) {
    num_stack = a / b;
  } else if (peek_type(tmp3) == Pow) {
    num_stack = pow(a, b);
  } else if (peek_type(tmp3) == Mod) {
    num_stack = fmod(a, b);
  }
  tmp1->priority = 0;
  tmp1->type = Num;
  tmp1->value = num_stack;
  DelStack(stack, tmp3);
  DelStack(stack, tmp2);
}

void calculate_functions(stack_t **stack, stack_t *tmp2, stack_t *tmp3) {
  double a = 0;
  double num_stack = 0;
  a = tmp2->value;
  if (peek_type(tmp3) == UnPlus) {
    num_stack = +a;
  } else if (peek_type(tmp3) == UnMinus) {
    num_stack = -a;
  } else if (peek_type(tmp3) == Sin) {
    num_stack = sin(a);
  } else if (peek_type(tmp3) == Cos) {
    num_stack = cos(a);
  } else if (peek_type(tmp3) == Tan) {
    num_stack = tan(a);
  } else if (peek_type(tmp3) == Asin) {
    num_stack = asin(a);
  } else if (peek_type(tmp3) == Acos) {
    num_stack = acos(a);
  } else if (peek_type(tmp3) == Atan) {
    num_stack = atan(a);
  } else if (peek_type(tmp3) == Ln) {
    num_stack = log(a);
  } else if (peek_type(tmp3) == Log) {
    num_stack = log10(a);
  } else if (peek_type(tmp3) == Sqrt) {
    num_stack = sqrt(a);
  }
  tmp2->priority = 0;
  tmp2->type = Num;
  tmp2->value = num_stack;
  DelStack(stack, tmp3);
}

void calculate_functions2(stack_t **stack, stack_t *tmp1, stack_t *tmp2) {
  double a = 0;
  double num_stack = 0;
  a = tmp1->value;
  if (peek_type(tmp2) == UnPlus) {
    num_stack = +a;
  } else if (peek_type(tmp2) == UnMinus) {
    num_stack = -a;
  } else if (peek_type(tmp2) == Sin) {
    num_stack = sin(a);
  } else if (peek_type(tmp2) == Cos) {
    num_stack = cos(a);
  } else if (peek_type(tmp2) == Tan) {
    num_stack = tan(a);
  } else if (peek_type(tmp2) == Asin) {
    num_stack = asin(a);
  } else if (peek_type(tmp2) == Acos) {
    num_stack = acos(a);
  } else if (peek_type(tmp2) == Atan) {
    num_stack = atan(a);
  } else if (peek_type(tmp2) == Ln) {
    num_stack = log(a);
  } else if (peek_type(tmp2) == Log) {
    num_stack = log10(a);
  } else if (peek_type(tmp2) == Sqrt) {
    num_stack = sqrt(a);
  }
  tmp1->priority = 0;
  tmp1->type = Num;
  tmp1->value = num_stack;
  DelStack(stack, tmp2);
}


void DelStack(stack_t **result, stack_t *tmp) {
  stack_t *tmp_in_function = {0};
  tmp_in_function = *result;
  if (*result == tmp) {
    tmp_in_function = (*result)->next;
    free(*result);
    *result = tmp_in_function;
  } else {
    while (tmp_in_function->next != tmp) {
      tmp_in_function = tmp_in_function->next;
    }
    tmp_in_function->next = tmp->next;
    free(tmp);
  }
}



