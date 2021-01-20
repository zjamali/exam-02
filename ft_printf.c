#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int ft_maxi(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
int ft_mini(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
int ft_putnbr(unsigned int n, int base)
{
	int		i;
	char	str[12];
	
	if (n == 0)
	{
		write (1,"0",1);
		return (0);
	}
	i = 0;
	while (n != 0)
	{
		str[i] = n % base < 10  ? n % base + 48 : n % base + 87 ;
		n = n / base;
		i++;	
	}
	while (i > 0)
	{
		i--;
		write(1, str + i, 1);
	}
	return (0);
}

int ft_intlen(unsigned int n, int base)
{
	int i;

	i = 1;
	while (n / base != 0)
	{
		n = n / base;
		i++;	
	}
	return (i);
}

int ft_print_s(char *str, int width, int precision)
{
	int min;
	int len;
	int i;
	
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	min = precision < 0 ? len : ft_mini(precision, len);
	i = 0;
	while (i < width - min)
	{
		write(1," ",1);
		i++;
	}
	write(1, str, min);
	return (i + min);
}

int ft_print_x(unsigned int l, int width, int precision)
{
	int		i;
	int		max;
	int		len;

	len = ft_intlen(l, 16);
	max = ft_maxi(precision, len);
	if (precision == 0 && l == 0)
		max = 0;
	i = 0;
	while (i < width - max)
	{
		write(1, " ", 1);
		i++;
	}
	i = 0;
	while (i < precision - len)
	{
		write(1, "0", 1);
		i++;
	}
	if (precision != 0 || l != 0)
		ft_putnbr(l, 16);
	return (ft_maxi(max , width));
}

int ft_print_d(int n, int width, int precision)
{
	long	l;
	int		i;
	int		max;
	int		len;

	l = n;
	l = l < 0 ? -l : l;
	len = ft_intlen(l, 10);
	max = ft_maxi(precision, len);
	if (precision == 0 && n == 0)
		max = 0;
	if (n < 0)
		max++;
	i = 0;
	while (i < width - max)
	{
		write(1, " ", 1);
		i++;
	}
	if (n < 0)
		write( 1, "-", 1);
	i = 0;
	while (i < precision - len)
	{
		write(1, "0", 1);
		i++;
	}
	if (precision != 0 || n != 0)
		ft_putnbr((unsigned int)l, 10);
	return (ft_maxi(max, width));
}

char	*ft_scan_flags(char *str, int *width, int *precision)
{
	*width = 0;
	*precision = -1;

	while (*str < 58 && *str > 47)
	{
		*width = *width * 10 + *str - 48;
		str++;
	}
	if (*str == '.')
	{
		*precision = 0;
		str++;
	}
	while (*str < 58 && *str > 47)
	{
		*precision = *precision * 10 + *str - 48;
		str++;
	}
	return (str);
}

int ft_print(char c, va_list *pa, int width, int precision)
{
	if (c == 's')
		return (ft_print_s(va_arg(*pa, char*), width, precision));
	if (c == 'd')
		return (ft_print_d(va_arg(*pa, int), width, precision));
	if (c == 'x')
		return (ft_print_x(va_arg(*pa,unsigned int), width, precision));
	return (0);
}

int ft_printf(const char *str, ...)
{
	va_list	pa;
	int		i;
	int		width;
	int		precision;

	i = 0;
	va_start(pa, str);
	while(*str != '\0')
	{
		while(*str == '%')
		{
			str = ft_scan_flags((char*)++str, &width, &precision);
			i += ft_print(*str, &pa, width, precision);
			if (*str == 'd' || *str == 's' || *str == 'x')
				str++;
		}
		if (*str != '\0')
		{
			write(1, str++, 1);
			i++;
		}
	}
	va_end(pa);
	return (i);
}

# define F	r += ft_printf
/*#else

# define F	r += printf
#endif*/

int
	main(void)
{
	int	r;

	r = 0;
	/*
	F("Simple test\n");
	F("");
	F("--Format---");
	F("\n");
	*/
//	F("%5d", 0);
	F("%5.d", 50);
	/*
	F("%d", 42);
	F("%d", 1);
	F("%d", 5454);
	F("%d", (int)2147483647);
	F("%d", (int)2147483648);
	F("%d", (int)-2147483648);
	F("%d", (int)-2147483649);
	F("\n");
	F("%x", 0);
	F("%x", 42);
	F("%x", 1);
	F("%x", 5454);
	F("%x", (int)2147483647);
	F("%x", (int)2147483648);
	F("%x", (int)-2147483648);
	F("%x", (int)-2147483649);
	F("%8.3s", "toto");
	F("%s", "toto");
	F("%s", "wiurwuyrhwrywuier");
	F("%s", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("\n--Mixed---\n");
	F("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("\n");
	F("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("--1 Flag--\n");
	F("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("--2 Flags--\n");
	F("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("--Precision--\n");
	F("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("--Width--\n");
	F("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("--Width and Precision--\n");
	F("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	F("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	F("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	*/
	printf("written: %d\n", r);
}
