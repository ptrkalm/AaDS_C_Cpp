#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Node::Node(long long int x, Node* p){
    value = x;
    priority = rand();
    parent = p;
    left   = nullptr;
    right  = nullptr;
}
Node* Node::insertNode(long long int x){
    if(x == value) return nullptr;

    if(x < value){
      if(left == nullptr){
        left = new Node(x, this);
        return left;
      }
      else return left->insertNode(x);
    }
    else{
      if(right == nullptr){
        right = new Node(x, this);
        return right;
      }
      else return right->insertNode(x);
    }

    return nullptr;
}
Node* Node::upperNode(long long int x, Node* prev){
    if (x == value) return this;
    if (x < value){
      if (left == nullptr) return this;
      else return left->upperNode(x, this);
    }
    if (x > value){
      if (right == nullptr) return prev;
      else return right->upperNode(x, prev);
    }
    return nullptr;
}
Node* Node::lowerNode(long long int x, Node* prev){
  if (x == value) return this;
  if (x < value){
    if (left == nullptr) return prev;
    else return left->lowerNode(x, prev);
  }
  if (x > value){
    if (right == nullptr) return this;
    else return right->lowerNode(x, this);
  }
  return nullptr;
}
Node* Node::findNode(long long int x){
  if (x == value) return this;
  if (x < value && left != nullptr)
    return left->findNode(x);
  if (x > value && right != nullptr)
    return right->findNode(x);
  return nullptr;
}
Node* Node::findReplacement(){
  if (this->left == nullptr) return this;
  else return this->left->findReplacement();
}
void Node::print(){
  if(left != nullptr) left->print();
  printf("(%lld, %d) ", value, priority);
  if(right != nullptr) right->print();
}
