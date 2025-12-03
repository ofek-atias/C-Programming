#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 11
#define MAX_STRING_POOL_SIZE 20

void lower_string(char str[MAX_STRING_LEN])
{
    int j = 0;
    
    while (str[j] != '\0') 
    {
        str[j] = tolower((unsigned char)str[j]); 
        j++;
    }
}

int main() {

    char str[MAX_STRING_LEN];
    char str_pool[MAX_STRING_POOL_SIZE][MAX_STRING_LEN];

    int counter = 0;
    int pool_len = 0;

    memset(str_pool, 0 , sizeof(str_pool)); //Initialize the pool to be each slot empty

    printf("Enter the search string:\n");
    scanf("%10s", str);

    lower_string(str);
    //printf("%s\n",str);


    printf("Enter the strings pool:\n");

    while ((fgets(str_pool[counter], MAX_STRING_POOL_SIZE , stdin) != NULL) &&  counter < 20)
    {
        lower_string(str_pool[counter]);
        //printf("%s", str_pool[counter]);
        counter++;
    }
    return 0;
}