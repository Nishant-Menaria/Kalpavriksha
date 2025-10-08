#include <stdio.h>
#include<stdlib.h>

int operandStack[100];
char operatorStack[100];

int g_operandTop = -1;
int g_operatorTop = -1;

void performComputation();
int getPrecedence(char val);
void pushOperand(int val);
void pushOperator(char val);
int popOperand();
char popOperator();
char getTopOperator();
int evaluateExpression(char *exp, int size);

int main()
{
    char exp[100];
    printf("Enter your expression :");
    fgets(exp, sizeof(exp), stdin);
    int i = 0;
    while (exp[i] != '\0')
    {
        i++;
    }
    int result = evaluateExpression(exp, i - 1);
    printf("%d", result);
    return 0;
}


void performComputation()
{
    char topOperator = getTopOperator();
    int rightOperand = popOperand();
    int leftOperand = popOperand();
    int result = 0;
    if (topOperator == '+')
    {
        result = leftOperand + rightOperand;
    }
    else if (topOperator == '-')
    {
        result = leftOperand - rightOperand;
    }
    else if (topOperator == '*')
    {
        result = leftOperand * rightOperand;
    }
    else if (topOperator == '/')
    {
        if (rightOperand == 0)
        {
            printf("dividing by zero");
            return ;
        }
        result = leftOperand / rightOperand;
    }
    popOperator();
    pushOperand(result);
}

int getPrecedence(char val)
{
    if (val == '/' || val == '*')
        return 2;
    else if (val == '+' || val == '-')
        return 1;

    return 0;
}

void pushOperand(int val)
{
    if (g_operandTop == 100)
    {
        printf("operand Stack overflow");
        return;
    }
    operandStack[++g_operandTop] = val;
}

void pushOperator(char val)
{
    if (g_operatorTop == 100)
    {
        printf("operator stack overflow");
        return;
    }
    operatorStack[++g_operatorTop] = val;
}

int popOperand()
{
    if (g_operandTop == -1)
    {
        printf("operand stack underflow");
        exit(0);
    }
    return operandStack[g_operandTop--];
}

char popOperator()
{
    if (g_operatorTop == -1)
    {
        printf("operator stack underflow");
        exit(0);
    }
    return operatorStack[g_operatorTop--];
}
char getTopOperator()
{
    if (g_operatorTop == -1)
        return '0';
    return operatorStack[g_operatorTop];
}

int evaluateExpression(char *exp, int size)
{
    int i = 0;
    while (i < size)
    {
        if (exp[i] == ' ')
        {
            i++;
            continue;
        }
        if (exp[i] >= '0' && exp[i] <= '9')
        {
            int val = 0;
            while (exp[i] >= '0' && exp[i] <= '9')
            {
                val = val * 10 + (int)(exp[i] - '0');
                i++;
            }
            pushOperand(val);
        }else if(exp[i]=='('){
            pushOperator(exp[i++]);
        }else if(exp[i]==')'){
            while(getTopOperator()!='('){
                performComputation();
            }
            popOperator();
            i++;
        }
        else if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '-')
        {
            if (g_operatorTop == -1)
            {
                pushOperator(exp[i++]);
                continue;
            }
            if (getPrecedence(getTopOperator()) < getPrecedence(exp[i]))
                pushOperator(exp[i++]);
            else
            {
                while (getPrecedence(getTopOperator()) >= getPrecedence(exp[i]))
                {
                    performComputation();
                }
                pushOperator(exp[i]);
                i++;
            }
        }
        else
        {
            printf("invalid expression");
            return 0;
        }
    }
    while (g_operatorTop != -1)
    {
        performComputation();
    }
    return operandStack[g_operandTop];
}