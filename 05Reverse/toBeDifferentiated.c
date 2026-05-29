/* Small example to differentiate many dependent variables
 * with respect to a many independent variable. 
 * i.e. f: R^m \to R^n */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

typedef struct _pt {
    float x;
    float y;
    float z;
    float aff; /* Stands for affinity */
    int nb_neighbours;
} pt;

typedef struct _connection {
    int idx1;
    int idx2;
    float d;
    struct _connection* next;
} connection;

float norm_pts(pt pt1, pt pt2) {
    return (pt1.x-pt2.x)*(pt1.x-pt2.x) + (pt1.y-pt2.y)*(pt1.y-pt2.y) + (pt1.z-pt2.z)*(pt1.z-pt2.z);
}

float compute_similarity(float d, float sigma) {
    float val = exp(-d/sigma);
    return val;
}

float compute_matrices(int nb_pts, float sigma, float max_val, pt pts[nb_pts], connection* cnts, float A[nb_pts][nb_pts], float S[nb_pts][nb_pts]) {
    // Compute all distances and affinity
    for(int i= 0; i < nb_pts; ++i) {
        for(int j= i+1; j < nb_pts; ++j) {
            A[i][j] = norm_pts(pts[i], pts[j])/max_val/max_val;
            // printf("Normalized Distance between points %i and %i is %f\n", i, j, A[i][j]);
            A[j][i] = A[i][j];
            S[i][j] = compute_similarity(A[i][j],sigma);
            S[j][i] = S[i][j];
        }
    }
    
    // Go over all connections to compute and store their distances
    for(connection* conn =cnts; conn != NULL; conn = conn->next) {
        conn->d = A[conn->idx1][conn->idx2];
        pts[conn->idx1].aff *= S[conn->idx1][conn->idx2];
        pts[conn->idx2].aff *= S[conn->idx1][conn->idx2];
        pts[conn->idx1].nb_neighbours++;
        pts[conn->idx2].nb_neighbours++;
    }

    // Return the total affinity (to create some diff variables!)
    float aff = 0;
    for(int i=0; i < nb_pts; ++i) {
        aff += pts[i].aff*pts[i].aff;
    }
    return aff;

}

int main(int argc, char* argv[]) {
    int nb_pts = 5;
    float sigma = 20.0;
    float max_val = 10.0;

    if (argc >= 2) {
        sigma =  atof(argv[1]);
    }
    if (argc >= 3) {
        max_val = atof(argv[2]);
    }
    
    printf("sigma = %f \t -- \t max_val = %f\n", sigma, max_val);

    pt pts[nb_pts];
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
    for(int i = 0; i < nb_pts; ++i) {
        for(int j = 0; j < nb_pts; ++j){
            A[i][j] = 0;
            S[i][j] = 0;
        }
    }

    // Prepare some (not so) random point to point connections
    connection* cnts = NULL;
    connection* next = NULL;

    for( int i=0; i < nb_pts; ++i) {
        for (int j = i+1; j < nb_pts; j += i+1) {
            cnts = (connection*)malloc(sizeof(connection)); 
            cnts->idx1 = i;
            cnts->idx2 = j;
            cnts->d = -1; // not computed yet
            cnts->next = next;
            next = cnts;
        }
    }

    // Visual inspection of the data 
    for(next = cnts; next != NULL; next = next->next) {
        printf("Looking at connection (%i, %i)\n", next->idx1, next->idx2);
    }
    // Call the main driver
    float aff = compute_matrices(nb_pts, sigma, max_val, pts, cnts, A, S);
    printf("Total affinity = %f\n", aff);
    return 0;
}