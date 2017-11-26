#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 6
#define NUM_ITERATIONS 100

int old_grid[GRID_SIZE][GRID_SIZE];
int cur_grid[GRID_SIZE][GRID_SIZE];

void print_grid() {
	int x, y;
	for (x = 0; x < GRID_SIZE; x++) {
		for (y = 0; y < GRID_SIZE - 1; y++) { // < GRID_SIZE - 1 to handle printing the last number without the "|"
			printf("%d | ", cur_grid[x][y]);
		}
		printf("%d\n", cur_grid[x][y]);
	}
}

// Note: uses the old grid
int is_cell_alive(int x, int y) {
	if (x == -1) {
		x = GRID_SIZE - 1;
	} else if (x == GRID_SIZE) {
		x = 0;
	}
	if (y == -1) {
		y = GRID_SIZE - 1;
	} else if (y == GRID_SIZE) {
		y = 0;
	}
	return old_grid[x][y];
}

// Points to search around a given cell.
// These are to be used with the same index.
// Example: index 1 should give (x + 0, x + (-1)), to check above the current cell.
int x_mod[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };
int y_mod[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };

// TODO: bail out if count > 3 ?
int determine_cell_next_state(int x, int y, int currently_alive) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		count += is_cell_alive(x + x_mod[i], y + y_mod[i]);
	}
	if ((currently_alive == 1 && count == 2) || count == 3) {
		return 1;
	} else {
		return 0;
	}
}

void run_tick() {
	// TODO: faster way of doing this
	memcpy(old_grid, cur_grid, sizeof(int) * GRID_SIZE * GRID_SIZE);
	memset(cur_grid, 0, sizeof(int) * GRID_SIZE * GRID_SIZE);
	int x, y;
	for (x = 0; x < GRID_SIZE; x++) {
		for (y = 0; y < GRID_SIZE; y++) {
			cur_grid[x][y] = determine_cell_next_state(x, y, old_grid[x][y]);
		}
	}
}

void init_grid() {
	int x, y;
	for (x = 0; x < GRID_SIZE; x++) {
		for (y = 0; y < GRID_SIZE; y++) {
			cur_grid[x][y] = (int) rand() % 2;
		}
	}
}

int main() {
	init_grid();
	printf("Starting grid is:\n");
	print_grid();
	int i;
	for (i = 0; i < NUM_ITERATIONS; i++) {
		printf("Grid %d\n", i + 1);
		run_tick();
		print_grid();
		printf("Press enter to continue...\n");
		getchar();
	}
	print_grid();
	return 0;
}
