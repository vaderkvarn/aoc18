#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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

bool isInfinite(Point *c, Corners* corners) {
    return c->x == corners->min.x 
    || c->x == corners->max.x      
    || c->y == corners->min.y
    || c->y == corners->max.y;
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
    uint32_t* closest = calloc(num_coords, sizeof(uint32_t));
    bool* infinite = calloc(num_coords, sizeof(bool));
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
    
    for (int y = corners.min.y ; y <= corners.max.y ; y++) {
        for (int x = corners.min.x ; x <= corners.max.x ; x++) {
            Point p = (Point){x, y};
            uint32_t min_manhattan = UINT32_MAX;
            int closest_index;
            bool equal = false;
            for (int i = 0 ; i < num_coords ; i++) {
                uint32_t dist = manhattan(&p, &(coords[i]));
                //printf("dist: %d\n", dist);
                if (dist == min_manhattan) {
                    equal = true;
                } else if (dist < min_manhattan) {
                    min_manhattan = dist;
                    closest_index = i;
                    equal = false;
                }
            }
            if (infinite[closest_index]) continue;
            if (!equal) {
                closest[closest_index]++;
            } 
            if (isInfinite(&p, &corners)) {
                infinite[closest_index] = true;
            }
        }
    }
    uint32_t max_length = 0;
    for (int i = 0 ; i < num_coords ; i++) {
        if (closest[i] > max_length && !infinite[i]) {
            max_length = closest[i];
        }
    }
    printf("%d\n", max_length);
    return 0;
}
