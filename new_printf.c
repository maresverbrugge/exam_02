#include <stdarg.h> // for variable arguments
#include <unistd.h> // for write

#include <stdio.h> // for std printf

int	ft_put_char(char c)
{
	int count = 0;
    
    write(1, &c, 1);
    count += 1;
	return (count);
}

int s_func(char *str)
{
    int	i = 0;
    int count = 0;

	if (!str)
		str = "(null)";
	while (str[i] != '\0')
	{
		count += ft_put_char(str[i]);
		i++;
	}
    return (count);
}

int d_func(int n)
{
	int count = 0;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
        count += 11;
		return (count);
	}
	if (n < 0)
	{
		write(1, "-", 1);
        count += 1;
		n = -n;
	}
	if (n >= 10)
		count += d_func(n / 10);
	count += ft_put_char(n % 10 + '0');
	return (count);
}

int x_func(unsigned int n)
{
    int 	count = 0;
	char	*hexa;

	hexa = "0123456789abcdef";
	if (n > 15)
		count += x_func(n / 16);
	n = hexa[n % 16];
	count += ft_put_char(n);
    return (count);
}

int	ft_printf(const char	*input, ...)
{
	int     i = 0;
    int     count = 0;
	va_list args;

	va_start(args, input);
	while (input[i] != '\0')
	{
		if (input[i] == '%')
		{
			i++;
            if (input[i] == 's')
				count += s_func(va_arg(args, char *));
			else if (input[i] == 'd')
				count += d_func(va_arg(args, int));
			else if (input[i] == 'x')
				count += x_func(va_arg(args, unsigned int));
		}
		else
			count += ft_put_char(input[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int main(void)
{
    int	my_count = 0;
	int st_count = 0;

	// my_count = ft_printf("bonjour %s %s waaah\n", "123", NULL);
	// st_count = printf("bonjour %s %s waaah\n", "123", NULL);

	// my_count = ft_printf("%d, %d bonjour\n", -2147483648, -3);
	// st_count = printf("%ld, %d bonjour\n", -2147483648, -3);

	my_count = ft_printf("coucou %x bonjour\n", 123);
	st_count = printf("coucou %x bonjour\n", 123);
	
	printf("my: %d\nst: %d\n", my_count, st_count);
	return (0);
}