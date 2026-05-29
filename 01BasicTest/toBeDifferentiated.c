#include <stdio.h>

float quad_fun(float x, float a, float b, float c); 

int main(int argc, char* argv[]) {
    float res;
    float a,b,c;
    float x;

    /* Some parameters, just because we can */
    a = 2.0;
    b = -1.05;
    c = 0.5;

    x = 1.0;
    res = quad_fun(x, a, b, c);
    printf("Res = %f\n", res);
    return 0;
}

float quad_fun(float x, float a, float b, float c) {
    return a*x*x+b*x+c;
}