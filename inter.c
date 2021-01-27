#include <unistd.h>

int main(int ac, char **av)
{
	if (ac == 3)
	{
		int tab[255];
		int i = 0;

		while (i < 255)
		{
			tab[i] = 0;
			i++;
		}
		i = 2;
		while (i > 0)
		{
			int j = 0;
			while (av[i][j])
			{
				if (i == 2 && !tab[(unsigned int)av[i][j]])
					tab[(unsigned int)av[i][j]] = 1;
				if(i == 1 && tab[(unsigned int)av[i][j]] == 1)
					{
						write(1,&av[i][j],1);
						tab[(unsigned int)av[i][j]] = 2;
					}
				j++;
			}
			i--;
		}
	}
	write(1, "\n", 1);
	return 0;
}