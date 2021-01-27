#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return(i);
}

char	*ft_strdup(const char *s)
{
	int i = 0;
	char *str = (char *)malloc(ft_strlen(s) + 1);
	while(s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return(str);
}

char	ft_strjoin(const char *s1, const char *s2)
{
	int i = 0;
	int j = 0;
	char *str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while(s1[i])
	{
		str[i + j] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	return(str);
}

char	*ft_substr(const char *s, int start, int len)
{
	char *str;
	int i = 0;

	str = (char *)malloc(len + 1);
	while (start < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return(str);
}

char	get_next_line()