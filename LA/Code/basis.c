#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int R,C;
void swap(int mat[R][C], int row1, int row2,int col)
{
    for (int i = 0; i < col; i++)
    {
        int temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

void display(int mat[R][C], int row, int col);

int rankOfMatrix(int mat[R][C],int *a)
{
    int rank = C;


    for (int row = 0; row < rank; row++)
    {
        if (mat[row][row])
    {
    //a[row]=1;
    for (int col = 0; col < R; col++)
    {
        if (col != row)
        {
            double mult = (double)mat[col][row] / mat[row][row];
            for (int i = 0; i < rank; i++)
            mat[col][i] -= mult * mat[row][i];

        }
    }
}

    else
    {
        int reduce = 1;
        for (int i = row + 1; i < R; i++)
        {
            if (mat[i][row])
            {
                swap(mat, row, i, rank);
                reduce = 0;
                break ;
            }
        }
        if (reduce)
        {
            a[row]=-1;
            rank--;
            for (int i = 0; i < R; i ++)
            mat[i][row] = mat[i][rank];

        }
        row--;
    }
}
return rank;
}

void display(int mat[R][C], int row, int col)
{
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        printf(" %d", mat[i][j]);
        printf("\n");
    }
}

void printbasis(int mat[R][C],int *a,int x)
{
    printf("Basis for the given matrix\n");
    for(int j=0;j<x;j++)
    {
        printf("( ");
        if(a[j]!=-1)
        {
            for(int i=0;i<R;i++)
            {
                printf("%d",mat[i][j]);
            }
        }
        printf(")");
        printf("\n");
    }
}

int main()
{
    clock_t start,end;
    printf("Enter the number of rows:\n");
    scanf("%d",&R);
    printf("Enter the number of columns:\n");
    scanf("%d",&C);
    int mat[R][C];
    int mat1[R][C];
    for(int i=0;i<R;i++)
    for(int j=0;j<C;j++)
    {
        mat[i][j]=rand();
        mat1[i][j]=mat[i][j];
    }
    
    int x;


    if(R<C)
    {
      x=R;
    }
    else {
      x=C;
    }

    int a[x];
    for(int i=0;i<x;i++)
    a[i]=1;
    start=clock();
    int rank=rankOfMatrix(mat,a);
    if(rank>x)
    rank=x;
    printf("\n");
    end=clock();
    printbasis(mat1,a,x);
    printf("%d is the dimension .\n",rank);
    printf("The time taken for this executionis %lf\n",((double)(end-start))/CLOCKS_PER_SEC);
    return 0;
}
