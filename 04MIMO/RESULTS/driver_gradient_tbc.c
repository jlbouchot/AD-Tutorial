/* Small example to differentiate many dependent variables
 * with respect to a many independent variable. 
 * i.e. f: R^m \to R^n */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#include <time.h> // For timing things
typedef struct _pt { 
    float x;
    float y;
    float z;
    float aff;
    /* Stands for affinity */
    int nb_neighbours;
} pt;
typedef struct _connection {
    int idx1;
    int idx2;
    float d;
    struct _connection *next;
} connection;

/** TODO:
 * Use the generated and validated code to measure the time required to compute the derivatives
 * Consider here the "simple" tangent differentiation for computing and measuring times.
 * 
 * Continue below with useful diff'ed code (obtained from Tapenade)
 */


float norm_pts_nodiff(pt pt1, pt pt2) {
    return (pt1.x-pt2.x)*(pt1.x-pt2.x) + (pt1.y-pt2.y)*(pt1.y-pt2.y) + (pt1.z-
    pt2.z)*(pt1.z-pt2.z);
}

/*
  Differentiation of compute_matrices in forward (tangent) mode (with options context):
   variations   of useful results: compute_matrices
   with respect to varying inputs: sigma max_val
   RW status of diff variables: compute_matrices:out sigma:in
                max_val:in A:(loc) S:(loc)
   Plus diff mem management of: pts:in A:in A[0:nb_pts-1]:in S:in
                S[0:nb_pts-1]:in
*/
/** TODO: 
 * Update with your generated / differentiated code here! 
 */
float compute_matrices_d(int nb_pts, float sigma, float sigmad, float max_val,
        float max_vald, pt pts[nb_pts], pt_diff ptsd[nb_pts], connection *cnts
        , float A[nb_pts][nb_pts], float Ad[nb_pts][nb_pts], float S[nb_pts][
        nb_pts], float Sd[nb_pts][nb_pts], float *compute_matrices) {
    // Return the total affinity (to create some diff variables!)
    float aff = 0;
    float affd;

    return affd;
}

/*
  Differentiation of main as a context to call tangent code (with options context):
*/
int main(int argc, char *argv[]) {
    int nb_pts = 5;
    float sigma = 20.0;
    float sigmad;
    float max_val = 10.0;
    float max_vald;
    if (argc >= 2)
        sigma = atof(argv[1]);
    if (argc >= 3)
        max_val = atof(argv[2]);
    printf("sigma = %f \t -- \t max_val = %f\n", sigma, max_val);
    pt pts[nb_pts];
    pt_diff ptsd[nb_pts];
    // First point
    pts[0].x = 1.0;
    pts[0].y = 1.0;
    pts[0].z = 1.0;
    pts[0].aff = 1;
    pts[0].nb_neighbours = 0;
    // Second point
    pts[1].x = 0.0;
    pts[1].y = 1.0;
    pts[1].z = 1.0;
    pts[1].aff = 1;
    pts[1].nb_neighbours = 0;
    // Third point
    pts[2].x = 0.0;
    pts[2].y = 0.0;
    pts[2].z = 1.0;
    pts[2].aff = 1;
    pts[2].nb_neighbours = 0;
    // Fourth point
    pts[3].x = -1.0;
    pts[3].y = -1.0;
    pts[3].z = 1.0;
    pts[3].aff = 1;
    pts[3].nb_neighbours = 0;
    // Fifth point
    pts[4].x = -1.0;
    pts[4].y = -1.0;
    pts[4].z = -1.0;
    pts[4].aff = 1;
    pts[4].nb_neighbours = 0;
    // Prepare the data for receiving affinity and similarity matrices
    float A[nb_pts][nb_pts], S[nb_pts][nb_pts];
    float Ad[nb_pts][nb_pts], Sd[nb_pts][nb_pts];
    for (int i = 0; i < nb_pts; ++i)
        for (int j = 0; j < nb_pts; ++j) {
            A[i][j] = 0;
            S[i][j] = 0;
        }
    // Prepare some (not so) random point to point connections
    connection *cnts = (void *)0;
    connection *next = (void *)0;
    for (int i = 0; i < nb_pts; ++i)
        for (int j = i + 1; j < nb_pts; j += i + 1) {
            cnts = (connection *)malloc(sizeof(connection));
            cnts->idx1 = i;
            cnts->idx2 = j;
            cnts->d = -1; // not computed yet
            cnts->next = next;
            next = cnts;
        }
    // // Visual inspection of the data 
    // for (next = cnts; next != (void *)0; next = next->next)
    //     printf("Looking at connection (%i, %i)\n", next->idx1, next->idx2);
    // Call the main driver
    float aff;
    float affd;
    float grad_aff[2] = {0.0,0.0}; // Keep track of the gradient
    // Time things for 1000 of such computations to be compared with the vector mode
    int nb_loops = 1000; 
    clock_t t = clock();
    for(int i=nb_loops+1; i>0; --i) {
        // TODO: Write out the required initialisations for computing the gradient of the function 
        affd = compute_matrices_d(nb_pts, sigma, sigmad, max_val, max_vald, pts, 
                              ptsd, cnts, A, Ad, S, Sd, &aff);
        // TODO: Uncomment if, for some reasons, you need to check your results!
        // printf("Trial %i. dAff/dSigma = %f\n", i, affd);
        
        // TODO: Update your gradient however needed
        

    }
    t = clock() - t;
    printf("Average hand made (over %i trials) Final gradient estimation is: dAff/dsigma = %f and dAff/dmax_val = %f\n", nb_loops, grad_aff[0]/nb_loops, grad_aff[1]/nb_loops);
    printf("%i runs in %f seconds.\n", nb_loops, ((double)t)/CLOCKS_PER_SEC);
    return 0;
}
