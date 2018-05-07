#include "Tree.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

using namespace std;

Tree::Tree(){ root = nullptr; }
Node* Tree::leftRotate(Node* node){
  if(node->parent != nullptr){
    int left;
    if (node->parent->left == node)
      left = 1;
    else
      left = 0;
    long long int oldNodeValue = node->value;
    int oldNodePriority = node->priority;
    Node* replacement = node->left;
    Node* nodeRightSubtree = node->right;
    Node* nodeParent = node->parent;
    delete node;
    if(left)
      node->parent->left = replacement;
    else
      node->parent->right = replacement;
    node = replacement;
    replacement = nullptr;
    node->parent = nodeParent;
    nodeParent = nullptr;

    Node* oldNode = new Node(oldNodeValue, node);
    oldNode->priority = oldNodePriority;
    oldNode->left = node->right;
    if (node->right != nullptr)
      oldNode->left->parent = oldNode;
    oldNode->right = nodeRightSubtree;
    if (nodeRightSubtree != nullptr)
      oldNode->right->parent = oldNode;
    nodeRightSubtree = nullptr;
    node->right = oldNode;
    return node;
  }

  long long int oldRootValue = root->value;
  int oldRootPriority = root->priority;
  Node* replacement = root->left;
  Node* rootRightSubtree = root->right;
  delete root;
  root = replacement;
  replacement = nullptr;
  root->parent = nullptr;
  Node* oldRoot = new Node(oldRootValue, root);
  oldRoot->priority = oldRootPriority;
  oldRoot->left = root->right;
  if (oldRoot->left != nullptr)
    oldRoot->left->parent = oldRoot;
  root->right = oldRoot;
  oldRoot->right = rootRightSubtree;
  if (oldRoot->right != nullptr)
    oldRoot->right->parent = oldRoot;
  return root;
}
Node* Tree::rightRotate(Node* node){
  if(node->parent != nullptr){
    int left;
    if (node->parent->left == node)
      left = 1;
    else
      left = 0;
    long long int oldNodeValue = node->value;
    int oldNodePriority = node->priority;
    Node* replacement = node->right;
    Node* nodeLeftSubtree = node->left;
    Node* nodeParent = node->parent;
    delete node;
    if(left)
      node->parent->left = replacement;
    else
      node->parent->right = replacement;
    node = replacement;
    replacement = nullptr;
    node->parent = nodeParent;
    nodeParent = nullptr;

    Node* oldNode = new Node(oldNodeValue, node);
    oldNode->priority = oldNodePriority;
    if (node->left != nullptr){
      oldNode->right = node->left;
      oldNode->right->parent = oldNode;
    }
    if (nodeLeftSubtree != nullptr){
      oldNode->left = nodeLeftSubtree;
      oldNode->left->parent = oldNode;
    }
    nodeLeftSubtree = nullptr;
    node->left = oldNode;
    return node;
  }

  long long int oldRootValue = root->value;
  int oldRootPriority = root->priority;
  Node* replacement = root->right;
  Node* rootLeftSubtree = root->left;
  delete root;
  root = replacement;
  replacement = nullptr;
  root->parent = nullptr;
  Node* oldRoot = new Node(oldRootValue, root);
  oldRoot->priority = oldRootPriority;
  oldRoot->right = root->left;
  if (oldRoot->right != nullptr)
    oldRoot->right->parent = oldRoot;
  root->left = oldRoot;
  oldRoot->left = rootLeftSubtree;
  if (oldRoot->left != nullptr)
    oldRoot->left->parent = oldRoot;
  return root;
}
void Tree::treapifyUp(Node* node){
  if (node->parent == nullptr) return;
  if (node->parent->priority < node->priority){
    if(node->parent->left == node){
      treapifyUp(leftRotate(node->parent));
    }
    else
      treapifyUp(rightRotate(node->parent));
  }
}
void Tree::treapifyDown(Node* node){
  if (node->left == nullptr && node->right == nullptr)
    return;
  if (node->left == nullptr){
    if (node->right->priority > node->priority)
      treapifyDown(rightRotate(node));
    return;
  }
  if (node->right == nullptr){
    if(node->left->priority > node->priority)
      treapifyDown(leftRotate(node));
    return;
  }

  if(node->left->priority > node->priority){
    if(node->right->priority > node->left->priority){
      treapifyDown(rightRotate(node));
      return;
    }
    else{
      treapifyDown(leftRotate(node));
      return;
    }
  }
  else if (node->right->priority > node->priority){
    treapifyDown(rightRotate(node));
    return;
  }
}
void Tree::insertNode(long long int x){
  if (root == nullptr){
    root = new Node(x, nullptr);
    return;
  }
  else{
    Node* inserted = root->insertNode(x);
    if(inserted != nullptr)
      treapifyUp(inserted);
  }
}
int Tree::deleteNode(long long int x){
  if (root == nullptr) return FALSE;
  Node* toErase = root->findNode(x);
  if (toErase == nullptr) return FALSE;

  if (toErase->left == nullptr && toErase->right == nullptr){
    if (toErase->parent == nullptr){
      delete root;
      root = nullptr;
      return TRUE;
    }
    if (toErase->parent->left == toErase){
      delete toErase->parent->left;
      toErase->parent->left = nullptr;
    }
    else{
      delete toErase->parent->right;
      toErase->parent->right = nullptr;
    }
    return TRUE;
  }
  else if (toErase->right == nullptr || toErase->left == nullptr){
    Node* replacement;
    if(toErase->right == nullptr)
      replacement = toErase->left;
    else
      replacement = toErase->right;

    if (toErase->parent == nullptr){
      delete root;
      root = replacement;
      root->parent = nullptr;
      replacement = nullptr;
    }
    else if (toErase->parent->left == toErase){
      replacement->parent = toErase->parent;
      toErase->parent->left = replacement;
      delete toErase;
      toErase = replacement;
      replacement = nullptr;
    }
    else{
      replacement->parent = toErase->parent;
      toErase->parent->right = replacement;
      delete toErase;
      toErase = replacement;
      replacement = nullptr;
    }
    return TRUE;
  }
  else{
    Node* replacement = toErase->right->findReplacement();
    toErase->value = replacement->value;
    toErase->priority = replacement->priority;
    if (replacement->right != nullptr)
      replacement->right->parent = replacement->parent;
    if (replacement->parent != toErase){
      replacement->parent->left = replacement->right;
      delete replacement;
      replacement = nullptr;
    }
    else{
      toErase->right = replacement->right;
      delete replacement;
      replacement = nullptr;
    }
  }
  treapifyDown(toErase);
  return TRUE;
}
Node* Tree::upperNode(long long int x){
  if(root == nullptr) return nullptr;
  return root->upperNode(x, nullptr);
}
Node* Tree::lowerNode(long long int x){
  if(root == nullptr) return nullptr;
  return root->lowerNode(x, nullptr);
}
Node* Tree::findNode(long long int x){
  if(root == nullptr) return nullptr;
  return root->findNode(x);
}
void Tree::print(){
  if(root == nullptr){
    printf("empty\n");
    return;
  }
  else{
    root->print();
    printf("\n");
    return;
  }
}
