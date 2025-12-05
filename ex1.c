#include <stdio.h>

#define MAX_BOARD_SIZE 10
#define PLAYER_ONE 1
#define PLAYER_TWO 2

#define FALSE 0
#define TRUE 1

#define VALID_CELL_VALUE 1
#define OUT_OF_BOUNDS_ERR_CODE -1
#define OCCUPIED_CELL_ERR_CODE -2

void player_choice(int name,char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],int size);
void board_print(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],int size);
int win_check(int name, char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
int tie_check(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size);
int check_cell_validity(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int pos_row, int pos_col, int size);

int check_cell_validity(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int pos_row, int pos_col, int size) {
    if ((pos_row < 1) || (pos_row > size) || (pos_col < 1) || (pos_col > size)) {
        return OUT_OF_BOUNDS_ERR_CODE;
    }

    if ((board[pos_row-1][pos_col-1] == 'X') || (board[pos_row-1][pos_col-1] == 'O')) {
        return OCCUPIED_CELL_ERR_CODE;
    }

    return VALID_CELL_VALUE;
}

void player_choice(int name, char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size)
{
    int pos_row = -1, pos_col = -1, validity_indicator = VALID_CELL_VALUE;
    printf("Player %d, please insert your move:\n", name);
    scanf("%d,%d", &pos_row, &pos_col);
    
    validity_indicator = check_cell_validity(board, pos_row, pos_col, size);
    while (validity_indicator == OUT_OF_BOUNDS_ERR_CODE || validity_indicator == OCCUPIED_CELL_ERR_CODE) {
        if (validity_indicator == OUT_OF_BOUNDS_ERR_CODE) {
            printf("Invalid indices (out of bounds), please choose your move again:\n");
        }
        else if (validity_indicator == OCCUPIED_CELL_ERR_CODE) {
            printf("Invalid indices (occupied cell), please choose your move again:\n");
        }
        
        scanf("%d,%d",&pos_row,&pos_col);
        validity_indicator = check_cell_validity(board, pos_row, pos_col, size);
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
void board_print(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (j == size - 1)
                printf("%c", board[i][j]);
            else
                printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int win_check(int name, char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size)
{
    int count_row = 0;
    int count_col = 0;
    int count_diag = 0;
    int count_anti_diag = 0;

    char player_char = (name == PLAYER_ONE) ? 'X' : 'O';

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == player_char)
                count_row +=1;
            if (board[j][i] == player_char)
                count_col +=1;
        }
        if (count_row == size || count_col == size)
            return TRUE;
        count_row = 0;
        count_col = 0;

    }
   
    for (int i = 0; i < size; i++)
    {
        if (board[i][i] == player_char)
            count_diag +=1;
        if (board[i][size-1-i] == player_char)
            count_anti_diag +=1;
    }
    if (count_diag == size || count_anti_diag == size)
            return TRUE;
    
    return FALSE;
}

int tie_check(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size)
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
            count++;
        
        if (count_x_col > 0 && count_o_col > 0)
            count++;
            
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
        count++;
        
    if (count_x_anti_diag > 0 && count_o_anti_diag > 0)
        count++;   

    if (count == size*2 + 2)
            return TRUE;
    
    return FALSE;
}


int main()
{
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int size = 0;
    int current_player = PLAYER_ONE;

    printf("Please enter the board size N [1-10]:\n");
    scanf("%d", &size);
    printf("Welcome to %dx%d Tic-Tac-Toe:\n", size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = '_';

            if (j == size - 1)
                printf("%c", board[i][j]);
            else
                printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    while (win_check(PLAYER_ONE, board, size) == FALSE && win_check(PLAYER_TWO, board, size) == FALSE && tie_check(board, size) == FALSE)
    {
        if (current_player % 2 == PLAYER_ONE)
            player_choice(PLAYER_ONE, board, size);
        else
            player_choice(PLAYER_TWO, board, size);
        current_player = (current_player % 2) + 1;
    }

    if (win_check(PLAYER_ONE, board, size) == TRUE)
        printf("Player 1 is the winner!\n");
    else if (win_check(PLAYER_TWO, board, size) == TRUE)
        printf("Player 2 is the winner!\n");
    else if (tie_check(board, size) == TRUE)
        printf("There is a Tie!\n");

    return 0;
}