#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct {
    int n;
    char emp, obs, ful;
} t_elem;

typedef struct {
    char **g;
    int h, w;
} t_map;

void free_map(char **g);
int execute_bsq(FILE *f);

#endif