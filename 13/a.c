#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct Point {
    int x;
    int y;
    char c;
} Point;

typedef struct Size {
    size_t rows;
    size_t cols;
} Size;

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

bool isLegal(Size size, Point p) {
    bool inside = p.x >= 0 && p.y >= 0 && p.x < size.cols && p.y < size.rows;
    //if(!inside) printf("Not inside\n");
    bool valid_char = p.c == '|' || p.c == '-' || p.c == '\\' || p.c == '/' || p.c == '+';
    //if(!valid_char) printf("Not valid char\n");
    return inside && valid_char;
}

void move(char** map, Size size, Point p) {
    Point next = (Point) {p.x, p.y, map[p.y][p.x]};
    switch(p.c) {
        case '>':
            next.x++;
            printf("Facing right\n");
            break;
        case '<':
            next.x--;
            printf("Facing left\n");
            break;
        case '^':
            next.y--;
            printf("Facing up\n");
            break;
        case 'v':
            next.y++;
            printf("Facing down\n");
            break;
        default: printf("No cart\n");
    }
    next.c = map[next.y][next.x];
    printf("Next square: %d, %d, %c\n", next.x, next.y, next.c);
    if (!isLegal(size, next)) {
        printf("Next move is not legal\n");
        exit(1);
    } 
    switch(next.c) {
        //case: '|'
    }
}

void tick(char** map, Size size, Point* carts, size_t num_carts) {
    qsort(carts, num_carts, sizeof(Point), cartCmp);
    for (int i = 0; i < num_carts; i++) {
        Point cart = carts[i];
        //char c = map[cart.y][cart.x];
        move(map, size, cart);
    }

}

int main(int argc, char** argv) {
    Size size;
    size.rows = atoi(argv[2]);
    size.cols = atoi(argv[3]);
    printf("Num rows: %ld, num cols: %ld\n", size.rows, size.cols);
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
                carts[num_carts++] = (Point){j, i, c};
            }
            map[i][j] = c;
        }
    }

    for (int i = 0; i < size.rows; i++) {
        for (int j = 0; j < size.cols; j++) {
            //if (map[i][j] == '\n') printf("New line in map\n");
            printf("%c", map[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < num_carts; i++) {
        printf("%d, %d, %c\n", carts[i].x, carts[i].y, carts[i].c);
    }
    tick(map, size, carts, num_carts);
    
    /*
    for (int i = 0 ; i < argc ; i++) {
        printf("%d, %s\n", i, argv[i]);
    }
    */
    return 0;
}