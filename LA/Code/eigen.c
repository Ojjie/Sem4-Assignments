// Compute the Eigen value and the corresponding eigenvector 

#include <stdio.h>
#include <math.h>

int main(){
 
 // Max eigen value z_max and eigen vector(s) - z
    int i,j,n;
    float A[40][40],x[40],z[40],e[40],z_max,e_max;
    printf("\nEnter the order of matrix:");
    scanf("%d",&n);
    printf("\nEnter matrix elements row wise\n");

// accepting the elements of the matrix from the user - even floating point values are allowed 
    for(i=1; i<=n; i++){
    
        for(j=1; j<=n; j++){
        
            printf("A[%d][%d]=", i,j);
            scanf("%f",&A[i][j]);
        }
    }
    printf("\nEnter the column vector\n");
    for(i=1; i<=n; i++){
    
        printf("X[%d]=",i);
        scanf("%f",&x[i]);
    }
    do
    {
        for(i=1; i<=n; i++)
        {
            z[i]=0;
            for(j=1; j<=n; j++)
            {
                z[i]=z[i]+A[i][j]*x[j];
            }
        }
        z_max=fabs(z[1]);
        for(i=2; i<=n; i++)
        {
            if((fabs(z[i]))>z_max)
                z_max=fabs(z[i]);
        }
        for(i=1; i<=n; i++)
        {
            z[i]=z[i]/z_max;
        }
        for(i=1; i<=n; i++)
        {
            e[i]=0;
            e[i]=fabs((fabs(z[i]))-(fabs(x[i])));
        }
        e_max=e[1];
        for(i=2; i<=n; i++)
        {
            if(e[i]>e_max)
                e_max=e[i];
        }
        for(i=1; i<=n; i++)
        {
            x[i]=z[i];
        }
    }
    while(e_max>0.001);

    printf("\n The required eigen value is %f",z_max);
    printf("\n\nThe required eigen vector is :\n");

// Generates and prints all the possible eigen vectors (column vectors) associated with the largest eigen value  

    for(i=1; i<=n; i++){
    
        printf("%f\t",z[i]);
    }
   
}