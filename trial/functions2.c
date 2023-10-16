#include "shell.h"

/**
 * our_itoa - converts int into string
 * @n: number of counts
 * @str: pointer to string
 * Return: i
 */
int our_itoa(int n, char *str)
{
	int i = 0;
	int isNegative = 0;

	if (n == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (1);
	}

	if (n < 0)
	{
		isNegative = 1;
		n = -n;
	}

	while (n != 0)
	{
		int rem = n % 10;

		str[i++] = rem + '0';
		n = n / 10;
	}

	if (isNegative)
	{
		str[i++] = '-';
	}

	str[i] = '\0';
	our_strrev(str);

	return (i);
}
#include "shell.h"

/**
 * our_strrev - function to reverse a string (assuming you don't have it)
 * @str: string
 */
void our_strrev(char *str)
{
	int start = 0;
	int end = strlen(str) - 1;
	char temp;

	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
