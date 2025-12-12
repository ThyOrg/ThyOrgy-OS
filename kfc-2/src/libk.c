#include "kernel.h"

void	kputchar(char c)
{
	terminal_putchar(c);
}

void	kputstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		kputchar(str[i++]);
}

size_t	kstrlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

char *kstrjoin(char const *s1, char const *s2, char *str)
{
	int		i;
	int		j;
	int		l2;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (0);
	l2 = kstrlen(s2);
	if (!str)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	kputnbr(int n)
{
	long	num;

	num = n;
	if (num < 0)
	{
		kputchar('-');
		num *= -1;
	}
	if (num > 9)
	{
		kputnbr(num / 10);
		kputnbr(num % 10);
	}
	else
	{
		kputchar(num + '0');
	}
}
