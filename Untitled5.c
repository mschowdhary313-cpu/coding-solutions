#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_RECURSION 3
#define EPSILON 0.001f

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 center;
    float radius;
    Vector3 color;
    float reflectivity;
} Sphere;

typedef struct {
    Vector3 position;
    Vector3 color;
} Light;

// Vector Math Operations
Vector3 v_add(Vector3 a, Vector3 b) { return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z}; }
Vector3 v_sub(Vector3 a, Vector3 b) { return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z}; }
Vector3 v_mul(Vector3 a, float scalar) { return (Vector3){a.x * scalar, a.y * scalar, a.z * scalar}; }
float v_dot(Vector3 a, Vector3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vector3 v_normalize(Vector3 v) {
    float len = sqrt(v_dot(v, v));
    return len > 0 ? (Vector3){v.x / len, v.y / len, v.z / len} : v;
}

// Ray-Sphere Intersection Test
int intersect_sphere(Sphere s, Ray r, float *t) {
    Vector3 oc = v_sub(r.origin, s.center);
    float b = 2.0f * v_dot(oc, r.direction);
    float c = v_dot(oc, oc) - s.radius * s.radius;
    float discriminant = b * b - 4.0f * c;

    if (discriminant < 0) return 0;

    float sqrt_disc = sqrt(discriminant);
    float t0 = (-b - sqrt_disc) / 2.0f;
    float t1 = (-b + sqrt_disc) / 2.0f;

    if (t0 > EPSILON) { *t = t0; return 1; }
    if (t1 > EPSILON) { *t = t1; return 1; }
    return 0;
}

// Trace Ray through the 3D Scene
Vector3 trace(Ray r, Sphere *spheres, int num_spheres, Light light, int depth) {
    if (depth > MAX_RECURSION) return (Vector3){0, 0, 0};

    float nearest_t = 1e20f;
    int hit_index = -1;

    for (int i = 0; i < num_spheres; i++) {
        float t;
        if (intersect_sphere(spheres[i], r, &t)) {
            if (t < nearest_t) {
                nearest_t = t;
                hit_index = i;
            }
        }
    }

    if (hit_index == -1) {
        // Background gradient (sky)
        float t = 0.5f * (v_normalize(r.direction).y + 1.0f);
        return v_add(v_mul((Vector3){1.0f, 1.0f, 1.0f}, 1.0f - t), v_mul((Vector3){0.5f, 0.7f, 1.0f}, t));
    }

    Sphere hit_sphere = spheres[hit_index];
    Vector3 hit_point = v_add(r.origin, v_mul(r.direction, nearest_t));
    Vector3 normal = v_normalize(v_sub(hit_point, hit_sphere.center));

    // Lighting calculation (Diffuse)
    Vector3 light_dir = v_normalize(v_sub(light.position, hit_point));
    float diff = fmaxf(0.0f, v_dot(normal, light_dir));
    Vector3 color = v_mul(hit_sphere.color, diff * 0.8f + 0.2f);

    // Reflection recursion
    if (hit_sphere.reflectivity > 0.0f) {
        Vector3 reflect_dir = v_sub(r.direction, v_mul(normal, 2.0f * v_dot(r.direction, normal)));
        Ray reflect_ray = {v_add(hit_point, v_mul(normal, EPSILON)), reflect_dir};
        Vector3 reflect_color = trace(reflect_ray, spheres, num_spheres, light, depth + 1);

        color = v_add(v_mul(color, 1.0f - hit_sphere.reflectivity),
                      v_mul(reflect_color, hit_sphere.reflectivity));
    }

    return color;
}

int main() {
    printf("Initializing 3D Ray Tracer in C...\n");

    // Define 3D Scene Objects (Spheres)
    Sphere spheres[] = {
        {{0.0f, -1.0f, 5.0f}, 1.5f, {0.8f, 0.2f, 0.2f}, 0.5f},  // Red shiny sphere
        {{2.0f, 0.0f, 6.0f}, 1.0f, {0.2f, 0.8f, 0.2f}, 0.3f},   // Green sphere
        {{-2.0f, 0.0f, 7.0f}, 1.2f, {0.2f, 0.2f, 0.8f}, 0.7f},  // Blue reflective sphere
        {{0.0f, -1001.5f, 5.0f}, 1000.0f, {0.5f, 0.5f, 0.5f}, 0.1f} // Ground floor
    };
    int num_spheres = 4;

    Light light = {{-10.0f, 10.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

    // Allocate frame buffer for pixel data
    Vector3 *buffer = (Vector3 *)malloc(WIDTH * HEIGHT * sizeof(Vector3));

    // Render loop: Cast rays for every pixel
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float u = (float)x / (float)WIDTH;
            float v = (float)(HEIGHT - y) / (float)HEIGHT; // Flip Y axis

            float aspect_ratio = (float)WIDTH / (float)HEIGHT;
            Vector3 dir = {
                (2.0f * u - 1.0f) * aspect_ratio,
                (2.0f * v - 1.0f),
                1.0f
            };

            Ray r = {{0.0f, 0.0f, 0.0f}, v_normalize(dir)};
            buffer[y * WIDTH + x] = trace(r, spheres, num_spheres, light, 0);
        }
    }

    // Output to an image file format (.ppm)
    FILE *f = fopen("output.ppm", "w");
    fprintf(f, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        int ir = (int)(255.99f * fminf(1.0f, buffer[i].x));
        int ig = (int)(255.99f * fminf(1.0f, buffer[i].y));
        int ib = (int)(255.99f * fminf(1.0f, buffer[i].z));
        fprintf(f, "%d %d %d\n", ir, ig, ib);
    }
    fclose(f);
    free(buffer);

    printf("Render complete! Saved as 'output.ppm'. Open it with any image viewer.\n");
    return 0;
}
