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
		i = 1;
		while (i < 3)
		{
			int j = 0;
			while (av[i][j])
			{
				if (tab[(unsigned int)av[i][j]] == 0)
				{
					write(1, &av[i][j], 1);
					tab[(unsigned int)av[i][j]] = 1;
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return 0;
}