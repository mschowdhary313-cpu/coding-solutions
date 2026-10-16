#include <stdio.h>

int main() {
    // Loop through coordinates on the complex plane
    for (float y = -1.3f; y < 1.3f; y += 0.07f) {
        for (float x = -2.0f; x < 0.5f; x += 0.03f) {
            float zr = 0.0f, zi = 0.0f;
            int i = 0;

            // Mandelbrot math iteration
            while (i < 50 && (zr * zr + zi * zi) < 4.0f) {
                float temp = zr * zr - zi * zi + x;
                zi = 2.0f * zr * zi + y;
                zr = temp;
                i++;
            }

            // Print characters based on escape speed
            if (i == 50) {
                putchar(' '); // Inside the set
            } else {
                char shades[] = ".-:=+*#%@";
                putchar(shades[i % 9]); // Gradient shading for the edge
            }
        }
        putchar('\n');
    }

    printf("\n[C Language Fractal Generated Successfully!]\n");
    return 0;
}
