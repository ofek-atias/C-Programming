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

void single_char_cycle(char str[MAX_STRING_LEN])
{
    char first_char = str[0];
    int i = 0;

    while(str[i+1] != '\0')
    {
        str[i] = str[i+1];
        i++;
    }
    str[i] = first_char;
}



void cycliced_str(char rotated_str[MAX_STRING_LEN][MAX_STRING_LEN], char str[MAX_STRING_LEN])
{
    int i = 0;
    int length = strlen(str);
    char first_char;
    char current_str[MAX_STRING_LEN] = "";

    strcpy(rotated_str[0], str);

    strcpy(current_str, str);

    for (i = 1; i < length; i++)
    {
        single_char_cycle(current_str);
        strcpy(rotated_str[i], current_str);
    }
}


int main() {

    char str[MAX_STRING_LEN] = "";
    char original_str[MAX_STRING_LEN] = "";
    char str_pool[MAX_STRING_POOL_SIZE][MAX_STRING_LEN];
    char rotated_str[MAX_STRING_LEN][MAX_STRING_LEN];

    int pool_counter = 0;
    int pool_len = sizeof(str_pool);
    int match_counter = 0;

    memset(str_pool, 0 , sizeof(pool_len)); //Initialize the pool to be each slot empty

    printf("Enter the search string:\n");
    scanf("%[^\n]", str);  // Reads with spaces
    getchar();

    strcpy(original_str, str);

    lower_string(str);
    cycliced_str(rotated_str,str);
    //printf("%s\n",str);


    printf("Enter the strings pool:\n");

    while ((scanf("%[^\n]", str_pool[pool_counter]) != -1) &&  pool_counter < 20)
    {
        lower_string(str_pool[pool_counter]);
        pool_counter++;
        getchar();
    }

    for(int i = 0; i < strlen(str);i++)
    {
        for (int j = 0; j < pool_counter; j++)
        {
            int cmp = strcmp(rotated_str[i],str_pool[j]);
            if (cmp==0)
                match_counter++;
        }
    } 
    printf("Number of rotations of \"%s\" in the strings pool is: %d\n", original_str, match_counter);

    return 0;
}