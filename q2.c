#include<stdio.h>
#include <stdlib.h>
#include<time.h>

#define MAXX 1000000000

int main(){

    int v,e;
    register int** M;
    register int i,j,k;

    scanf("%d %d", &v, &e);

    register int all = v;
    M = (int**)malloc(all * sizeof(int*));

    for(i=0;i<all;++i){
        M[i] = (int*)malloc(all * 4);
        for(j=0;j<all;++j)
            M[i][j] = MAXX;
    }
    int x,y,w;
    for(i=0;i<e;++i){
        scanf("%d %d %d", &x, &y, &w);
        M[x-1][y-1] = w;
    }


    for(int i=0;i<v;++i){
        M[i][i] = 0;
    }


    register int temp;
    register int A;
    register int* restrict B;
    register int* restrict C;

    for(k = all-1 ; k >=0 ; --k){
        B = *(M+k);
        for(i = all-1 ; i >=0 ; --i){
            C = *(M+i);
            A = *(C+k);
            for(j = all-1 ; j>=0;--j){
                temp = A + *(B+j);
                if( *(C+j) > temp ){
                    *(C+j) =  temp;
                }
            }
        }
    }


    for(int i=0;i<v;i++){
        for(int j=0;j<v;++j){
            if(M[i][j] == MAXX){
                printf("%d ", -1);
            }
            else{
                printf("%d ", M[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}