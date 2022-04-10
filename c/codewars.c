#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printSolution(int count, unsigned int board[9][9]) {
  printf("solution #%d\n", count);
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
      printf("%d ", board[i][j]);
    printf("\n");
  }
  printf("\n");
}

bool validSolution(unsigned int board[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0)
                return false;
      
            // search for board[i][j] on row i and then on col j
            // if it appears more than once, the solution is invalid
            for (int k = 0; k < 9; ++k)
                if (k == j)
                    continue;
                else if (board[i][k] == board[i][j])
                    return false;
            
            for (int k = 0; k < 9; ++k)
                if (k == i)
                    continue;
                else if (board[k][j] == board[i][j])
                    return false;
        }
    }
    return true;
}

int main(void) {
    unsigned int example1[9][9] =  {{5, 3, 4, 6, 7, 8, 9, 1, 2}, 
                                    {6, 7, 2, 1, 9, 5, 3, 4, 8},
                                    {1, 9, 8, 3, 4, 2, 5, 6, 7},
                                    {8, 5, 9, 7, 6, 1, 4, 2, 3},
                                    {4, 2, 6, 8, 5, 3, 7, 9, 1},
                                    {7, 1, 3, 9, 2, 4, 8, 5, 6},
                                    {9, 6, 1, 5, 3, 7, 2, 8, 4},
                                    {2, 8, 7, 4, 1, 9, 6, 3, 5},
                                    {3, 4, 5, 2, 8, 6, 1, 7, 9}};
                             
    unsigned int example2[9][9] =  {{5, 3, 4, 6, 7, 8, 9, 1, 2}, 
                                    {6, 7, 2, 1, 9, 0, 3, 4, 8},
                                    {1, 0, 0, 3, 4, 2, 5, 6, 0},
                                    {8, 5, 9, 7, 6, 1, 0, 2, 0},
                                    {4, 2, 6, 8, 5, 3, 7, 9, 1},
                                    {7, 1, 3, 9, 2, 4, 8, 5, 6},
                                    {9, 0, 1, 5, 3, 7, 2, 1, 4},
                                    {2, 8, 7, 4, 1, 9, 6, 3, 5},
                                    {3, 0, 0, 4, 8, 1, 1, 7, 9}};
    
    printf("%d\n%d\n", validSolution(example1), validSolution(example2));
    return 0;
}