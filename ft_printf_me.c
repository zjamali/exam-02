#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
char *ft_get_flags(char *str,int *width,int *presicion)
{
	*presicion = -1;
	*width = 0;

	while (*str >= 48 && *str <= 57)
	{
		*width = *width * 10 + (*str - 48);
		str++;
	}
	if (*str == '.')
	{
		*presicion = 0;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		*presicion = *presicion * 10 + (*str - 48);
		str++;
	}
	return str;
}
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
	
}
int ft_min(int a,int b)
{
	if (a > b)
		return b;
	return a;
}
int ft_max(int a,int b)
{
	if (a > b)
		return a;
	return b;
}
int print_s(char *str,int width,int presicion)
{
	
	int strlen = ft_strlen(str);
	int len = presicion < 0 ? strlen : ft_min(presicion,strlen);
	int i = 0;
	while (i < width - len)
	{
		write(1," ",1);
		i++;
	}
	write(1,str,len);
	return i + len;
}
int ft_num_len(int number)
{
	int i = 0;

	while ( number < 10)
	{
		number = number / 10;
		i++;
	}
	return i;
}
int ft_print_number(int number,int type)
{
	while (number < 10)
	{
		
	}
	

}
int print_d(int number,int width,int presicion)
{
	
	int numlen = ft_num_len(number);
	int len = presicion < 0 ? numlen : ft_max(presicion,numlen);
	int i = 0;

	while (i < width - len)
	{
		write(1," ",1);
		i++;
	}
	i = ft_print_number(number,10);
	return i + len;
}

int ft_print(char *str,int width,int presicion,va_list *ap)
{
	int i = 0;
	if (*str == 's')
		i = print_s(va_arg(*ap,char*),width,presicion);
	return i;
}

int ft_printf(const char *str,...)
{
	int presicion;
	int width;
	int i;
	va_list ap;

	va_start(ap,str);
	i = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str = ft_get_flags((char*)++str,&width,&presicion);
			//printf("|%d|%d|",width,presicion);
			i += ft_print((char*)str,width,presicion,&ap);
			if (*str == 's')
				str++;
		}
		if (*str != '\0')
		{
			write(1, str++, 1);
			i++;
		}
	}
	va_end(ap);
	return i;
}

int main()
{
	int i = ft_printf("hellllo %10.5s","zouhair");
	printf("\nreturn : %d\n",i);
	i = printf("hellllo %10.5s","zouhair");
	printf("\nreturn : %d\n",i);
	return 0;
}