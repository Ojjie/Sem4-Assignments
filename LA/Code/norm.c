#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n,m;
    printf("Enter the dimensions:");
    scanf("%d%d",&n,&m);
    
    float mat[n][m];

    printf("Enter the elements\n");

    for(int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<m ; j++)
        {
            scanf("%f",&mat[i][j]);
        }
    }
    
    float ratio = 0;
    float length = 0;
    for (int i=1 ; i<m ; i++)
    {
        for(int k=i-1 ; k>=0 ; k--)
        {
            for (int l=0 ; l<n ; l++)
            {
                ratio += mat[l][i]*mat[l][k];
            }
            for (int p=0 ; p<n ; p++)
            {
                length += mat[p][k]*mat[p][k];
            }
            ratio = ratio/length;
            for (int l=0 ; l<n ; l++)
            {
                mat[l][i] -= ratio*mat[l][k];
            }
            ratio = 0;
            length = 0;
            for (int u=0 ; u<n ; u++)
            {
                length += mat[u][i]*mat[u][i];
            }
            printf("%f\n",length);
            for (int z=0 ; z<n ; z++)
            {
                mat[z][i] = mat[z][i]/sqrt(length);
            }
            length = 0;
        }
    }
    length = 0;
    for (int i=0 ; i<n ; i++)
    {
        length += mat[i][0] * mat[i][0];
    }
    for (int i=0 ; i<n ; i++)
    {
        mat[i][0] = mat[i][0]/sqrt(length);
    }
   
    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<m ; j++)
        {
            printf("%f ",mat[i][j]);
        }
        printf("\n");
    }

}