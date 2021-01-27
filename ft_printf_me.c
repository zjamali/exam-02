#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int ft_max(int a,int b)
{
	if ( a >b)
		return a;
	return b;

}
int ft_min(int a,int b)
{
	if( a > b)
		return b;
	return a;
}

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		{
			i++;
		}
		return i;
}

int ft_intlen(int n, int base)
{
	int i = 1;

	while (n / base != 0)
	{
		 n = n / base;
		 i++;
	}
	return i;
}

int ft_putnbr(unsigned int nbr,int base)
{
	char str[14];

	if (nbr == 0)
		{
			write(1,"0",1);
			return 0;
		}
	
	int i = 0;
	while (nbr % base != 0)
	{
		str[i] = nbr % base < 10 ? nbr % base + 48 : nbr % base + 87;
		nbr = nbr / base;
	}
	while (i > 0)
	{
		i--;
		write(1,str + i,1);
	}
	return 0;
}

int ft_print_s(char *str,int width ,int prec)
{
	if (str == NULL)
		str = "(null)";
	
	int len = ft_strlen(str);
	int max = prec < 0? len : ft_min(len,prec);

	int i = 0;
	while (i < width - max)
	{
		write(1," ",1);
		i++;
	}
	write(1,str,max);
	return (i + max);
}

int ft_print_d(int n , int width,int prec)
{
	int l =  n < 0 ? -n : n;

	int len = ft_intlen(l,10);

	int max = ft_max(prec,len);
	if (n == 0 && prec == 0)
		max = 0;
	if (n < 0)
		max++;
	
	int i = 0; 
	while (i < width - max)
	{
		write(1," ",1);
		i++;
	}
	if (n < 0)
		write(1,"-",1);
	i = 0;
	while (i < prec - len)
	{
		write(1,"0",1);
		i++;
	}
	if (prec != 0 || n != 0)
		ft_putnbr(n, 10);

	return(ft_max(max,width));
}

int ft_print_x(unsigned int n , int width,int prec)
{
	int l = n;

	int len = ft_intlen(l,16);

	int max = ft_max(prec,len);
	if (n == 0 && prec == 0)
		max = 0;
	int i = 0; 
	while (i < width - max)
	{
		write(1," ",1);
		i++;
	}
	i = 0;
	while (i < prec - len)
	{
		write(1,"0",1);
		i++;
	}
	if (prec != 0 || n != 0)
		ft_putnbr(n, 16);

	return(ft_max(max,width));
}

int ft_print_all(char c,va_list *ap,int width,int prec)
{
	if (c == 's')
		return ft_print_s(va_arg(*ap,char *),width,prec);
	if (c == 'd')
		return ft_print_d(va_arg(*ap,int),width,prec);
	if (c == 'x')
		return ft_print_x(va_arg(*ap,unsigned int),width,prec);
	return 0;
}

char *ft_get_flags(char *str,int *width,int *prec)
{
	*width = 0;
	*prec = -1;

	while (*str > 47 && *str < 59 )
	{
		*width = *width * 10 + *str - 48;
		str++;
	}
	if(*str == '.')
	{
		*prec = 0;
		str++;
	}
	while (*str > 47 && *str < 59 )
	{
		*prec = *prec * 10 + *str - 48;
		str++;
	}
	return str;
}

int ft_printf(const char *str, ... )
{
	int width;
	int prec;
	va_list ap;
	int i = 0;

	va_start(ap,str);
	while(*str)
	{
		while (*str == '%')
		{
			str = ft_get_flags((char*)++str,&width,&prec);
			i+= ft_print_all(*str,&ap,width,prec);
			if ( *str == 's' || *str == 'x' || *str == 'd')
				str++;
		}
		if(*str)
		{
			write(1,str,1);
			i++;
		}
	}
	va_end(ap);
	return i;
}