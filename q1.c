#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define max(a,b) (a>b?a:b)

void dnc(long long int **restrict c, long long int **restrict a, long long int **restrict b, int rows1 /*n*/, int cols1 /*m*/, int cols2 /*p*/, int starting_col_c, int starting_col_a, int starting_col_b)
{

    int maxval = max(max(rows1, cols1),cols2);

    if( maxval <= 32){

        register long long int** restrict initb = b;

        register long long int *restrict tempc;
        register long long int *restrict tempa;
        register long long int *restrict  tempb;

        for(register int i=0; i<rows1; ++i){
            tempa = *a;
            tempc = *c;
            b = initb;
            for (register int k = starting_col_a; k < starting_col_a +cols1; ++k)
            {
                tempb = *b;
                for (register int j = starting_col_c; j < starting_col_c+cols2; ++j)
                {
                    *(tempc+j) += *(tempa+k) *  *(tempb+j);
                }
                ++b;
            }
            ++c;
            ++a;
        }
        // prlong long intf("Done\n");
        return;
    }
    else if(maxval == rows1){//n
        // a1 = 0;
        register int a2;
        a2 = (rows1>>1);

        dnc(c, a, b, a2, cols1, cols2, starting_col_c, starting_col_a, starting_col_b);
        dnc(c+a2, a+a2, b, rows1 - a2, cols1, cols2, starting_col_c, starting_col_a, starting_col_b);
    }
    else if(maxval == cols2){//p
        register int b2;
        b2 = cols2>>1;

        dnc(c, a, b, rows1, cols1, b2, starting_col_c, starting_col_a, starting_col_b);
        dnc(c, a, b, rows1, cols1, cols2 - b2, starting_col_c + b2, starting_col_a, starting_col_b + b2);
    }
    else {//m
        register int a2;
        a2 = (cols1>>1);

        dnc(c, a, b, rows1, a2, cols2, starting_col_c, starting_col_a, starting_col_b);
        dnc(c, a, b+a2, rows1, cols1 - a2, cols2, starting_col_c, starting_col_a + a2, starting_col_b);
    }
}

int main(){

    // Take input
    int n;
    scanf("%d", &n);

    long long int** restrict arr[n];
    int dim[n][2];
    register int i,j,k;

    for(i=0;i<n;++i){
        scanf("%d %d", &dim[i][0], &dim[i][1]);
        arr[i] = malloc(dim[i][0] * sizeof(long long int *));

        for(j=0;j<dim[i][0];j++){
            arr[i][j] = malloc(dim[i][1] * sizeof(long long int*));
            for (k = 0; k < dim[i][1]; k++){
                scanf("%lld", &arr[i][j][k]);
            }
        }

    }

    register long long int** restrict prev_prod = arr[0];
    register long long int** restrict current_prod = NULL;


    register int current_dim_x = dim[0][0];

    for(i=0;i<n-1;++i){

        current_prod = malloc(current_dim_x * sizeof(long long int*));
        for(j=0;j<current_dim_x;j++){
            current_prod[j] = calloc(dim[i+1][1], sizeof(long long int));
        }

        dnc(current_prod, prev_prod, arr[i+1], current_dim_x, dim[i+1][0], dim[i+1][1], 0, 0, 0);

        // assign current dims to prev dims

        // assign current value to prev value for next iter
        prev_prod = current_prod;

        // unassign
        // current_prod = NULL;
    }

    current_dim_x = dim[0][0];
    k = dim[n-1][1];

    printf("%d %d\n", current_dim_x,k);

    for(i=0;i<current_dim_x;i++){
        for(j=0;j<k;j++){
            printf("%lld ", *(*(prev_prod+i)+j));
        }
        printf("\n");
    }

    return 0;
}
