#include "Node.h"

struct Tree {
  Node* root;

  Tree();
  Node* leftRotate(Node* node);
  Node* rightRotate(Node* node);
  void treapifyUp(Node* node);
  void treapifyDown(Node* node);
  void insertNode(long long int x);
  int deleteNode(long long int x);
  Node* upperNode(long long int x);
  Node* lowerNode(long long int x);
  Node* findNode(long long int x);
  void print();
};
