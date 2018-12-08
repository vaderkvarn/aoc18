#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define LIMIT 10000
//#define LIMIT 32

typedef struct Point {
    uint32_t x;
    uint32_t y;
} Point;

typedef struct Corners {
    Point min;
    Point max;
} Corners;

uint32_t manhattan(Point* p1, Point* p2) {
    return abs(p1->x - p2->x) + abs(p1->y - p2->y);
}

int main() {
    FILE* f = fopen("input", "r");
    //FILE* f = fopen("test_input", "r");
    int num_coords = 0;
    while (!feof(f)) {
        char ch = fgetc(f);
        if (ch == '\n') num_coords++;
    }
    Point* coords = calloc(num_coords, sizeof(Point));
    rewind(f);
    uint32_t x, y;
    Corners corners = (Corners) {{UINT32_MAX, UINT32_MAX}, {0, 0}};

    for (int i = 0 ; i < num_coords ; i++) {
        fscanf(f, "%d, %d", &x, &y);
        coords[i] = (Point){x, y};
        if (x < corners.min.x) corners.min.x = x;
        if (y < corners.min.y) corners.min.y = y;
        if (x > corners.max.x) corners.max.x = x;
        if (y > corners.max.y) corners.max.y = y;
    }
    int count = 0;
    for (int y = corners.min.y ; y <= corners.max.y ; y++) {
        for (int x = corners.min.x ; x <= corners.max.x ; x++) {
            Point p = (Point){x, y};
            uint32_t sum_dists = 0;
            for (int i = 0 ; i < num_coords ; i++) {
                sum_dists += manhattan(&p, &(coords[i]));
                if (sum_dists > LIMIT) break;
            }
            if (sum_dists < LIMIT) count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
