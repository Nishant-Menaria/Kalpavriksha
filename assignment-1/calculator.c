#include <stdio.h>
#include<stdlib.h>

int operandStack[100];
char operatorStack[100];

int g_topOfOperandStack = -1;
int g_topOfOperatorStack = -1;

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
    char expression[100];
    printf("Enter your expression :");
    fgets(expression, sizeof(expression), stdin);
    int sizeOfExpression = 0;
    while (expression[sizeOfExpression] != '\0')
    {
        sizeOfExpression++;
    }
    int result = evaluateExpression(expression, sizeOfExpression - 1);
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
    if (g_topOfOperandStack == 100)
    {
        printf("operand Stack overflow");
        return;
    }
    operandStack[++g_topOfOperandStack] = val;
}

void pushOperator(char val)
{
    if (g_topOfOperatorStack == 100)
    {
        printf("operator stack overflow");
        return;
    }
    operatorStack[++g_topOfOperatorStack] = val;
}

int popOperand()
{
    if (g_topOfOperandStack == -1)
    {
        printf("operand stack underflow");
        exit(0);
    }
    return operandStack[g_topOfOperandStack--];
}

char popOperator()
{
    if (g_topOfOperatorStack == -1)
    {
        printf("operator stack underflow");
        exit(0);
    }
    return operatorStack[g_topOfOperatorStack--];
}
char getTopOperator()
{
    if (g_topOfOperatorStack == -1)
        return '0';
    return operatorStack[g_topOfOperatorStack];
}

int evaluateExpression(char *expression, int size)
{
    int expressionIndex = 0;
    while (expressionIndex < size)
    {
        if (expression[expressionIndex] == ' ')
        {
            expressionIndex++;
            continue;
        }
        if (expression[expressionIndex] >= '0' && expression[expressionIndex] <= '9')
        {
            int val = 0;
            while (expression[expressionIndex] >= '0' && expression[expressionIndex] <= '9')
            {
                val = val * 10 + (int)(expression[expressionIndex] - '0');
                expressionIndex++;
            }
            pushOperand(val);
        }else if(expression[expressionIndex]=='('){
            pushOperator(expression[expressionIndex++]);
        }else if(expression[expressionIndex]==')'){
            while(getTopOperator()!='('){
                performComputation();
            }
            popOperator();
            expressionIndex++;
        }
        else if (expression[expressionIndex] == '*' || expression[expressionIndex] == '/' || expression[expressionIndex] == '+' || expression[expressionIndex] == '-')
        {
            if (g_topOfOperatorStack == -1)
            {
                pushOperator(expression[expressionIndex++]);
                continue;
            }
            if (getPrecedence(getTopOperator()) < getPrecedence(expression[expressionIndex]))
                pushOperator(expression[expressionIndex++]);
            else
            {
                while (getPrecedence(getTopOperator()) >= getPrecedence(expression[expressionIndex]))
                {
                    performComputation();
                }
                pushOperator(expression[expressionIndex]);
                expressionIndex++;
            }
        }
        else
        {
            printf("invalid expression");
            return 0;
        }
    }
    while (g_topOfOperatorStack != -1)
    {
        performComputation();
    }
    return operandStack[g_topOfOperandStack];
}