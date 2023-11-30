#include<stdio.h>
#include<stdbool.h>

void printarr(int arr[] , int n)
{
    int i;
    for(i = 0 ; i< n ; i++)
    {
        printf("%d " , arr[i]);
    }
    printf("\n");
}

int main ()
{
    int n,i,j,k, total = 0;

    printf("Enter the number of points: ");
    scanf("%d", &n);

    int x[n] , y[n], hull[n];

    for(i = 0 ; i < n ; i++)
    {
        scanf("%d %d" , &x[i] , &y[i]);
        hull[i] = -1;
    }

    bool flag;
    int val;

    for(i = 0 ; i < n ; i++)
    {
        for(j = 0 ; j < n ; j++)
        {
            if(i != j)
            {
                flag = true;

                for(k = 0 ; k < n ; k++)
                {
                    if(i != k && j != k)
                    {
                        val = ((x[j] - x[i])*(y[k] - y[i])) - ((y[j] - y[i])*(x[k] - x[i]));
                        if(val <= 0)
                        {
                            flag = false;
                            break;
                        }
                    }
                }

                if(flag)
                {
                    hull[i] = j;
                    total++;
                }
            }
        }
    }

    i = 0;
    int count = 0;
    printf("total = %d\n" , total);
    while(true)
    {
        if(count == total)
        {
            break;
        }

        if(hull[i] != -1)
        {
            printf("%d,%d -> %d,%d\n" , x[i] , y[i] , x[hull[i]] , y[hull[i]]);
            i = hull[i];
            count++;
        }
        else
        {
            i++;
        }
    }

    return 0;
}