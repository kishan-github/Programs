#include <stdio.h>
#include <stdbool.h>

#define MAX 50

char stack_arr[MAX] = {'\0'};
int stack_pos = -1;

void addToStack(char chr)
{
    if(stack_pos >= MAX)
    {
        printf("\nOverflow.");
        return;
    }
    
    stack_arr[++stack_pos] = chr;
}

void removeFromStack()
{
    if(stack_pos < 0)
    {
        printf("\nUnderflow.");
        return;
    }
    stack_arr[stack_pos] = '\0';
    --stack_pos;
}

bool isOpeningParanthesis(char str)
{
	switch(str)
	{
		case '{':
		case '(':
		case '[':
			return true;
		default:
			return false;
	}
}

bool isClosingParanthesis(char str)
{
	switch(str)
	{
		case '}':
		case ')':
		case ']':
			return true;
		default:
			return false;
	}
}

char mapClosingToOpeningParanthesis(char str)
{
	switch(str)
	{
		case '}': 
			return '{';
		case ']': 
			return '[';
		case ')': 
			return '(';
		default:
			printf("Invalid paranthesis received.\n");
			return '\0';
	}
}

bool checkString(char *str)
{
	int i = 0;
	
	while(str[i] != '\0')
	{
		if(isOpeningParanthesis(str[i]))
			addToStack(str[i]);
		else if(isClosingParanthesis(str[i]))
		{
			if((stack_pos != -1) && (stack_arr[stack_pos] == mapClosingToOpeningParanthesis(str[i])))
				removeFromStack();
			else
				return false;
		}
		else
		{
			printf("Not a valid paranthesis.\n");
			return false;
		}
		i++;
	}
	
	if(stack_pos == -1)
		return true;
	else
		return false;
}

int main() {
	
	if(checkString("(([]{}([{}])))"))
		printf("Balanced.\n");
	else
		printf("Un-Balanced.\n");
	
	return 0;
}