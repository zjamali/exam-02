#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_buff
{
	char *buff;
	size_t	size;
	size_t	pos;
}				t_buff;

void copy(t_buff *dest,t_buff *src)
{
	/// copy content of prev to current 
	dest->buff = src->buff;
	dest->pos = src->pos;
	dest->size = src->size;

	/// set previous to NULL
	src->buff = NULL;
	src->size = NULL;
	src->pos = NULL;
}
int check(char *str,size_t len)
{
	int i;
	i = 0;
	while(str[i])
	{
		if (str[i] == '\n')
			return i;
		i++;
	}
	return -1; 
}
int get_next_line(char **line)
{
	static t_buff	prev;
	t_buff			curr;

	if (prev.buff != NULL)
	{
		copy(&curr,&prev);

	}
	else
	{

		
	}
	
	

}