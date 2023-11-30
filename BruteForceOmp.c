#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

void printarr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n, i, j, k, total = 0;

    printf("Enter the number of points: ");
    scanf("%d", &n);

    int x[n], y[n], hull[n];

    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &x[i], &y[i]);
        hull[i] = -1;
    }

    bool flag;
    int val;

    omp_set_num_threads(n);

    #pragma omp parallel for private(j, k, flag, val) reduction(+ : total)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                flag = true;

                #pragma omp parallel for private(k) shared(flag) schedule(static)
                for (k = 0; k < n; k++)
                {
                    if (i != k && j != k)
                    {
                        val = ((x[j] - x[i]) * (y[k] - y[i])) - ((y[j] - y[i]) * (x[k] - x[i]));
                        if (val <= 0)
                        {
                            flag = false;
                        }
                    }
                }

                #pragma omp critical
                {
                    if (flag)
                    {
                        hull[i] = j;
                        total++;
                        printf("Thread %d found hull point: (%d,%d) -> (%d,%d) out of %d threads\n",omp_get_thread_num(), x[i], y[i], x[j], y[j] , omp_get_max_threads());
                    }
                }
            }
        }
    }

    i = 0;
    int count = 0;
    printf("total = %d\n", total);
    while (true)
    {
        if (count == total)
        {
            break;
        }

        if (hull[i] != -1)
        {
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