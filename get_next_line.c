#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_buff
{
	char *buff;
	size_t	size;
	size_t	pos;
}				t_buff;

int get_next_line(char **line)
{
	static t_buff	prev;
	t_buff			curr;



}