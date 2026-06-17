/* Small example to differentiate many dependent variables
 * with respect to a single independent variable.
 * i.e. f: R^1 \to R^n */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double get_radius(double in, double* outcos, double* outsin) {
    double tmp = in*in/2.0+in+1.0;

    *outcos = cos(tmp);
    *outsin = sin(tmp);

    return (*outcos)*(*outcos)+(*outsin)*(*outsin);
}

int main(int argc, char* argv[]) {

    double innum;
    double outcos;
    double outsin;
    double rad;

    if (argc != 2)
    {
        printf("ERROR: some angle should be provided as first argument!\n");
        return EXIT_FAILURE;
    }

    innum = atof(argv[1]);

    rad = get_radius(innum, &outcos, &outsin);

    printf("Radius = %f \t -- \t cos = %f - sin = %f\n", rad, outcos, outsin);
    return EXIT_SUCCESS;
}
