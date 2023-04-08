#include <iostream>
#include <cstring>

using namespace std;

#include "node.h"

node::node(){
  right = NULL;
  left =NULL;
  int data = 0;
}

node::node(int num, node *left, node *right){
  data = num;
  this->data = data;
  this->left = left;
  this->right = right;
}

node::~node(){
  //nothing to do here
}

node* node::getNext(){
  return next;
}

int node::getNum(){
  return data;
}
