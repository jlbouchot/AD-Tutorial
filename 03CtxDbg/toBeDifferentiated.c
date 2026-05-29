/* Small example to differentiate many dependent variables
 * with respect to a single independent variable and validate the diff'ed code
 * i.e. f: R^1 \to R^n */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double get_prod_sum(double in, double* outcos, double* outsin);
double some_tmp_val(const double in);

int main(int argc, char* argv[]) {

    double innum;
    double outcos;
    double outsin;
    double rad;

    if (argc != 2)
    {
        printf("ERROR: radius should be provided as first argument!\n");
        return EXIT_FAILURE;
    }

    innum = atof(argv[1]);

    rad = get_prod_sum(innum, &outcos, &outsin);

    printf("Radius = %f \t -- \t cos = %f - sin = %f\n", rad, outcos, outsin);
    return 0;
}

double some_tmp_val(const double in) {
    return in*in/2.0+in+1.0;
}

double get_prod_sum(double in, double* outcos, double* outsin) {
    double tmp = some_tmp_val(in);

    *outcos = cos(tmp);
    *outsin = sin(tmp);

    return (*outcos)*(*outcos)+(*outsin)*(*outsin);
}
