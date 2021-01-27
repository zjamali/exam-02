#include <unistd.h>

int main(int ac, char **av)
{
    if (ac == 3)
    {
        char u[255];
        int i = 0;
        while(i < 255)
            u[i++] = 0;
        i = 2;
        int j;
        while(i > 0)
        {
            j = 0;
            while(av[i][j])
            {
                if (i == 2 && u[(unsigned char)av[i][j]] == 0)
                    u[(unsigned char)av[i][j]] = 1;
                if (i == 1 && u[(unsigned char)av[i][j]] == 1)
                {
                    write(1, &av[i][j], 1);
                    u[(unsigned char)av[i][j]] =2;
                }
                j++;
            }
            i--;
        }
    }
    write(1, "\n", 1);
    return(0);
}