#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
     
char** create_board(){
  char** chessboard=(char**)malloc(10*sizeof(char **));
  for(char i=0;i<10;i++){
    chessboard[i]=(char*)malloc(10*sizeof(char *));
  }              
  return chessboard;
}
char** initiate_board(char** chessboard){
  for(char i=0;i<10;i++){
    for(char j=0;j<10;j++){
      chessboard[i][j]='a';
      printf("%c ",chessboard[i][j]);
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
