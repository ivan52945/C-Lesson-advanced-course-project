#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include <unistd.h>

args_res_t read_args(int argc, char* argv [])
{
    args_res_t result_args = {0};

    int err_c = 0;
    int abs_c = 0;
    int steps_c = 0;
    int help_c = 0;
    int test_c = 0;

    int result = 0;

    while((result = getopt(argc, argv, "htas")) != -1) {
        switch(result) {
            case 'h':
                help_c = 1;
                break;
            case 't':
                test_c = 1;
                break;
            case 'a':
                abs_c = 1;
                break;
            case 's':
                steps_c = 1;
                break;
            case '?':
                err_c = 1;
                break;
        }
    }

    if(err_c) {
        printf("bad args\n");
        abort();
    }
    if(help_c && test_c){
        printf("you can't use -h and -t flags on same time");
        abort();
    }
    if((help_c || test_c)  && (abs_c || steps_c)){
        printf("you can't use flags -t and -h with other flags");
        abort();
    }
    result_args.clc = !help_c && !test_c;
    result_args.help = help_c;
    result_args.crosses = abs_c;
    result_args.test = test_c;
    result_args.steps = steps_c;

    return result_args;
}

void print_help(void) {
    printf("CALCULATE SQUARE OF FIGURE BETWEEN FUNCTIONS\n");
    printf(" -h HELP\n");
    printf(" -t TEST FUNCTIONS\n");
    printf(" -s PRINT NUM OF STEPS\n");
    printf(" -a PRINT ABSCISSAS OF CROSSING POINTS\n");
}