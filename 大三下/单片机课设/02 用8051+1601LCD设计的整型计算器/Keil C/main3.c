#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char NumberStr[10] = "5+6/2+3*4";
char NumberIdx = 9;
char numbers[10] = { 0 };
int numsTop = 0;
char flags[10] = { 0 };
int flagsTop = 0;
char mid;
int flagCompare(char a, char b);

int main()
{
	int i;

	for (i = 0; i < NumberIdx; i++) {
		if (isdigit(NumberStr[i]))
		{
			numbers[numsTop++] = NumberStr[i] - '0';
			numbers[numsTop] = 0;
		}
		else {
			if (flagsTop == 0 || (flagsTop != 0 && (flagCompare(NumberStr[i], flags[flagsTop - 1]) == 1)))
			{
				flags[flagsTop++] = NumberStr[i];
				flags[flagsTop] = 0;
			}
			else {
				while (flagsTop!= 0 && (flagCompare(flags[flagsTop - 1], NumberStr[i]) >= 0))
				{
					switch (flags[flagsTop-1])
					{
					case '+':
						mid = numbers[numsTop - 1] + numbers[numsTop - 2];
						numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
						numsTop -= 1;
						numbers[numsTop - 1] = mid;
						flags[--flagsTop] = 0;
						break;
					case '-':
						mid = numbers[numsTop - 1] - numbers[numsTop - 2];
						numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
						numsTop -= 1;
						numbers[numsTop - 1] = mid;
						flags[--flagsTop] = 0;
						break;
					case '*':
						mid = numbers[numsTop - 1] * numbers[numsTop - 2];
						numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
						numsTop -= 1;
						numbers[numsTop - 1] = mid;
						flags[--flagsTop] = 0;
						break;
					case '/':
						mid = numbers[numsTop - 2] / numbers[numsTop - 1];
						numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
						numsTop -= 1;
						numbers[numsTop - 1] = mid;
						flags[--flagsTop] = 0;
						break;
					}
				}
				flags[flagsTop++] = NumberStr[i];
			}
		}
	}
	int j;
	for (j = flagsTop - 1; j >= 0; j--)
	{
		switch (flags[j])
		{
		case '+':
			mid = numbers[numsTop - 1] + numbers[numsTop - 2];
			numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
			numsTop -= 1;
			numbers[numsTop - 1] = mid;
			break;
		case '-':
			mid = numbers[numsTop - 1] - numbers[numsTop - 2];
			numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
			numsTop -= 1;
			numbers[numsTop - 1] = mid;
			break;
		case '*':
			mid = numbers[numsTop - 1] * numbers[numsTop - 2];
			numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
			numsTop -= 1;
			numbers[numsTop - 1] = mid;
			break;
		case '/':
			mid = numbers[numsTop - 2] / numbers[numsTop - 1];
			numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
			numsTop -= 1;
			numbers[numsTop - 1] = mid;
			break;
		}
	}
	printf("%d", numbers[0]);
	return 0;
}

int flagCompare(char a, char b)
{
	switch (a)
	{
	case '*':
		if (b == '+' || b == '-') return 1;
		else return 0;
	case '/':
		if (b == '+' || b == '-') return 1;
		else return 0;
	default:
		if (b == '*' || b == '/') return -1;
		else return 0;
	}
}