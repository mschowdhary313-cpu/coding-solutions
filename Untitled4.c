#include <stdio.h>
#include <math.h>

int main() {
    int width = 70;
    int height = 35;

    char *shades = " .:-=+*#%@";
    int num_shades = 10;

    printf("\n--- C LANGUAGE PROCEDURAL RENAISSANCE PORTRAIT ---\n\n");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Normalize coordinates between -1.0 and 1.0
            float nx = (float)(x - width / 2) / (width / 2);
            float ny = (float)(y - height / 2) / (height / 2);

            // Mathematical approximation of a shaded head and veil geometry
            float face = exp(-(nx * nx * 4.0f + ny * ny * 3.0f));
            float eyes = exp(-(((nx - 0.2f) * (nx - 0.2f)) * 40.0f + ((ny + 0.1f) * (ny + 0.1f)) * 80.0f)) +
                         exp(-(((nx + 0.2f) * (nx + 0.2f)) * 40.0f + ((ny + 0.1f) * (ny + 0.1f)) * 80.0f));

            float smile = exp(-((nx * nx) * 50.0f + ((ny - 0.3f) * (ny - 0.3f)) * 150.0f));
            float hair = exp(-(nx * nx * 1.2f + (ny + 0.2f) * (ny + 0.2f) * 1.5f)) * (ny < 0.0f ? 1.0f : 0.2f);

            // Combine features into a single gradient intensity value
            float intensity = (face * 0.7f) + (hair * 0.5f) - (eyes * 0.8f) + (smile * 0.3f);

            // Add a frame boundary background
            if (fabs(nx) > 0.85f || fabs(ny) > 0.9f) {
                putchar('#');
            } else {
                // Map intensity to ASCII character ramp
                int val = (int)((intensity + 0.2f) * num_shades);
                if (val < 0) val = 0;
                if (val >= num_shades) val = num_shades - 1;
                putchar(shades[val]);
            }
        }
        putchar('\n');
    }

    printf("\n[Portrait Rendered Successfully via Pure C Math]\n");
    return 0;
}
