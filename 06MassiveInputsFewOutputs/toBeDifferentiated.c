/* Example of code highlighting the complexity of computing gradients in the presence of many inputs 
 * It shows the importance of both vector mode and reverse mode AD
 */

#include <stdio.h>
#include <math.h>

double compute_avg(int n, double values[n]){
    double s = values[0];
    for(int i = n-1; i > 0; --i){
        s += values[i];
    }
    return s/n;
}

double compute_mean_abs_deviation(int n, double values[n]) {
    // Clearly, we can do better in computing everything, but this is not the point of the demonstration.
    double avg = compute_avg(n,values); 
    double s;
    s= fabs(values[0] - avg);
    for(int i=n-1; i > 0; --i) {
        s += fabs(values[i] - avg);
    }
    return s/n;
}

double compute_sq_norm(int n, double values[n]) {
    double s = values[0]*values[0];
    for (int i = n-1; i > 0; --i) {
        s += values[i]*values[i];
    }
    return s;
}

double compute_std(int n, double values[n]) {
    double avg = compute_avg(n, values);
    double nsq = compute_sq_norm(n, values);
    return sqrt(nsq/n - avg*avg);
}

double abs_to_std(double a, double s) {
    return (a*a-s*s)/s;
}

void compute_qoi(int n, double values[n], double *average, double *mabs, double *std, double *a_to_s){
    *average = compute_avg(n, values);
    *mabs = compute_mean_abs_deviation(n, values);
    *std = compute_std(n, values);
    *a_to_s = abs_to_std(*mabs, *std);
}

int main(int argc, char* argv[]){
    int n = 200;
    double values[n];

    values[n-1] = 32.01;

    // Fill some values
    for(int i = n-1; i > 0; --i){
        values[i-1] = 2.0*sqrt(values[i])*i + exp(-values[i]);
    }

    double average, mabs, std, as;

    compute_qoi(n, values, &average, &mabs, &std, &as);
    printf("Avg = %f\t Mean abs deviation = %f\t Standard deviation = %f\t Our metric = %f\n", average, mabs, std, as);
}