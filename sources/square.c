#include "square.h"
#include <math.h>
#include <stdio.h>

static inline float diff(callback  f, callback g, float x)
{
    return f(x) - g(x);
}

static inline int sign(float x)
{
    if(x > 0)
        return 1;
    if(x == 0)
        return 0;
    return -1;
}

/*
 * @brief function, that fill array crossing between functions
 * @param {square_cross_t} arr array of crossing functions
 * @param {int} n length of arr
 * @param {float} eps, accuracy of calculation
 * @param {int} print_steps_n need or not po print number of steps
 */
void get_crosses(square_cross_t arr[], int n, float eps, int print_steps_n)
{
    for(int i = 0; i < n; ++i){
        arr[i].start_cross = root(arr[i].f1, arr[i].f2, -100, 100, eps, print_steps_n);
    }
}

/*
 * @brief function for sorting crosses
 * @param {square_cross_t} arr array of crossings
 * @param {int} n length of arr
 */
void sort_crosses_and_fill_ends(square_cross_t arr[], int n)
{
    square_cross_t tmp;

    for(int i = 0; i < (n - 1); ++i)
        for(int j = i + 1; j < n; ++j){
            if(arr[i].start_cross > arr[j].start_cross){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }

    for(int i = 0; i < (n - 1); ++i){
        arr[i].end_cross = arr[i + 1].start_cross;
    }
}
/*
 * @brief function for finding crosses between functions
 * @param {callback} f, g functions
 * @param {float} xl, xr start and end of find area
 * @param {float} eps, accuracy of calculation
 * @param {int} print_steps_n need or not po print number of steps
 */
float root(callback  f, callback g, float xl, float xr, float eps, int print_steps_n)
{
    int steps = 0;
    float xm, diff_m;
    float diff_l = diff(f, g, xl);
    float diff_r = diff(f, g, xr);
    float xr_r = xr + 1.0;

    while(fabs(xl - xr) > eps){
        steps += 1;

        xm = (xl + xr) / 2;

        diff_m = diff(f, g,xm);

        if(sign(diff_l) != sign(diff_m)){
            xr = xm;
            diff_r = diff_m;
        }
        else if(sign(diff_r) != sign(diff_m)){
            xl = xm;
            diff_l = diff_m;
        }
        else
            return xr_r + 1;
    }

    if(print_steps_n){
        printf("num of steps for finding cross: %d\n", steps);
    }

    return (xl + xr) / 2;
}

/*
 * @brief function for calculating integral
 * @param {callback} f function
 * @param {float} xl, xr start and end of calculation area
 * @param {float} eps, accuracy of calculation
 */
float integral(callback f, float xl, float xr, float eps)
{
    float yr_i;
    float dx = (xr - xl) * eps;
    float yl_i = f(xl);
    float integral = 0;

    for(float x_i = (xl + dx); x_i <= xr; x_i += dx){
        yr_i = f(x_i);
        integral += (yl_i + yr_i) * dx / 2;
        yl_i = yr_i;
    }

    return integral;
}
/*
 * @brief function for finding squares between 2 functions
 * @param {square_cross_t} arr array of functions with start and end if calculation areas
 * @param {int n} length of array
 * @param {float} eps, accuracy of calculation
 */
void get_squares(square_cross_t arr[], int n, float eps)
{
    float xl, xr;

    for(int i = 0; i < (n - 1); ++i){
        xl = arr[i].start_cross;
        xr =  arr[i].end_cross;

        float f1_s = integral(arr[i].f1, xl, xr, eps);
        float f2_s = integral(arr[i].f2, xl, xr, eps);

        arr[i].square = fabs(f1_s - f2_s);
    }
}
/*
 * @brief function for getting summary square
 * @param {square_cross_t} arr array of squares
 * @param {int n} length of array
 */
float get_sum_square(square_cross_t arr[], int n)
{
    float square_sum = 0;

    for(int i = 0; i < n - 1; ++i){
        square_sum += arr[i].square;
    }

    return square_sum;
}