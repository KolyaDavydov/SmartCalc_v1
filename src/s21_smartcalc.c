
#include "s21_smartcalc.h"

int calc(char *str, double *result, double x_val) {
  // char str[] = "10-(sin(-4)+5)+(4-2.345)";


  
  stack_t *stack = NULL;
  
  int error = check_formula(str);
  if (error == OK) error = expression_to_list(str, &stack, x_val);
  if (error == OK) {

    stack_t *polish_notation = NULL;
    error = to_polish_notation(stack, &polish_notation);
    if(error == OK) {
      
      *result = calculation(&polish_notation, &error);
      // printf("result = %f\n", *result);
    }
    del_stack(&polish_notation);
  }
  del_stack(&stack);
  return error;
}

/**
 * @brief преобразует стэк с обычной записью в стэк обратной польской нотацией
 *
 * @param stack стэк с обычной записью лексем
 * 
 * @param polish_notation стэк лексем обратной польской нотации
 *
 * @returns номер ошибки, OK или ERR
*/
int to_polish_notation(stack_t *stack, stack_t **polish_notation) {
  int error = OK;
  stack_t *tmp = {0}; // вспомогательный стэк
  
  while (stack && error != ERR) {
    if (peek_type(stack) != CloseBrace) {
      if (peek_type(stack) == Num || peek_type(stack) == X) {
        push(polish_notation, stack->value, stack->priority, peek_type(stack));
      } else {
        while (1) {
          if ((more_priority(tmp, stack->priority)) || peek_type(stack) == OpenBrace) {
            push(&tmp, stack->value, stack->priority, peek_type(stack));
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
        if (!tmp->next && tmp->type != OpenBrace) {
          error = ERR;
          break;
        }
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
    return error;
}

/**
 * @brief преобразует выражение-строку в "стэк"
 *
 * @param str выражение строка
 * 
 * @param stack адрес верхнего элемента стэка
 * 
 * @param x_val значение поля 'x' в калькуляторе
 *
 * @returns номер ошибки, OK или ERR
*/
int expression_to_list(char *str, stack_t **stack, double x_val) {
  int error = OK;
  int brace = 0;
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
      } else if (*str == 'X') {
        // push(stack, 0, 0, X);
        push(stack, x_val, 0, Num);
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
        brace++;
        push(stack, 0, 0, OpenBrace);
      } else if (*str == ')') {
        brace--;
        push(stack, 0, 0, CloseBrace);
      } else if (*str == '*') {
        push(stack, 0, 2, Mult);
      } else if (*str == '/') {
        push(stack, 0, 2, Div);
      } else if (*str == '%') {
        push(stack, 0, 2, Mod);
      } else if (*str == '^') {
        push(stack, 0, 3, Pow);
      } else if (strncmp(str, "sin", 3) == 0) { // sin
        push(stack, 0, 4, Sin);
        str += 2, i += 2;
      } else if (strncmp(str, "asin", 4) == 0) { // asin
        push(stack, 0, 4, Asin);
        str += 3, i += 3;
      } else if (strncmp(str, "cos", 3) == 0) { // cos
        push(stack, 0, 4, Cos);
        str += 2, i += 2;
      } else if (strncmp(str, "acos", 4) == 0) { // acos
        push(stack, 0, 4, Acos);
        str += 3, i += 3;
      } else if (strncmp(str, "tan", 3) == 0) { // tan
        push(stack, 0, 4, Tan);
        str += 2, i += 2;
      } else if (strncmp(str, "atan", 4) == 0) { // atan
        push(stack, 0, 4, Atan);
        str += 3, i += 3;
      } else if (strncmp(str, "sqrt", 4) == 0) { // sqrt
        push(stack, 0, 4, Sqrt);
        str += 3, i += 3;
      } else if (strncmp(str, "ln", 2) == 0) { // ln
        push(stack, 0, 4, Ln);
        str++, i ++;
      } else if (strncmp(str, "log", 3) == 0) { // log
        push(stack, 0, 4, Log);
        str += 2, i += 2;
      } else {
        error = ERR;
        break;
      }
      if (brace < 0) {
        error = ERR;
        break;
      }
    }
  }
  
  if (brace != 0) error = ERR;
  if (error == OK) {
    *stack = reverse(stack);
  }
  return error;
}

/**
 * @brief возвращает тип лексемы переданного элемента стэка
 * 
 * @param stack адрес верхнего элемента стэка
 *
 * @returns тип переданной лексемы преобрахованной к int
*/
int peek_type(stack_t *stack) { 
  return stack->type;
}

/**
 * @brief помещает элемент в стэк
 *
 * @param element адрес текущего верхнего элемента стека
 * 
 * @param value значение помещаемой лексемы, если не число, то 0
 * 
 * @param priority приоретет помещаемой лексемы
 * 
 * @param type тип помещаемой лексемы
*/
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

/**
 * @brief удалает верхний элемент стэка и меняет адрес на нижележащий
 *
 * @param element адрес удаляемого верхнего элемента стека
*/
void pop(stack_t **top_element) {
  if (*top_element != NULL) {
    stack_t *tmp = (*top_element)->next;
    free(*top_element);
    *top_element = tmp;
  }
}

/**
 * @brief меняет стэк наоборот и самый нижний элемент становится верхним
 * 
 * @param stack адрес верхнего элемента стэка до разворота
 *
 * @returns адрес развернутого стэка
*/
stack_t *reverse(stack_t **stack) {
  stack_t *new_stack = NULL;
  while (*stack != NULL) {
    push(&new_stack, (*stack)->value, (*stack)->priority, (*stack)->type);
    pop(stack);
  }
  return new_stack;
}

/**
 * @brief сравнение приоритетов
 * 
 * @param stack стэк с которым сравниваем
 * 
 * @param priority значение приоритета другой лексемы
 *
 * @returns 1 - если приоритет priority выше, 0 - в противном случае
*/
int more_priority(stack_t *stack, int priority) {
  int priority_right = 0;
  if (stack != NULL) {
    if (priority > stack->priority) {
      priority_right = 1;
    }
  } else {
    priority_right = 1;
  }
  return priority_right;
}

/**
 * @brief полностью удаляет и освобождает память от стэка
 * 
 * @param stack адрес верхнего элемента стэка
*/
void del_stack(stack_t **stack) {
  while (*stack != NULL) {
    stack_t *tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);
  }
}

/**
 * @brief вычисляет значение выражение в обратной польской нотации
 * результат в итоге храниться 
 * 
 * @param stack адрес верхнего элемента стэка
*/
double calculation(stack_t **stack, int *error) {
  // print_stack(*stack);
  double result = 0;
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
      if (peek_type(tmp3) >= 15 && peek_type(tmp3) <= 20) {
        arithmetic_calc(stack, tmp1, tmp2, tmp3, error);
      } else {
        function_calc(stack, tmp2, tmp3);
      }
    } else {
      function_calc(stack, tmp1, tmp2);
    }
  }
  result = (*stack)->value;
  del_stack(stack);
  return result;
}

