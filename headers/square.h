#pragma once

typedef float(*callback)(float);

typedef struct {
    callback f1;
    callback f2;
    float start_cross;
    float square;
    float end_cross;
} square_cross_t;

void get_crosses(square_cross_t arr[], int n, float eps, int print_steps_n);

void sort_crosses_and_fill_ends(square_cross_t arr[], int n);

float root(callback  f, callback g, float xl, float xr, float eps, int print_steps_n);

float integral(callback f, float xl, float xr, float eps);

void get_squares(square_cross_t arr[], int n, float eps);

float get_sum_square(square_cross_t arr[], int n);