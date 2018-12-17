#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

typedef enum Direction { LEFT, STRAIGHT, RIGHT } Direction;

char cart_heads[] = {'^','>','v','<'};

typedef struct Point {
    int x;
    int y;
    char c;
    char replacement;
    Direction cross_direction;
    bool dead;
} Point;

typedef struct Size {
    size_t rows;
    size_t cols;
} Size;

int mod(int i, int n) {
    return (i % n + n) % n;
}
bool isCart(char c) {
    switch(c) {
        case '<': case '>': case 'v': case '^':
        return true;
        default: return false;
    }
}

int cartCmp(const void* s1, const void* s2) {
    Point *c1 = (Point *) s1;
    Point *c2 = (Point *) s2;
    if (c1->y == c2->y) {
        return c1->x - c2->x;
    } 
    return c1->y - c2->y;
}

bool validChar(char c) {
    return c == '|' || c == '-' || c == '\\' || c == '/' || c == '+';
}

void printMap(char** map, Size size) {
    for (int i = 0; i < size.rows; i++) {
        //printf("%d:", i);
        for (int j = 0; j < size.cols; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int getCartHeadIndex(char c) {
    for (int i = 0; i < 4; i++) {
        if (c == cart_heads[i]) return i;
    }
    return -1;
}

char getNextHeadCross(char old_head, Direction cross_direction) {
    int i = getCartHeadIndex(old_head);
    switch (cross_direction) {
        case LEFT: return cart_heads[mod(i-1,4)];
        case STRAIGHT: return old_head;
        case RIGHT: return cart_heads[mod(i+1,4)];
    }
    return old_head;
}
char getNextHead(char old_head, char tile) {
    int i = getCartHeadIndex(old_head);
    switch(tile) {
        case '|': case '-': return old_head;
        case '/':
            if (old_head == '>') return '^';
            if (old_head == '<') return 'v';
            if (old_head == 'v') return '<';
            if (old_head == '^') return '>';
            break;
        case '\\':
            if (old_head == '>') return 'v';
            if (old_head == '<') return '^';
            if (old_head == 'v') return '>';
            if (old_head == '^') return '<';
    }
    return tile;
}
bool found_first = false;
Point move(char** map, Size size, Point p) {
    if (p.dead) return p;
    if (map[p.y][p.x] == 'X') {
        p.c = 'X';
        map[p.y][p.x] = p.replacement;
        return p;
    }
    Point next = (Point) {p.x, p.y, map[p.y][p.x]};
    switch(p.c) {
        case '>':
            next.x++;
            break;
        case '<':
            next.x--;
            break;
        case '^':
            next.y--;
            break;
        case 'v':
            next.y++;
            break;
        default: printf("No cart\n");
    }
    next.c = map[next.y][next.x];
    next.replacement = map[next.y][next.x];
    if (next.c == '+') {
        next.c = getNextHeadCross(p.c, p.cross_direction);
        next.cross_direction = mod(p.cross_direction + 1,3);
    } else {
        next.c = getNextHead(p.c, next.c);
        next.cross_direction = p.cross_direction;
    }
    if (isCart(map[next.y][next.x]) || map[next.y][next.x] == 'X') {
        if (!found_first) {
            printf("%d,%d\n", next.x, next.y);
            found_first = true;
        }
        next.c = 'X';
    }
    map[next.y][next.x] = next.c;
    map[p.y][p.x] = p.replacement;
    return next;
}

int numValidCarts(Point* carts, size_t num_carts) {
    int num = 0;
    for (int i = 0; i < num_carts; i++) {
        if (carts[i].c != 'X') num++;
    }
    return num;
}

void tick(char** map, Size size, Point* carts, size_t num_carts) {
    for (int i = 0; i < num_carts; i++) {
        Point cart = carts[i];
        if (cart.c == 'X') cart.dead = true;
        carts[i] = move(map, size, cart);
    }
    for (int i = 0; i < num_carts; i++) {
        if (carts[i].dead) continue;
        for (int j = 0; j < num_carts; j++) {
            if (i == j || carts[j].dead) continue;
            if (carts[i].c == 'X' || carts[j].c == 'X') {
                if (carts[i].x == carts[j].x && carts[i].y == carts[j].y) {
                    carts[i].c = 'X';
                    carts[j].c = 'X';
                    if (map[carts[i].y][carts[i].x] == 'X') {
                        map[carts[i].y][carts[i].x] = carts[i].replacement;
                    }
                }
            }
        }
    }
    if (numValidCarts(carts, num_carts) <= 1) {
        for (int i = 0; i < num_carts; i++) {
            if (carts[i].c != 'X') {
                printf("%d,%d\n", carts[i].x, carts[i].y);
            }
        }
        exit(0);
    }
}

int main(int argc, char** argv) {
    Size size;
    size.rows = atoi(argv[2]);
    size.cols = atoi(argv[3]);
    char** map = calloc(size.rows, sizeof(char*));
    Point carts[256];
    size_t num_carts = 0;
    for (int i = 0; i < size.rows; i++) map[i] = calloc(size.cols, sizeof(char));
    FILE *fp = fopen(argv[1], "r");
    for (int i = 0; i < size.rows; i++) {
        for (int j = 0; j < size.cols; j++) {
            char c = fgetc(fp);
            if (c == '\n') {
                break;
            } else if (isCart(c)) {
                char replacement;
                if (c == '>' || c == '<') replacement = '-';
                else replacement = '|';
                carts[num_carts++] = (Point){j, i, c, replacement, 0};
            }
            map[i][j] = c;
        }
    }

    while (true) {
        //printMap(map, size);
        qsort(carts, num_carts, sizeof(Point), cartCmp);
        tick(map, size, carts, num_carts);
        //sleep(1);
    }
    return 0;
}