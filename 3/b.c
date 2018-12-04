#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Claim {
    int id;
    int x;
    int y;
    int w;
    int h;
};

#define SIZE 1318

int map[SIZE][SIZE][SIZE];
struct Claim my_claims[SIZE];

void fillMap(int id, int x, int y, int w, int h) {
    for (int i = x ; i < x+w ; i++ ) {
        for (int j = y ; j < y+h ; j++) {
            map[i][j][id] = 1;
        }
    }
}

void checkId(struct Claim *c) {
    bool others = false;
    for (int i = c->x ; i < c->x + c->w ; i++ ) {
        for (int j = c->y ; j < c->y + c->h ; j++) {
            int num_ids = 0;
            for (int k = 0 ; k < SIZE ; k++) {
                if (map[i][j][k]) {
                    num_ids++;
                }
            }
            if (num_ids > 1) others = true;
        }
    }
    if (!others) printf("%d\n", c->id);
}


int main() {
    FILE* f;
    f = fopen("input", "r");
    int id, x, y, w, h;
    int i = 0;
    while (fscanf(f, "#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5) {
        fillMap(id,x,y,w,h);
        struct Claim c;
        c.id = id; c.x = x; c.y = y; c.w = w; c.h = h;
        my_claims[i] = c;
        i++;
    }
    for (int j = 0 ; j < i ; j++) {
        checkId(&my_claims[j]);
    }

    return 0;
}