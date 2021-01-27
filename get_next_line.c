#include "get_next_line.h"

int get_next_line(char **line);

int main(void) {
  int r;
  char *line;

  line = NULL;
  while ((r = get_next_line(&line)) > 0) {
    printf("%s\n", line);
    free(line);
    line = NULL;
  }
  printf("%s", line);
  free(line);
  line = NULL;
}

size_t ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return i;
}
char *ft_strdup(char *str)
{
	char *strdup;
	int i = 0;

	if (!(strdup = (char*)malloc(ft_strlen(str) + 1)))
		return NULL;
	while(str[i])
	{
		strdup[i] = str[i];
		i++;
	}
	strdup[i] = '\0';
	return strdup;
}
char *ft_substr(char *str,int start,int end)
{
	char *sub;
	int i = 0;
	int len = end - start;
	if(!(sub = malloc(sizeof(char)*(len  + 1))))
		return NULL;
	while ((i + start) < len)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return sub;
}

char *ft_strjoin(char *str1, char *str2)
{
	if (str1 == NULL)
		return ft_strdup(str2);
	if (str2 == NULL)
		return ft_strdup(str1);
	char *join;
	if (!(join = malloc((sizeof(char)*(ft_strlen(str1)+ ft_strlen(str2) + 1)))))
		return NULL;
	int i = 0;
	int j = 0;
	while (str1[i])
	{
		join[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	while (str2[i])
	{
		join[j] = str2[i];
		j++;
		i++;
	}
	join[j] = '\0';
	return join;
}
int ft_strchr(char *str,int c)
{
	char ch = c;
	int i =  0;
	while (str[i])
	{
		if (str[i] == ch)
			return 1;
		i++;
	}
	return 0;
}

int get_next_line(char **line)
{
	char *buff;
	static char *str;
	char *tmp;
	int r;
	int i = 0;
	
	if (!line)
		return -1;
	buff = malloc(101);
	while((r = read(0,buff,100)) > 0)
	{
		buff[r] = '\0';
		tmp = str;
		str = ft_strjoin(str,buff);
		free(tmp);
		if (ft_strchr(str,'\n'))
			break;
	}
	free(buff);
	if (r < 0)
		return -1;
	else if (!r && (str == NULL || *str = '\0'))
	{
		*line = ft_strdup("");
		return 0;
	}
	if (*str)
	{
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
		{
			*line = ft_substr(str,0,i);
			tmp = str;
			str = ft_strdup(str + i + 1);
			free(tmp);
			return (1);
		}
		else if (str[i] != '\0')
		{
			*line = ft_strdup(str);
			free(str);
			str = NULL;
			return 0;
		}
	}
	return 0;
}