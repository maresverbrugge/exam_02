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

int s_func(va_list args)
{
    int     i = 0;
    int count = 0;
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	while (str[i] != '\0')
	{
		count += ft_put_char(str[i]);
		i++;
	}
    return (count);
}

int	ft_put_nbr(int n)
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
		count += ft_put_nbr(n / 10);
	count += ft_put_char(n % 10 + '0');
	return (count);
}

int d_func(va_list args)
{
	int count = 0;
    int	d;

	d = va_arg(args, int);
	count += ft_put_nbr(d);
	return (count);
}
int	ft_put_hex(unsigned int n)
{
	int count = 0;
    char			*hexa;
	unsigned int	x;

	hexa = "0123456789abcdef";
	if (n > 15)
		count += ft_put_hex(n / 16);
	x = hexa[n % 16];
	count += ft_put_char(x);
	return (count);
}

int x_func(va_list args)
{
    int count = 0;
    unsigned int	x;

	x = va_arg(args, unsigned int);
	count += ft_put_hex(x);
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
				count += s_func(args);
			else if (input[i] == 'd')
				count += d_func(args);
			else if (input[i] == 'x')
				count += x_func(args);
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

	my_count = ft_printf("bonjour %s %s waaah\n", "123", NULL);
	st_count = printf("bonjour %s %s waaah\n", "123", NULL);

	// my_count = ft_printf("%d, %d bonjour\n", -2147483647, 123);
	// st_count = printf("%d, %d bonjour\n", -2147483647, 123);

	// my_count = ft_printf("coucou %x bonjour\n", 123);
	// st_count = printf("coucou %x bonjour\n", 123);
	
	printf("my: %d\nst: %d\n", my_count, st_count);
	return (0);
}