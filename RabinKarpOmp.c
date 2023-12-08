#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>
#define MAX_LENGTH 1000
char word[MAX_LENGTH], pattern[MAX_LENGTH];
double time , time1 , time2;

int CalculateHash(char s[], int start, int end)
{
    int i, val = 0, power = 1, j = 0, diff;
    diff = end - start + 1;

    for (i = end; j < diff; i--)
    {
        val += (s[i] - 'a' + 1) * power;
        power *= 10;
        j++;
    }

    return val;
}

void RabinKarp()
{
    int i, j, start, end, curr_val, act_val;
    bool found;
    printf("Enter the pattern to be found: ");
    scanf("%s", pattern);

    int len = strlen(word);
    int sublen = strlen(pattern);

    if(len == 0 || sublen == 0 || sublen > len)
    {
        printf("Invalid Inputs.\n");
        return ;
    }

    act_val = CalculateHash(pattern, 0, sublen - 1);

    int iterations = len - sublen + 1;


    omp_set_num_threads(iterations);
    time1 = omp_get_wtime();

    found = false;
    #pragma omp parallel for ordered private(curr_val) schedule(static)
    for(i = 0 ; i < iterations ; i++)
    {
        #pragma omp ordered
        {
            start = i;
            end = i + sublen - 1;
            curr_val = CalculateHash(word , start , end);

            if(curr_val == act_val)
            {
                printf("The pattern exists from index %d to %d in the string found by thread %d of %d threads\n", start, end , omp_get_thread_num() , omp_get_max_threads());
                found  = true;
            }
        }
    }

    time2 = omp_get_wtime();
    time = time2 - time1;
    printf("The time taken is: %.8f\n" , time);
    
    if(!found)
    {
        printf("The pattern does not exist in the string");
    }
}

int main()
{
    int choice;
    printf("--------------------------------------------------------\n");
    printf("\t\t RABIN KARP ALGORITHM OPENMP  \t\t\n");
    printf("--------------------------------------------------------\n");
    do
    {
        printf("\nEnter your choice: \n");
        printf("1. Enter string manually \n");
        printf("2. Read from file \n");
        printf("3. Exit \n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter the string: ");
            fflush(stdin);
            if (fgets(word, MAX_LENGTH, stdin) == NULL)
            {
                printf("Error reading the string from input.\n");
                return 1;
            }
            printf("String length: %d\n" , strlen(word));
            RabinKarp();
            printf("--------------------------------------------------------\n");
        }
        else if (choice == 2)
        {
            FILE *filePointer;
            char fileName[MAX_LENGTH];

            printf("Enter the file name: ");
            scanf("%s", fileName);

            filePointer = fopen(fileName, "r");

            if (filePointer == NULL)
            {
                printf("Unable to open the file %s.\n", fileName);
                return 1;
            }

            if (fgets(word, MAX_LENGTH, filePointer) == NULL)
            {
                printf("Error reading the string from the file.\n");
                fclose(filePointer);
                return 1;
            }
            fclose(filePointer);
            printf("String length: %d\n" , strlen(word));
            RabinKarp();
            printf("--------------------------------------------------------\n");
        }
        else if (choice == 3)
        {
            return 0;
        }
        else
        {
            printf("Wrong input! Please Enter again. \n");
            printf("--------------------------------------------------------\n");
        }
    } while (choice != 3); 

    return 0;
}