#include <stdio.h>

int main(){
  int N;
  int Q;
  int temp;
  int i;
  int childs[1000002] = {0};
  int counter[1000002] = {0};
  int first[1000002] = {0};
  int stack[1000002] = {0};
  int in[1000002] = {0};
  int out[1000002] = {0};
  scanf("%d %d", &N, &Q);
  for (i = 2; i <= N; i++) {
    scanf("%d", &temp);
    in[i] = temp;
    counter[temp]++;
  }
  
  first[1] = counter[1];
  int prev = first[1];
  for (i = 2; i <= N; i++) {
    if (counter[i] != 0){
      first[i] = counter[i] + prev;
      prev = first[i];
    }
  }

  for (i = 2; i <= N; i++){
    childs[first[in[i]]] = i;
    first[in[i]]--;
  }

  int stackLvl = 1;
  stack[1] = 1;
  int currTime = 0;
  int child;
  while(stackLvl != 0){
    if(counter[stack[stackLvl]] != 0){
      counter[stack[stackLvl]]--;
      currTime++;
      child = childs[first[stack[stackLvl]] + 1];
      first[stack[stackLvl]]++;
      stackLvl++;
      stack[stackLvl] = child;
      in[child] = currTime;
    }
    else{
      child = stack[stackLvl];
      out[child] = currTime;
      stackLvl--;
    }
  }
  int asc, dsc;
  for (i = 0; i < Q; i++) {
    scanf("%d %d", &asc, &dsc);
    if (in[asc] < in[dsc] && out[asc] >= out[dsc])
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}
