#include <stdio.h>
#include "square.h"
#include "interface.h"
#include <math.h>

float f1(float x);
float f2(float x);
float f3(float x);

float f_integral_test(float x);
float f1_crossing_test(float x);
float f2_crossing_test(float x);

int main(int argc, char* argv []) {

    args_res_t args = read_args(argc, argv);

    if(args.clc){
        square_cross_t crosses[] = {
                [0] = {
                        .f1 = f1,
                        .f2 = f2,
                },
                [1]= {
                        .f1 = f1,
                        .f2 = f3,
                },
                [2] = {
                        .f1 = f2,
                        .f2 = f3,
                }
        };

        int n = sizeof(crosses) / sizeof (crosses[0]);

        get_crosses(crosses, n, 0.01, args.steps);

        sort_crosses_and_fill_ends(crosses, n);

        if(args.crosses){
            for(int i = 0; i < n; ++i){
                printf("cross %d: x=%.3f\n", i + 1, crosses[i].start_cross);
            }
        }

        get_squares(crosses, n, 0.01);

        float square_sum = get_sum_square(crosses, n);

        printf("square of figure: %f\n", square_sum);
    }
    else if(args.test){
        printf("Testing program\n");
        float abs_test = root(f1_crossing_test, f2_crossing_test, -10, 10, 0.001, 0);
        float integral_test = integral(f_integral_test, -5, 10, 0.01);
        printf("Abscissa of crossing functions y(x)=x and y(x)=2-x: %.3f\n", abs_test);
        printf("Integral of function y(x) = x from -5 to 10: %.3f\n", integral_test);
    }
    else
        print_help();

    return 0;
}

float f1(float x)
{
    return 0.6 * x + 3;
}

float f2(float x)
{
    float x_2 = x - 2;

    return x_2 * x_2 * x_2 - 1;
}

float f3(float x)
{
    return 3.0 / x;
}

float f_integral_test(float x)
{
    return x;
}

float f1_crossing_test(float x)
{
    return x;
}

float f2_crossing_test(float x)
{
    return 2 - x;
}