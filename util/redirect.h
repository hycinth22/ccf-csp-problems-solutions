// Usage:
//  redirect_input("sample2.in");
//  disable_stream(clog);

#ifndef CCF_CSP_PROBLEMS_REDIRECT_H
#define CCF_CSP_PROBLEMS_REDIRECT_H
#include <cstdio>
#include <iostream>

void redirect_input(const char *filepath, FILE *stream = stdin);
void redirect_output(const char *filepath, FILE *stream = stdout);

template <class streamType>
void disable_stream(streamType& stream) {
    stream.setstate(std::ios_base::failbit);
}

#endif //CCF_CSP_PROBLEMS_REDIRECT_H
