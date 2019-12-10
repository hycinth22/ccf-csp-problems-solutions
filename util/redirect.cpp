//
// Created by inked on 2019/12/10 0010.
//
#include <stdio.h>
#include <stdlib.h>

void redirect_input(const char *filepath, FILE *stream) {
#ifdef _DEBUG
    if (!freopen(filepath, "r", stream)) {
        exit(255);
    }
#endif
}

void redirect_output(const char *filepath, FILE *stream) {
#ifdef _DEBUG
    if (!freopen(filepath, "w", stream)) {
        exit(255);
    }
#endif
}