#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int neighbors(char *b, int w, int h, int i, int j) {
    int c = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if ((di || dj) && i + di >= 0 && i + di < h && j + dj >= 0 && j + dj < w) {
                c += (b[(i + di) * w + j + dj] == 'O');
            }
        }
    }
    return c;
}

int main(int ac, char **av) {
    if (ac != 4)
        return 1;
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int it = atoi(av[3]);
    int px = 0, py = 0, draw = 0, sz = w * h;
    char c, *b = malloc(sz), *t;
    if (!b)
        return 1;
    for (int i = 0; i < sz; i++)
        b[i] = ' ';
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if      (c == 'w' && py > 0)     py--;
        else if (c == 's' && py < h - 1) py++;
        else if (c == 'a' && px > 0)     px--;
        else if (c == 'd' && px < w - 1) px++;
        else if (c == 'x') draw = !draw;
        else continue;
        if (draw)
            b[py * w + px] = 'O';
    }
    while (it--) {
        if (!(t = malloc(sz))) {
            free(b);
            return 1;
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int nb = neighbors(b, w, h, i, j);
                t[i * w + j] = (nb == 3 || (nb == 2 && b[i * w + j] == 'O')) ? 'O' : ' ';
            }
        }
        free(b);
        b = t;
    }
    for (int i = 0; i < sz; i++) {
        putchar(b[i]);
        if ((i + 1) % w == 0)
            putchar('\n');
    }
    free(b);
    return 0;
}