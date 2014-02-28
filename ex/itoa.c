#include <stdlib.h>
#include <stdio.h>

int i;

char *itoa(int n)
{
  char *retbuf = malloc(25);
  if(retbuf == NULL)
    {
      fprintf(stderr, "out of memory\n");
      exit(EXIT_FAILURE);
    }

  if(retbuf == NULL)
    return NULL;

  sprintf(retbuf, "%c", n);
  return retbuf;
  free(retbuf);
  retbuf = NULL;
}

char *atoii(int n)
{
  char *retbuf = malloc(25);
  if(retbuf == NULL)
    {
      fprintf(stderr, "out of memory\n");
      exit(EXIT_FAILURE);
    }

  if(retbuf == NULL)
    return NULL;

  sprintf(retbuf, "%d", n);
  return retbuf;
  free(retbuf);
  retbuf = NULL;
}

int main() {
  char number_str[6]= {0};
  int number[5] = {72,69,76,76,79};
  
  for (int i = 0; i <= 4; i++) {
    snprintf(&number_str[i], 5, "%c", *(itoa(number[i])));
  }
  printf("\t%s\n", number_str);

  for (int i = 0; i <= 4; i++) {
    snprintf(&number_str[i], 5, "%d", *(atoii(number[i])));
  }
  printf("\t%s\n", number_str);

  for (int i = 0; i <= 4; i++) {
    snprintf(&number_str[i], 5, "%d", *(itoa(number[i])));
  }
  printf("\t%s\n", number_str);

  for (int i = 0; i <= 4; i++) {
    snprintf(&number_str[i], 5, "%c", *(atoii(number[i])));
  }

  printf("\t%s\n\n", number_str);

  for (int i = 97; i <= 122; i++)
    {
      printf("%d ", *(itoa(i)));
    }

  printf("\n");

  for (int i = 97; i <= 122; i++)
    {
      printf("%c ", *(itoa(i)));
    }

  printf("\n");

  for (int i = 97; i <= 122; i++)
    {
      printf("%2d ", *(atoii(i)));
    }

  printf("\n");

  for (int i = 97; i <= 122; i++)
    {
      printf("%c ", *(atoii(i)));
    }

  printf("\n");

  for (char i = 97; i <= 122; i++)
    {
      printf("%c ", *(itoa(i)));
    }

  printf("\n\n");
  return 0;
}


