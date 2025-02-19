#pragma once

typedef struct {
    int clc;
    int help;
    int crosses;
    int test;
    int steps;
} args_res_t;

args_res_t read_args(int argc, char* argv []);

void print_help(void);