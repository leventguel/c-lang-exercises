#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

char** create_board(){
  char** chessboard= (char**) malloc(10*sizeof(char **)); /* an array of ten pointers */
  for(char i=0;i<10;i++){
    chessboard[i]=(char*)malloc(10*sizeof(char *)); /* to strings == char array, note second index not given explicitly, yet! */
  }              
  return chessboard;
}
char** initiate_board(char** chessboard){
  for(char i=0;i<10;i++){ /* range of first index */
    for(char j=0;j<10;j++){ /* range of second index */
      chessboard[i][j]='a'; /* init the char arrays chars with the character a */
      printf("%c ",chessboard[i][j]); /* print the array */
    }
    printf("\n");
  }  
  return chessboard;
}

int main(void){
  char** chessboard;
  chessboard=create_board();
  chessboard=initiate_board(chessboard);
  getch();
}