/**
 * @brief выполнение арифметической операции польской нотации
 * 
 * @param stack адрес верхнего элемента стэка
 * 
 * @param tmp1 лексема - число которое находится на два выше
 * чем первая арифметическая операция
 * 
 * @param tmp2 лексема - число которое находится над 
 * высшей арифметической операцией
 * 
 * @param tmp3 лексема - самая верхняя арифметическая операция
*/
void arithmetic_calc(stack_t **stack, stack_t *tmp1, stack_t *tmp2,
                      stack_t *tmp3, int * error) {
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
    if(b == 0.0) {
      *error = ERR_DIV_ZERO;
    } else {
      num_stack = a / b;
    }
  } else if (peek_type(tmp3) == Pow) {
    num_stack = pow(a, b);
  } else if (peek_type(tmp3) == Mod) {
    num_stack = fmod(a, b);
  }
  tmp1->priority = 0;
  tmp1->type = Num;
  tmp1->value = num_stack;

  del_averege_element(stack, tmp3);
  del_averege_element(stack, tmp2);
}

/**
 * @brief выполнение тригонометрические и унарные операции польской нотации
 * 
 * @param stack адрес верхнего элемента стэка
 * 
 * @param tmp2 лексема - число которое находится над 
 * высшей тригонометрической лексемой или унарной
 * 
 * @param tmp3 лексема - самая верхняя тригонометрия или унарный
*/
void function_calc(stack_t **stack, stack_t *tmp2, stack_t *tmp3) {
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
  del_averege_element(stack, tmp3);
}

