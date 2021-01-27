/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   againprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 14:40:26 by knabouss          #+#    #+#             */
/*   Updated: 2020/12/14 10:12:35 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct  s_struct
{
	int width;
	int point;
	int precision;
	int sign;
	int len;
	char    specifier;
	int    dec;
	unsigned int hex;
	char *str;
	int count;
	long l;
}               t_struct;


int 	ft_strlen(char *s)
{
	int i = 0;

	if (!s)
		return(0);
	while(*s)
	{
		i++;
		s++;
	}
	return(i);
}

void    ft_putchar(char c)
{
	write(1, &c, 1);
}

void    ft_putstr(char *s)
{
	while(*s)
	{
		ft_putchar(*s);
		s++;
	}
}

void    ft_putnbr(long a)
{
	if (a == -2147483648)
		{
			ft_putstr("2147483648");
			return ;
		}
	if( a > 9)
		ft_putnbr(a/10);
	ft_putchar((a % 10) + '0');
}


void	init_flag(t_struct *gnrl)
{
	gnrl->width = 0;
	gnrl->point = 0;
	gnrl->len = 0;
	gnrl->sign = 0;
	gnrl->precision = 0;
	gnrl->specifier = 0;
}


int		is_dig(char c)
{
	return(c >= '0' && c <= '9');
}


int		ft_atoi(char **s)
{
	int a = 0;
	while (is_dig(**s))
	{
		a = (a * 10) + (**s - '0');
		(*s)++;
	}
	return (a);
}

void	gather_flag(t_struct *gnrl, char **s, va_list ap)
{
	(*s)++;
	while(**s)
	{
		if (**s == 'd' || **s == 's' || **s == 'x')
		{
			gnrl->specifier = **s;
			if (**s == 'd')
				gnrl->dec = va_arg(ap, int);
			else if (**s == 's')
				gnrl->str = va_arg(ap, char *);
			else if (**s == 'x')
				gnrl->hex = va_arg(ap, unsigned int);
			(*s)++;
			break;
		}
		else if (**s == '.')
		{
			gnrl->point = 1;
			(*s)++;
			gnrl->precision = ft_atoi(s);
			(*s)--;
		}
		else if (is_dig(**s))
		{
			gnrl->width = ft_atoi(s);
			(*s)--;
		}
		(*s)++;
	}
}

int     nbrlen(long a)
{
	int l;

	l = 1;
	while(a/10)
	{
		a /= 10;
		l++;
	}
	return(l);
}


void	correct_dec(t_struct *gnrl)
{
	gnrl->len = nbrlen(gnrl->dec);
	if (gnrl->dec < 0)
		gnrl->sign = 1;
	if (gnrl->sign)
		gnrl->dec *= -1; /*(long)(-gnrl->dec)*/;
	if (!gnrl->dec && gnrl->point && gnrl->precision == 0)
		gnrl->len = 0;
	gnrl->precision -= (gnrl->precision > gnrl->len) ? gnrl->len : gnrl->precision;
	gnrl->width -= (gnrl->width > gnrl->len + gnrl->precision + gnrl->sign) ? gnrl->len + gnrl->sign + gnrl->precision : gnrl->width;
}

void	print_dec(t_struct *gnrl)
{
	while (gnrl->width)
	{
		ft_putchar(' ');
		gnrl->count++;
		gnrl->width--;
	}
	if (gnrl->sign)
	{
		ft_putchar('-');
		gnrl->count++;
	}
	while (gnrl->precision)
	{
		ft_putchar('0');
		gnrl->count++;
		gnrl->precision--;
	}
	if (gnrl->len)
		ft_putnbr((long long)gnrl->dec);
	gnrl->count += gnrl->len;
}


void	correct_str(t_struct *gnrl)
{
	gnrl->len = (gnrl->str) ? ft_strlen(gnrl->str) : 6;
	gnrl->len = (gnrl->point && gnrl->len > gnrl->precision) ? gnrl->precision : gnrl->len;
	gnrl->width -= (gnrl->width > gnrl->len) ? gnrl->len : gnrl->width;
}

void	print_str(t_struct *gnrl)
{
	while(gnrl->width)
	{
		ft_putchar(' ');
		gnrl->count++;
		gnrl->width--;
	}
	if (!gnrl->str)
		gnrl->str = "(null)";
	gnrl->count += gnrl->len;
	while (gnrl->len)
	{
		ft_putchar(*gnrl->str);
		gnrl->len--;
		gnrl->str++;
	}
}

char		hex_dig(int n)
{
	if (n < 10)
		return(n + '0');
	else
		return(n + 'W');
}

char	*conv_hex(unsigned int u, int step)
{
	static	int l;
	static char *hex;
	if (!step)
	{
		int i = 0;
		hex = (char *)malloc(17);
		while(i < 17)
			hex[i++] = 0;
		l = 0; 
	}
	if (u / 16)
		conv_hex(u / 16, 1);
	hex[l++] = hex_dig(u % 16);
	return(hex);
}


void     correct_hex(t_struct *gnrl)
{
    gnrl->str = conv_hex(gnrl->hex, 0);
    gnrl->len = ft_strlen(gnrl->str);
    if (!gnrl->hex && gnrl->point && gnrl->precision == 0)
        gnrl->len = 0;
    gnrl->precision -= (gnrl->precision > gnrl->len) ? gnrl->len : gnrl->precision;
    gnrl->width -= (gnrl->width > gnrl->precision + gnrl->len) ? gnrl->precision + gnrl->len : gnrl->width;
}

void	print_hex(t_struct *gnrl)
{
	while(gnrl->width)
	{
		ft_putchar(' ');
		gnrl->count++;
		gnrl->width--;
	}
	while (gnrl->precision)
	{
		ft_putchar('0');
		gnrl->count++;
		gnrl->precision--;
	}
	gnrl->count += gnrl->len;
	while (gnrl->len)
	{
		ft_putchar(*gnrl->str);
		gnrl->str++;
		gnrl->len--;
	}
}

void	global_print(t_struct *gnrl)
{
	if (gnrl->specifier == 'd')
	{
		correct_dec(gnrl);
		print_dec(gnrl);
	}
	else if (gnrl->specifier == 's')
	{
		correct_str(gnrl);
		print_str(gnrl);
	}
	else if (gnrl->specifier == 'x')
	{
		correct_hex(gnrl);
		print_hex(gnrl);
	}
}

int 	ft_printf(const char *s, ...)
{
	t_struct gnrl;
	va_list	ap;

	va_start(ap, s);
	gnrl.count = 0;
	while(*s)
	{
		while (*s != '%' && *s)
		{
			ft_putchar(*s);
			gnrl.count++;
			s++;
		}
		if (*s == '%' && *s)
		{
			init_flag(&gnrl);
			gather_flag(&gnrl, (char **)&s, ap);
			global_print(&gnrl);
		}
	}
	return(gnrl.count);
}