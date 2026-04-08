#include "bsq.h"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        if (execute_bsq(stdin) == -1)
            fprintf(stderr, "map error\n");
        return (0);
    }
    for (int i = 1; i < ac; i++)
    {
        FILE    *f = fopen(av[i], "r");
        int      ret = (!f) ? -1 : execute_bsq(f);
        if (f) fclose(f);
        if (ret == -1)
            fprintf(stderr, "map error\n");
        if (ac > 2)
            fprintf(stdout, "\n");
    }
    return (0);
}