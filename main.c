#include <stdio.h>
#include <stdlib.h>

// Returns the y position at x
// This function is used to return the positions of both initial units and dynamic units
int getPosition(int *board, int x){
    if(board[x]>0) return board[x]-1;
    else if(board[x]<0) return -(board[x])-1;
    else return -1;
}

// Checks if the unit at (x, getposition(x)) conflicts with other units on the board
int checkConflict(int *board, int n, int x){
    int y = getPosition(board, x);
    int i;
    int t;

    if(y<0) return 0;

    // Check vertical slots
    for (i = 0; i < n; i++)
        if (x!=i && getPosition(board, i) == y ) return 1;

    // Check longer L
    if (x > 1){
        t=getPosition(board, x-2);
        if(t>=0 && (t == y+1 || t == y-1)) return 1;
    }

    if(x < n-2){
        t=getPosition(board, x+2);
        if(t>=0 && (t == y+1 || t == y-1)) return 1;
    }

    // Check shorter L
    if(x > 0){
        t=getPosition(board, x-1);
        if(t>=0 && (t == y+2 || t == y-2)) return 1;
    }

    if(x < n-1){
        t=getPosition(board, x+1);
        if(t>=0 && (t == y+2 || t == y-2)) return 1;
    }
    return 0;
}


int findnextSlot(int *board, int n, int x){
    while(board[x]!=0 && x<n) x++;
    return x;
}

int printBoard(int *board, int n, int sCount){
    int i,j;
    printf("%d:\n", sCount);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            if(i == getPosition(board, j))
                if(board[i] < 0) printf(" I");
                else printf(" C");
            else printf(" _");
        printf("\n");
    }
}

int checkBoard(int *board, int n){
    int i=0;
    for(i=0;i<n;i++) if(checkConflict(board, n, i)) return 1;
    return 0;
}

int nChancellors(int *board, int n){
    int solutions = 0;
    int x = findnextSlot(board, n, 0);
    while(x>=0){
        if(board[x] >= 0) do board[x]++; while(getPosition(board, x) < n && checkConflict(board, n, x));

        if (getPosition(board,x) < n && board[x] >= 0){
            if (x < n-1) x = findnextSlot(board, n, x);
            else printBoard(board, n, ++solutions);
        }else{
            if(board[x]>0) board[x] = 0;
            if(board[--x]<0) x--;
        }
    }
    return solutions;
}

int main(void)
{
    int i,j,k,n,s;
    FILE *fp = fopen("input.txt", "r");
    fscanf(fp, " %d", &n);
    for(i=0;i<n;i++){
        printf("Solving problem %d:\n", i+1);
        fscanf(fp, " %d", &s);

        int *board = malloc(sizeof(int) * s);
        int hasConflict = 0;
        for(int j=0;j<s;j++) board[i] = 0;
        for(int j=0;j<s;j++) for(int k=0;k<s;k++){
            int tmp;
            fscanf(fp, " %d", &tmp);
            if(tmp > 0)
                if(board[k]==0) board[k] = -(j+1);
                else hasConflict = 1;
        }
        if(checkBoard(board, n) || hasConflict)
            printf("UH OH! There is a conflict in the initial board.\nNumber of solutinos: 0\n\n");
        else
            printf("Number of solutions: %d\n\n", nChancellors(board, s));
    }
    return 0;
}
