#include <stdarg.h> // va_args
#include <stdio.h> // printf
#include <unistd.h> // write

int put_char(char c)
{
    int count = 0;

    write(1, &c, 1);
    count += 1;
    return (count);
}

int s_func(char *str)
{
    int i = 0;
    int count = 0;

    if (!str)
        str = "(null)";
    while (str[i] != '\0')
    {
        count += put_char(str[i]);
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
    count += put_char(n % 10 + '0');
    return (count);
}

int x_func(unsigned int x)
{
    int count = 0;
    char *hex = "0123456789abcdef";

    if (x > 15)
        count += x_func(x / 16);
    x = hex[x % 16];
    count += put_char(x);
    return (count);
}

int ft_printf(char *input, ...)
{
    int count = 0;
    int i = 0;
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
            count += put_char(input[i]);
        i++;
    }   
    va_end(args);
    return (count);
}

int main()
{
    int i = 0;
    int j = 0;
    char *str1 = "helloooo";
    char *str2 = NULL;

    i = ft_printf("test %d, %d, %d, %s, %s, %x, %x string\n", -2147483648, -456, 123, str1, str2, 456, 2336);
    j = printf("test %ld, %d, %d, %s, %s, %x, %x string\n", -2147483648, -456, 123, str1, str2, 456, 2336);
    printf("my: %d\nst: %d\n", i, j);
    return (0);
}