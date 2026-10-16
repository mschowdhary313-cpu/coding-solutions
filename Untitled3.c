#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cross-platform sleep function
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#define WIDTH 60
#define HEIGHT 25

// Function to render the grid without screen flickering
void printGrid(int grid[HEIGHT][WIDTH]) {
    printf("\033[H"); // Move cursor back to top-left
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(grid[i][j] ? '#' : ' ');
        }
        putchar('\n');
    }
    fflush(stdout);
}

int main() {
    int grid[HEIGHT][WIDTH];
    int nextGrid[HEIGHT][WIDTH];

    srand(time(NULL));

    // Initialize the grid with random living cells (~30% density)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = (rand() % 100 < 30) ? 1 : 0;
        }
    }

    printf("\033[2J"); // Clear screen once at the start

    // Infinite evolution loop
    while (1) {
        printGrid(grid);

        // Calculate the next generation of cells
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int neighbors = 0;

                // Count living neighbors (with wrap-around edges)
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = (i + di + HEIGHT) % HEIGHT;
                        int nj = (j + dj + WIDTH) % WIDTH;
                        neighbors += grid[ni][nj];
                    }
                }

                // Apply Game of Life rules
                if (grid[i][j] && (neighbors == 2 || neighbors == 3)) {
                    nextGrid[i][j] = 1; // Lives on
                } else if (!grid[i][j] && neighbors == 3) {
                    nextGrid[i][j] = 1; // Reproduction
                } else {
                    nextGrid[i][j] = 0; // Dies (underpopulation or overpopulation)
                }
            }
        }

        // Copy next generation into current grid
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                grid[i][j] = nextGrid[i][j];
            }
        }

        SLEEP(120); // Control the speed of evolution
    }

    return 0;
}
