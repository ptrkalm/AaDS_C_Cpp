#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"

int main(){

  int N;
  char command;
  long long int x;
  Tree tree;
  Node* suspect;
  srand(time(NULL));

  if(scanf("%d", &N) < 0) return 0;
  for(int i = 0; i < N; i++){
    if(scanf(" %c %lld", &command, &x) < 0) return 0;
    if      (command == 'I')
      tree.insertNode(x);
    else if (command == 'D'){
      if(tree.deleteNode(x)) printf("OK\n");
      else printf("BRAK\n");
    }
    else if (command == 'U'){
      suspect = tree.upperNode(x);
      if(suspect != nullptr)
        printf("%lld\n", suspect->value);
      else
        printf("BRAK\n");
    }
    else if (command == 'L'){
      suspect = tree.lowerNode(x);
      if(suspect != nullptr)
        printf("%lld\n", suspect->value);
      else
        printf("BRAK\n");
    }
  }
  return 0;
}
