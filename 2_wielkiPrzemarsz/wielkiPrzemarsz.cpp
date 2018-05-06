#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include <queue>

#define MAX_CORD 1000000002
#define MAX_RES 999979
#define MAX_EDG 500002
#define MAX_VRT 1000002

int main()
{
  unsigned long int n, m;
  unsigned int t;
  unsigned int i;
  unsigned long int a1, b1, a2, b2;
  std::unordered_map<unsigned long long int, unsigned int> reorder;
  unsigned int arrows[MAX_EDG][2];
  unsigned int newOrder = 1;
  unsigned long long int key;
  scanf("%lu %lu %u", &m, &n, &t);

  //collecting table of arrows
  for (i = 1; i <= t; i++){
    scanf("%lu %lu %lu %lu", &a1, &b1, &a2, &b2);
    key = a1 * MAX_CORD + b1;
    if(reorder.find(key) == reorder.end()){
      arrows[i][0] = newOrder;
      reorder[key] = newOrder++;
    }
    else arrows[i][0] = reorder[key];

    key = a2 * MAX_CORD + b2;
    if(reorder.find(key) == reorder.end()){
      arrows[i][1] = newOrder;
      reorder[key] = newOrder++;
    }
    else arrows[i][1] = reorder[key];
  }

  for (i = 1; i <= t; i++){
    printf("%u %u\n", arrows[i][0], arrows[i][1]);
  }

  //creating lists of succesors
  unsigned int counter[MAX_EDG] = {0};
  unsigned int first[MAX_EDG] = {0};
  unsigned int succesors[MAX_VRT] = {0};
  unsigned int maxOrder = newOrder - 1;
  for (i = 1; i <= t; i++) {
    counter[arrows[i][0]]++;
  }

  for (i = 1; i <= maxOrder; i++){
    printf("%u. counter: %u\n", i, counter[i]);
  }

  for (i = 1; i <= t; i++){
    first[i] = first[i-1] + counter[i];
  }

  for (i = 1; i <= maxOrder; i++){
    printf("%u. first: %u\n", i, first[i]);
  }

  for (i = 1; i <= t; i++){
    succesors[first[arrows[i][0]]] = arrows[i][1];
    first[arrows[i][0]]--;
  }

  printf("succesors: ");
  for (i = 1; i <= t; i++){
    printf("%u ", succesors[i]);
  }
  printf("\n");

  for (i = 1; i <= maxOrder; i++){
    printf("%u. first: %u\n", i, first[i]);
  }


  std::queue<unsigned int> container;
  unsigned int indeg[MAX_VRT];
  unsigned int sortedTPL[MAX_VRT];
  //unsigned int idxTPL[1000002];
  unsigned int it = 1;
  unsigned int tail, head;

  for (i = 1; i <= t; i++) indeg[succesors[i]]++;

  for (i = 1; i <= maxOrder; i++){
    printf("%u. indeg: %u\n", i, indeg[i]);
  }

  for (i = 1; i <= maxOrder; i++)
    if (indeg[i] == 0)
      container.push(i);

  while(!container.empty()){
    tail = container.front();
    printf("\n%u: ", tail);
    //idxTPL[tail] = it;
    sortedTPL[it++] = tail;
    container.pop();
    for (i = 1; i <= counter[tail]; i++){
      head = succesors[first[tail] + i];
      printf("%u ", head);
      indeg[head]--;
      if(indeg[head] == 0)
        container.push(head);
    }
  }
  printf("\n");

  for (i = 1; i <= maxOrder; i++){
    printf("%u ", sortedTPL[i]);
  }
  printf("\n");

  unsigned int source = reorder[0];
  unsigned int destiny = reorder[m * MAX_CORD + n];
  printf("source: %u, destiny: %u\n", source, destiny);

  unsigned int paths[MAX_VRT] = {0};
    printf("%llu\n", paths[2]);
  unsigned int j;
  paths[source] = 1;
  for (i = 1; i <= maxOrder; i++){
    tail = sortedTPL[i];
    for (j = 1; j <= counter[tail]; j++){
      head = succesors[first[tail] + j];
      paths[head] += paths[tail] % MAX_RES;
    }
  }

  printf("result: %u\n", paths[destiny]);

  return 0;
}
