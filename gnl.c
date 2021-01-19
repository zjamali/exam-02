#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

int is_n(char *w)
{
    while (*w)
    {
        if (*w == '\n')
            return (1);
        w++;
    }
    return (0);
}

int ft_strlen(char *z)
{
    int zz;

    zz = 0;
    while (z[zz++]);
    return(--zz);
}

char *ft_strdup(char *s)
{
    int i;
    int len;
    char *ret;

    len = ft_strlen(s) + 1;
    ret = (char *)malloc(len);
    i = 0;
    while (s[i])
    {
        ret[i] = s[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char *ft_strjoin(char *s1, char *s2)
{
    int len1;
    int len2;
    int i;
    char *fill;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    fill = malloc(sizeof(char) * (len1 + len2 + 1));
    i = 0;
    while (*s1)
        fill[i++] = *s1++;
    while (*s2)
        fill[i++] = *s2++;
    fill[i] = '\0';
    return (fill);
}

char *my_strcut(char *str, int end)
{
    int len;
    int i;
    char *bf;

    len = ft_strlen(str);
    if (len > end)
        len = end;
    bf = malloc(sizeof(char) * (len + 1));
    i = 0;
    while (*str && len--)
        bf[i++] = *str++;
    bf[i] = '\0';
    return (bf);
}

int fill_line(char **content, char **line)
{
    int end;
    char *tmp;

    end = 0;
    while ((*content)[end] != '\n' && (*content)[end] != '\0')
        end++;
    if ((*content)[end] == '\n')
    {
        *line = my_strcut(*content, end);
        tmp = ft_strdup(*content + end + 1);
        free(*content);
        *content = tmp;
        return (1);
    }
    else if ((*content)[end] == '\0')
    {
        *line = ft_strdup(*content);
        free(*content);
    }
    return (0);
}

int get_next_line(char **line)
{
    static char *content;
    char *buff;
    char *tmp;
    int r;

    if (content == NULL)
        content = ft_strdup("");
    buff = (char *)malloc(101);
    if (!is_n(content))
        while ((r = read(0, buff, 100)) > 0)
        {
            buff[r] = '\0';
            tmp = ft_strjoin(content, buff);
            free(content);
            content = tmp;
            if (is_n(buff))
                break;
        }
    free(buff);
    return (fill_line(&content, line));
}

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