/**
 * @brief удаляет определенный элемент стека
 * 
 * @param result адрес верхнего элемента стэка
 * 
 * @param tmp элемент который необходимо удалить из стэка result
*/
void del_averege_element(stack_t **result, stack_t *tmp) {
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

/**
 * @brief проверяет формулу на корректность написания
 * 
 * @param str формула
 * 
 * @returns номер ошибки, OK или ERR 
*/
int check_formula(char *str) {
  int error = OK;
  int i = 0;
  int point = 0;
  int len = strlen(str);
  if (len != 0) {
    if (str[0] == '^' || str[0] == '.' || str[0] == '/' || str[0] == '*' ||
        str[0] == ')' || str[i] == '%') {
      error = ERR;
    } else {
      int bracket = 0;
      while (str[i] != '\0') {
        if ((str[i] == '*' || str[i] == '.' || str[i] == '^' ||
             str[i] == '%' || str[i] == '/') &&
            ((str[i + 1] >= 41 && str[i + 1] <= 47) || str[i + 1] == '^' ||
             str[i + 1] == '%')) {
          if ((str[i] != ')' && str[i - 1] != ')') ||
              (str[i] != ')' && str[i + 1] != ')')) {
            error = ERR;
            break;
          }
        } else if (str[i] == '(' &&
                   (str[i + 1] == ')' || str[i + 1] == '*' ||
                    str[i + 1] == '%' || str[i + 1] == '^' ||
                   str[i + 1] == '.' || str[i + 1] == '/')) {
          error = ERR;
          break;
        } else if (str[i] == '*' || str[i] == '+' || str[i] == '/' ||
                   str[i] == '-') {
          point = 0;
        } else if (str[i] == '.' && point == 0) {
          point++;
          if (point > 1) {
            error = ERR;
            break;
          }
        } else if (str[i] == '(') {
          bracket++;
        } else if (str[i] == ')') {
          if (bracket > 0) {
            bracket--;
          } else {
            break;
          }
        } else if (str[i] == '%' && ((str[i + 1] != '(') &&
                  (str[i + 1] < '0' && str[i + 1] > '9'))) {
          error = ERR;
          break;
        }
        i++;
        if (i == len && bracket == 0) {
          if ((str[i - 1] >= '0' && str[i - 1] <= '9') ||
              str[i - 1] == ')' || str[i - 1] == 'X') {
            error = 0;
          }
        }
      }
    }
  }
  return error;
}


// void print_stack(stack_t *list) {
//   printf("- * - * -\n");
//   char ch = '0';
//   for (stack_t *p = list; p != NULL; p = p->next) {

//     if (p->type == OpenBrace) ch = '(';
//     else if (p->type == CloseBrace) ch = ')';
//     else if (p->type == Sin) ch = 's';
//     else if (p->type == Cos) ch = 'c';
//     else if (p->type == Tan) ch = 't';
//     else if (p->type == Asin) ch = 'S';
//     else if (p->type == Acos) ch = 'C';
//     else if (p->type == Atan) ch = 'T';
//     else if (p->type == Sqrt) ch = 'q';
//     else if (p->type == Ln) ch = 'l';
//     else if (p->type == Log) ch = 'L';
//     else if (p->type == UnMinus) ch = 'M';
//     else if (p->type == UnPlus) ch = 'P';
//     else if (p->type == Mod) ch = 'm';
//     else if (p->type == Pow) ch = '^';
//     else if (p->type == Plus) ch = '+';
//     else if (p->type == Minus) ch = '-';
//     else if (p->type == Mult) ch = '*';
//     else if (p->type == Div) ch = '/';
//     else if (p->type == Num) ch = ' ';

//     printf("value - %f %c\n", p->value, ch);

//   }
//   printf("- * - * -\n");
// }