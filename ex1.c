#include <stdio.h>


void player_choice(int name,char board[10][10],int size);
void board_print(char board[10][10],int size);
int win_check(int name, char board[10][10], int size);
int tie_check(char board[10][10], int size);


void player_choice(int name,char board[10][10],int size)
{
    int pos_row = -1, pos_col = -1;
    printf("Player %d, please insert your move:\n",name);
    scanf("%d,%d",&pos_row,&pos_col);
    while((pos_row < 1) || (pos_row > size) || (pos_col < 1) || (pos_col > size)||(board[pos_row-1][pos_col-1] == 'X') || (board[pos_row-1][pos_col-1] == 'O'))
    {
        if((pos_row < 1) || (pos_row > size) || (pos_col < 1) || (pos_col > size))
        {
            printf("Invalid indices (out of bounds), please choose your move again:\n");
             scanf("%d,%d",&pos_row,&pos_col);
        }
        else if((board[pos_row-1][pos_col-1] == 'X') || (board[pos_row-1][pos_col-1] == 'O'))
        {
            printf("Invalid indices (occupied cell), please choose your move again:\n");
             scanf("%d,%d",&pos_row,&pos_col);
        }

    }
    
    switch (name)
    {
        case 1:
            board[pos_row-1][pos_col-1] = 'X';
            break;
         case 2:
            board[pos_row-1][pos_col-1] = 'O';
            break;
    } 
    board_print(board, size);

}
void board_print(char board[10][10],int size)
{
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size;j++)
        {
            printf("%c",board[i][j]);
            if (j!=size-1)
                printf(" ");
        }
        printf("\n");
    }
}

int win_check(int name, char board[10][10], int size)
{
    int count_row = 0;
    int count_col = 0;
    int count_diag = 0;
    int count_anti_diag = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (name == 1)
            {
                if (board[i][j] == 'X')
                    count_row +=1;
                if (board[j][i] == 'X')
                    count_col +=1;
            }
            else 
            {
                if (board[i][j] == 'O')
                    count_row +=1;
                if (board[j][i] == 'O')
                    count_col +=1;
            }

            
        }
        if (count_row == size || count_col == size)
            return name;
        count_row = 0;
        count_col = 0;

    }
   
    for (int i = 0; i < size; i++)
    {
        if (name == 1)
        {
            if (board[i][i] == 'X')
                count_diag +=1;
            if (board[i][size-1-i] == 'X')
                count_anti_diag +=1;
            
        }
        else 
        {
            if (board[i][i] == 'O')
                count_diag +=1;
            if (board[i][size-1-i] == 'O')
                count_anti_diag +=1;
        }
    }
    if (count_diag == size || count_anti_diag == size)
            return name;
    
    return 0;


}

int tie_check(char board[10][10], int size)
{
    int count = 0;
    int count_x_row = 0;
    int count_o_row = 0;
    int count_x_col = 0;
    int count_o_col = 0;
    int count_x_diag = 0;
    int count_o_diag = 0;
    int count_x_anti_diag = 0;
    int count_o_anti_diag = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 'X')
                count_x_row +=1;
            if (board[i][j] == 'O')
                count_o_row +=1;

            if (board[j][i] == 'X')
                count_x_col +=1;
            if (board[j][i] == 'O')
                count_o_col +=1;
        }
        if (count_x_row > 0 && count_o_row > 0)
            count ++;
        
        if (count_x_col > 0 && count_o_col > 0)
            count ++;    
        count_x_row = 0;
        count_o_row = 0;
        count_x_col = 0;
        count_o_col = 0;

    }
   
    for (int i = 0; i < size; i++)
    {
        if (board[i][i] == 'X')
            count_x_diag +=1;
        if (board[i][i] == 'O')
            count_o_diag +=1;
        
        if (board[i][size-1-i] == 'X')
            count_x_anti_diag +=1;       
        if (board[i][size-1-i] == 'O')
            count_o_anti_diag +=1;
    }
    if (count_x_diag > 0 && count_o_diag > 0)
        count ++;
        
    if (count_x_anti_diag > 0 && count_o_anti_diag > 0)
        count ++;   

    if (count == size*2+2)
            return 1;
    
    return 0;


}


int main()
{
    char board[10][10];
    int size = 0;
    int current_player = 1;

    printf("Please enter the board size N [1-10]:\n");
    scanf("%d",&size);
    printf("Welcome to %dx%d Tic-Tac-Toe:\n",size,size);
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size;j++)
        {
            board[i][j] = '_';
            printf("%c",board[i][j]);
            if (j!=size-1)
                printf(" ");
        }
        printf("\n");
    }
    while (win_check(1,board,size) == 0 && win_check(2,board,size) == 0 && tie_check(board,size) == 0)
    {
        if (current_player % 2 == 1)
            player_choice(1,board,size);
        else
            player_choice(2,board,size);
        current_player = (current_player%2) + 1;
    }
    if (win_check(1,board,size) == 1)
        printf("Player 1 is the winner!\n");
    else if (win_check(2,board,size) == 2)
        printf("Player 2 is the winner!\n");
    else if (tie_check(board,size) ==1)
        printf("There is a Tie!\n");


    return 0;
}