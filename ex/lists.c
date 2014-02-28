#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct CELL *LIST;
struct CELL {
  int element;
  LIST next;
};

int sum(LIST list);
int find0(LIST list, int x);

LIST merge(LIST list1, LIST list2);
LIST split(LIST list);
LIST MergeSort(LIST list);
LIST MakeList();

void PrintList(LIST list);

int main(void)
{
  int y;
  LIST list;
  list = MakeList();
  PrintList(MergeSort(list));
  printf("sum is %d\n", sum(list));
  scanf("%d", &y);
  printf("found %d %d times \n", y, find0(list, y));
  return 0;
}

void PrintList(LIST list)
{
  while (list != NULL) {
    printf("%d\n", list->element);
    list = list->next;
  }
}

LIST MakeList()
{
  int x;
  LIST pNewCell;
  if (scanf("%d", &x) == EOF) return NULL;
  else {
    pNewCell = (LIST) malloc(sizeof(struct CELL));
    pNewCell->next = MakeList();
    pNewCell->element = x;
    return pNewCell;
  }
}

LIST MergeSort(LIST list)
{
  LIST SecondList;
  if (list == NULL) return NULL;
  else if (list->next == NULL) return list;
  else {
    SecondList = split(list);
    return merge(MergeSort(list), MergeSort(SecondList));
  }
}

LIST split(LIST list)
{
  LIST pSecondCell;
  if (list == NULL) return NULL;
  else if (list->next == NULL) return NULL;
  else {
    pSecondCell = list->next;
    list->next = pSecondCell->next;
    pSecondCell->next = split(pSecondCell->next);
    return pSecondCell;
  }
}

LIST merge(LIST list1, LIST list2)
{
  if (list1 == NULL) return list2;
  else if (list2 == NULL) return list1;
  else if (list1->element <= list2->element) {
    list1->next = merge(list1->next, list2);
    return list1;
  }
  else {
    list2->next = merge(list1, list2->next);
    return list2;
  }
}

int sum(LIST list)
{
  int sum0;
  if (list == NULL) sum0 = 0;
  else sum0 = list->element + sum(list->next);
  return sum0;
}

int find0(LIST list, int x)
{
  static int found = 0;

  while(list != NULL)
    {
      if(list->element == x) 
	{ 
	  found++;
	}
      
      else 
	{}

      find0(list->next, x);      
      return found;
    }

  return 0;
}






















