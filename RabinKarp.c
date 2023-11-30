#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

char word[1000], pattern[1000];

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

int main()
{
    int i, j, start, end, curr_val, act_val;
    bool found;

    printf("Enter the string: ");
    scanf("%s", word);

    printf("Enter the pattern to be found: ");
    scanf("%s", pattern);

    int len = strlen(word);
    int sublen = strlen(pattern);

    if(len == 0 || sublen == 0 || sublen > len)
    {
        printf("Invalid Inputs.\n");
        return 1;
    }

    act_val = CalculateHash(pattern, 0, sublen - 1);

    int iterations = len - sublen + 1;

    found = false;
    for(i = 0 ; i < iterations ; i++)
    {
        start = i;
        end = i + sublen - 1;
        curr_val = CalculateHash(word , start , end);

        if(curr_val == act_val)
        {
            printf("The pattern exists from index %d to %d in the string\n", start, end);
            found  = true;
        }
    }

    if(!found)
    {
        printf("The pattern does not exist in the string");
    }

    return 0;
}