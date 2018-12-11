#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <strings.h>

typedef struct Point {
    int64_t x;
    int64_t y;
    int64_t vx;
    int64_t vy;
} Point;

int x_comp(const void *p1, const void *p2) {
    return ((Point *)p1)->x - ((Point *)p2)->x;
}
int y_comp(const void *p1, const void *p2) {
    return ((Point *)p1)->y - ((Point *)p2)->y;
}
int numLineups(Point** points, int n, int treshold) {
    int best_x = 0, best_y = 0, tot_x = 0, tot_y = 0;
    Point *ps = *points;
    qsort(*points, n, sizeof(Point), x_comp);
    
    int cur_stretch = 1;
    for (int i = 1 ; i < n ; i++) {
        if (ps[i-1].x == ps[i].x && abs(ps[i-1].y - ps[i].y) == 1) cur_stretch++;
        else {
            if (cur_stretch > treshold) tot_x += cur_stretch;
            best_x = best_x > cur_stretch ? best_x : cur_stretch;
            cur_stretch = 1;
        }
    }
    qsort(*points, n, sizeof(Point), y_comp);
    
    cur_stretch = 1;
    for (int i = 1 ; i < n ; i++) {
        if (ps[i-1].y == ps[i].y && abs(ps[i-1].x - ps[i].x) == 1) cur_stretch++;
        else {
            if (cur_stretch > treshold) tot_y += cur_stretch;
            best_y = best_y > cur_stretch ? best_y : cur_stretch;
            cur_stretch = 1;
        }
    }
    return best_x*10 + best_y*10 + tot_x + tot_y;
}

bool contains(Point** points, int n, int x, int y) {
    Point* ps = *points;
    for (int i = 0; i < n; i++) {
        if (ps[i].x == x && ps[i].y == y) return true;
    }
    return false;
}

void draw(Point** points, int n, Point* top_left, Point* bottom_right, int lap) {
    int width = bottom_right->x - top_left->x + 1;
    int height = bottom_right->y - top_left->y + 1;
    if (width > 500 || height > 500) return;
    Point* ps = *points;
    char name[16];
    sprintf(name, "img/%d.ppm", lap);
    FILE *fp = fopen(name, "wb");
    fprintf(fp, "P4\n%d %d\n", width, height);
    for (int y = top_left->y; y <= bottom_right->y; y++) {
        char c = 0;
        int i = 0;
        for (int x = top_left->x; x <= bottom_right->x; x++) {
            if (contains(points, n, x, y)) {
               c |= 1 << (8-i); 
            } 
            else c |= 0 << (8-i);
            i++;
            if (i == 8) {
                fwrite(&c, 1, 1, fp);
                c = 0;
                i = 0;
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void getCorners(Point** points, int n, Point* tl, Point* br) {
    Point* ps = *points;
    tl->x = 0; tl->y = 0; br->x = 0; br->y = 0;
    for (int i = 0 ; i < n; i++) {
        if (ps[i].x < tl->x) tl->x = ps[i].x;
        if (ps[i].y < tl->y) tl->y = ps[i].y;
        if (ps[i].x > br->x) br->x = ps[i].x;
        if (ps[i].y > br->y) br->y = ps[i].y;
    }
}

void run(Point** points, int n) {
    Point* ps = *points;
    int laps = 20000;
    int top_score = 0;
    int top_lap = 0;
    for (int l = 1 ; l < laps ; l++) {
        Point top_left; Point bottom_right;
        getCorners(points, n, &top_left, &bottom_right);
        for (int i = 0 ; i < n ; i++) {
            ps[i].x += ps[i].vx;
            ps[i].y += ps[i].vy;
        }
        int score = numLineups(&ps, n, 4);
        if (score > top_score) {
            draw(&ps, n, &top_left, &bottom_right, l);
            top_score = score;
            top_lap = l;
        }
    }
} 

int main() {
    FILE* f = fopen("input", "r");
    //FILE* f = fopen("test_input", "r");
    int num_points = 1;
    while (!feof(f)) {
        char ch = fgetc(f);
        if (ch == '\n') num_points++;
    }
    Point* points = calloc(num_points, sizeof(Point));
    rewind(f);
    int64_t x, y, vx, vy;

    for (int i = 0 ; i < num_points ; i++) {
        int num_read = fscanf(f, "position=<%ld, %ld> velocity=<%ld, %ld>\n", &x, &y, &vx, &vy);
        points[i] = (Point){x, y, vx, vy};
    }
    run(&points, num_points);

    return 0;
}