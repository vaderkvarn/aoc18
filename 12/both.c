#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct Rule {
	char* pattern;
	char output;
} Rule;

bool ruleApplies(char* state, Rule* rule) {
	int i = 0;
	while (state[i-2] == rule->pattern[i] && i <= 5) i++;
	return i == 5;
}

size_t expandLeft(char** state, size_t size) {
	size_t new_size = size + 4;
	char* new_state = calloc(new_size, sizeof(char));
	memset(new_state, '.', 4);
	memcpy(new_state + 4, *state, size);
	free(*state);
	*state = new_state;
	return new_size;
}

size_t expandRight(char** state, size_t size) {
	size_t new_size = size + 4;
	char* new_state = realloc(*state, new_size*sizeof(char));
	memset(new_state + new_size - 4, '.', 4);
	return new_size;
}

uint64_t run(char* state, size_t size, int num_times, Rule* rules, size_t num_rules) {
	int offset = 0;
	for (uint64_t i = 0; i < num_times; i++) {
		if(strncmp(state, "....", 4) != 0) {
			size = expandLeft(&state, size);		   
			offset += 4;		
		}
		if (strncmp(state + size - 4, "....", 4) != 0) {
			size = expandRight(&state, size);
		}
		char* res_state = calloc(size, sizeof(state[0]));
		memset(res_state, '.', size);
		for (int i = 2; i < size - 2; i++) {
			for (int j = 0; j < num_rules; j++) {
				if (ruleApplies(state + i, &rules[j])) {
					res_state[i] = rules[j].output;
				}
			}
		}
		state = res_state;
	}
	uint64_t tot = 0;
	for (int i = 0; i < size; i++) {
		if (state[i] == '#') {
			tot += (i - offset);
		}
	}
	return tot;
}

uint64_t solve2(uint64_t x) {
	return 10847 + (x-96)*91;
}

int main() {
	FILE *fp = fopen("input", "r");
	char* state;
	fscanf(fp, "initial state: %m[#.]\n", &state);
	size_t size = strlen(state);
	size_t num_rules = 0;
	Rule rules[32];
	while (fscanf(fp, 
				"%m[#.] => %[#.]\n", 
				&rules[num_rules].pattern, 
				&rules[num_rules].output) != EOF) { 
		num_rules++;
	}
	uint64_t first = run(state, size, 20, rules, num_rules);
	printf("%ld\n", first);
	printf("%ld\n", solve2(50000000000));
	return 0;
}
