#include "holberton.h"
#include <stdio.h>

/**
 * _isdigit - checks if character is a digit
 * @s: the character to check
 *
 * Return: 1 if digit, 0 otherwise
 */
int _isdigit(char s)
{
	return (s >= '0' && s <= '9');
}

/**
 * _atoi - converts string to integer
 * @s: the string
 *
 * Return: integer value of string
 */
int _atoi(char *s)
{
	int i = 0, num = 0, neg = 0, d;

	while (s[i])
	{
		if (s[i] == '-')
		{
			neg++;
		}
		else if (s[i] == '+')
		{
			neg--;
		}
		else if (_isdigit(s[i]))
		{
			while (_isdigit(s[i]))
			{
				d = (s[i] - '0');
				d = neg > 0 ? -d : d;
				num = num * 10 + d;
				s++;
			}
			break;
		}
		s++;
	}
	return (num);
}
