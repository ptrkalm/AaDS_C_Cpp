#include "stdio.h"

int main(){
  int N;
  long long int minPrice[1000002] = {0};
  long int dist[1000002] = {0};
  long int front = 0;
  long int end = 1;
  long int currDist;
  long int currPrice;
  long long int currMinPrice;
  long long int result;
  long int l, b;
  scanf("%d %ld %ld", &N, &l, &b);
  if (N == 0) { if (b < l)
    	{ printf("NIE\n"); return 0; }
    	else{ printf("0"); return 0; }
  }
  for (int i = 1; i <= N; i++){
    	scanf("%ld %ld", &currDist, &currPrice);
    	while(currDist - dist[front] > b && front < end) front++;
    	if (front == end) {printf("NIE\n"); return 0;}
    	//printf("%d\n", i);
    	currMinPrice = minPrice[front] + currPrice;
    	while(currMinPrice < minPrice[end-1] && end >= front){
      	end--;
    	}
    	minPrice[end] = currMinPrice;
    	dist[end] = currDist;
    	end++;
  }
  currDist = l;
  currPrice = 0;
  while(currDist - dist[front] > b && front < end) front++;
  if (front == end) {printf("NIE\n"); return 0;}
  currMinPrice = minPrice[front] + currPrice;
  while(currMinPrice < minPrice[end-1] && end > front){
     	end--;
  }
  minPrice[end] = currMinPrice;
  result = minPrice[front];
  printf("%lld\n", result);

  return 0;
}
