#include "shell.h"
#include <math.h>
#include <stdio.h>

void calc(char *value1, char *op, char *value2)
{
    double v1 = atof(value1), v2 = atof(value2);
    switch (op[0])
    {
    case '+':
        printf("%0.1f\n", v1 + v2);
        break;
    case '-':
        printf("\n%0.1f\n", v1 - v2);
        break;
    case '*':
        printf("%0.1f\n", v1 * v2);
        break;
    case '/':
        if (fabs(v2) < __FLT_EPSILON__) // quando == 0
        {
            printf("noooooooo, divido por 0\n");
            break;
        }
        printf("%0.1f\n", v1 / v2);
        break;
    case '^':
        printf("%0.1f\n", powf(v1, v2));
        break;

    default:
        printf("Invalid Operand");
        break;
    }
}

void bits(char *op1, char *op, char *op2)
{
  int n1 = atoi(op1);
  int n2 = atoi(op2);

  if (strcmp(op, "&") == 0)
  {
    printf("%d\n", n1 & n2);
  }
  else if (strcmp(op, "^") == 0)
  {
    printf("%d\n", n1 ^ n2);
  }
  else if (strcmp(op, "|") == 0)
  {
    printf("%d\n", n1 | n2);
  }
}
