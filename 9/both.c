#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <strings.h>

#define NUM_ELVES 411
#define SIZE_A 71058
#define SIZE_B 71058*100

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    uint64_t val;
} Node;

Node* addAfter(Node* before, uint64_t val) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->prev = before;
    node->next = before->next;
    before->next = node;
    node->next->prev = node;
    return node;
}

Node* initCircular(uint64_t val) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->next = node;
    node->prev = node;
    return node;
}

Node* rmNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    Node* next = node->next;
    free(node);
    return next;
}

uint64_t getMaxScore(uint64_t size) {
    Node* start = initCircular(0);
    Node* current = start;
    uint64_t score[NUM_ELVES];
    bzero(score, NUM_ELVES*sizeof(uint64_t));
    uint64_t current_elv = 0;
    for (uint64_t i = 1; i <= size; i++) {
        if (i % 23 == 0) {
            score[current_elv] += i;     
            for (int i = 0; i < 7; i++) current = current->prev;
            score[current_elv] += current->val;
            current = rmNode(current);
        } else {
            current = addAfter(current->next, i);
        }
        current_elv = (current_elv + 1)%NUM_ELVES;
    }
    uint64_t max_score = 0;
    for (uint64_t i = 0 ; i < NUM_ELVES; i++) {
        if (score[i] > max_score) max_score = score[i]; 
    }
    return max_score;
}

int main() {
    printf("%ld\n", getMaxScore(SIZE_A));
    printf("%ld\n", getMaxScore(SIZE_B));

    return 0;
}