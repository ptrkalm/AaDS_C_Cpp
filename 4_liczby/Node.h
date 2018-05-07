struct Node {
  long long int value;
  int priority;
  Node *parent;
  Node *left;
  Node *right;

  Node(long long int x, Node* p);
  Node* insertNode(long long int x);
  Node* upperNode(long long int x, Node* prev);
  Node* lowerNode(long long int x, Node* prev);
  Node* findNode(long long int x);
  Node* findReplacement();
  void print();
};
