#include <iostream>
#include <cstring>

using namespace std;

class node{
 public:
  node();
  node *next;
  node *left;//for the left pointer
  node *right;//for the right pointer
  int data;
  node(int num, node *left, node *right);
  ~node();
  node *getNext();
  int getNum();
};
