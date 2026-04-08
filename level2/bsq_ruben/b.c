#include "bsq.h"

void free_map(char **g) {
    if (!g) return ;
    for (int i = 0; g[i]; i++) free(g[i]);
    free(g);
}

static char *strdup_n(char *s, int n) {
    char *r = malloc(n + 1);
    for (int i = 0; i < n; i++) r[i] = s[i];
    r[n] = '\0';
    return r;
}

static int valid_chars(char **g, char emp, char obs) {
    for (int i = 0; g[i]; i++)
        for (int j = 0; g[i][j]; j++) 
            if (g[i][j] != emp && g[i][j] != obs) return -1;
    return 0; 
}

static int load_elem(FILE *f, t_elem *e) {
    if (fscanf(f, "%d %c %c %c", &e->n, &e->emp, &e->obs, &e->ful) != 4 || e->n <= 0)
        return -1;
    if (e->emp == e->ful || e->emp == e->obs || e->ful == e->obs)
        return -1;
    return 0;
}

static int load_map(FILE *f, t_map *m, t_elem *e) {
    char *line = NULL;
    size_t len = 0;
    ssize_t r;
    m->h = e->n;
    if (!(m->g = calloc(m->h + 1, sizeof(char *)))) return -1;
    if (getline(&line, &len, f) == -1) { free(line); free_map(m->g); return -1; }
    for (int i = 0; i < m->h; i++) {
        if ((r = getline(&line, &len, f)) == -1 || line[r - 1] != '\n')
            { free(line); free_map(m->g); return -1; }
        r--;
        if (i == 0) m->w = (int)r;
        else if (m->w != (int)r) { free(line); free_map(m->g); return -1; }
        if (!(m->g[i] = strdup_n(line, r))) { free(line); free_map(m->g); return -1; }
    }
    free(line);
    if (valid_chars(m->g, e->emp, e->obs) == -1) { free_map(m->g); return -1; }
    return 0;
}

static int min3(int a, int b, int c) {
    return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}

static int solve(t_map *m, t_elem *e) {
    int *dp = calloc(m->h * m->w, sizeof(int));
    int si = 0, sj = 0, ss = 0, val = 0;
    if (!dp) return -1;
    for (int i = 0; i < m->h; i++) {
        for (int j = 0; j < m->w; j++) {
            if (m->g[i][j] == e->obs)
                val = 0;
            else if (i == 0 || j == 0)
                val = 1;
            else
                val = min3(dp[(i-1)*m->w + j], dp[(i-1)*m->w + j-1], dp[i*m->w + j-1]) + 1;
            dp[i*m->w + j] = val;
            if (val > ss)
                { ss = val; si = i - ss + 1; sj = j - ss + j; }
        }
    }
    free(dp);
    for (int)
}