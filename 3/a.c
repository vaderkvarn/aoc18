#include <stdio.h>
#include <stdlib.h>

#define SIZE 1318

int map[SIZE][SIZE];

void fillMap(int x, int y, int w, int h) {
        for (int i = x ; i < x+w ; i++ ) {
            for (int j = y ; j < y+h ; j++) {
                map[i][j]++;
        }
    }
}

int main() {
    FILE* f;
    f = fopen("input", "r");
    int id, x, y, w, h;
    while (fscanf(f, "#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5) {
        fillMap(x,y,w,h);
    }
    int count = 0;
    for (int i = 0 ; i < SIZE ; i++ ) {
        for (int j = 0 ; j < SIZE ; j++) {
            if (map[i][j] > 1) count++;
        }
    }
    printf("%d\n", count);

    return 0;
}