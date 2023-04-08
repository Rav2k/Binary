#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "node.h"
#include <random>

using namespace std;

void insert(node *&cur, int number);
void fileGeneration();
void print(node *cur2, int layers);
void search(node *cur, int nums);
node *del(node *cur, int numDel);
node *root = NULL;

int main(){
  char userInput[20];
  bool loop = false;
  
  do{

    cout<<"type 'gen' to generate 10 numbers from a file"<<endl;
    cin>>userInput;
    cin.get();
    if(strcmp(userInput, "gen") == 0){
      cout<<"Generating numbers..."<<endl;
      fileGeneration();
      cout<<"done!"<<endl;
      loop = true;
    }else{
      cout<<"invalid choice"<<endl;
    }

  }while(!loop);

  cout<<"Printing..."<<endl;
  print(root, 0);

  cout<<"to add type 'add'"<<endl;
  cout<<"to search type 'search'"<<endl;
  cout<<"to remove type 'del'"<<endl;
  cout<<"to print type 'print'"<<endl;
  cout<<"to quit type 'quit'"<<endl;

  char user[20];
  int userNum = 0;

  do{
    cout<<"to add type 'add'"<<endl;
  cout<<"to search type 'search'"<<endl;
  cout<<"to remove type 'del'"<<endl;
  cout<<"to print type 'print'"<<endl;
  cout<<"to quit type 'quit'"<<endl;
    cout<<endl;
    cout<<"What do you want to do?: "<<endl;
    cin.get(user, 20);
    cin.get();
    if(strcmp(user, "add") == 0){
      cout<<"Enter the number: "<<endl;
      cin>>userNum;
      cin.get();
      insert(root, userNum);
      cout<<"Number has been successfully added!"<<endl;
    }

    else if(strcmp(user, "search")==0){
      cout<<"Enter the number you want to search for: "<<endl;
      cin>>userNum;
      cin.get();
      search(root, userNum);
      cout<<endl;
           cout<<"Search complete..."<<endl;
    }
    else if(strcmp(user, "del")==0){
      cout<<"Enter the number doomed to be deleted: "<<endl;
      cin>>userNum;
      cin.get();
      root = del(root, userNum);
      cout<<endl;
      cout<<"Number deleted"<<endl;
    }
    else if(strcmp(user, "print") == 0){
      cout<<"printing..."<<endl;
      print(root, 0);
    }
    else{
      cout<<"type something valid"<<endl;
    }
  }while(strcmp(user, "quit")!=0);

  
  return 0;
}
  void insert(node *&cur, int number){//adding in a number to the tree!
    if(cur == NULL){//if nothing is there then create the node with the number 
      cur = new node(number, NULL, NULL);
      return;
    }
    if(number>=cur->data){//if the number is greater than the current node which is the "root" this case then...
      if(cur->right == NULL){//... check to make sure the right is empty then put that number there
	cur->right = new node(number, NULL, NULL);
	return;
      }
      else{
	insert(cur->right, number);//if there is something there already go to the right one which is the higher and run this function again to see where it can fit
      }
    }
    else{//same idea as the right one but with when the data that will be inserted is less than that of the current's data
      if(cur->left == NULL){
	cur->left = new node(number, NULL, NULL);
	return;
      }
      else{
	insert(cur->left, number);
      }
    }
  }

//Asked noam for how he did his and used the approach he used.
void fileGeneration(){//taking the numbers from the text file and making the base tree
  ifstream numbers("numbers2.txt");
  srand(time(NULL));
  int num = 0;
  vector<int> nums;
  while (!numbers.eof()) {
    numbers >> num;
    nums.push_back(num);
  }
  int randomIndex = 0;
  int counter = 0;
  while (counter != 10) {
    randomIndex = (rand() % nums.size()) + 1;
    num = nums.at(randomIndex);
    cout << num << " ";
    insert(root, num);
    counter++;
  }
  cout<<"Finished"<<endl;
}

void print(node *cur2, int layers){
  if(cur2 == NULL){
    return;
  }
  print(cur2->right, layers+1);//right side printing 

  for(int i = 0; i<layers;i++){
    cout<<"     ";
  }

  cout<<cur2->data<<endl;
  print(cur2->left, layers+1);//print the left side
}

void search(node *cur, int nums){
  int userNum = 0;

  while(cur != NULL){
    userNum = cur->data;
    if(userNum == nums){
      cout<<"Your number has been found in the tree"<<endl;
      return;
    }
    if(nums>userNum){
      cur = cur->right;
    }else{
      cur = cur->left;
    }
  }

  cout<<"The entered number couldn't be found"<<endl;
}
//Noam gave me this website to help with my delete function: https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
node* del(node *cur, int numDel){
  if(cur == NULL){
    return cur;
  }
  if(numDel<cur->data){
    cur->left = del(cur->left, numDel);
    return cur;
  }

  if(numDel>cur->data){
    cur->right = del(cur->right, numDel);
    return cur;
  }

  else{
    if(cur->right == NULL && cur->left == NULL){
      return NULL;
    }
    else if(cur->left == NULL){
      node *temp = cur->right;
      delete cur;
      return temp;
    }
    else if(cur->right == NULL){
      node *tempNode = cur->left;
      delete cur;
      return tempNode;
    }
    else {
      node *dominantParent = cur;
      node *succesor = cur->left;
      while (succesor->right != NULL) {
	dominantParent = succesor;
	succesor = succesor->right;
      }
      if (dominantParent != cur) {
	dominantParent->right = succesor->left;
      }
      //current's left is the replacement
      else {
	dominantParent->left = succesor->left;
      }
      cur->data = succesor->data;
      delete succesor;
      return cur;
    }
  }
  return cur;
}
