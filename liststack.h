#ifndef PA3_H
#define PA3_H
#include <iostream>
#include <string>
#include "stdio.h"

using namespace std;


// Stack class, based on a linked list data structure
class Stack{
private:

	int stackSize;

	// Creates a node struct
    typedef struct node{
        string data;
        node *next;
        bool isFree;
    }* nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;

// Declares public functions that are a part of the Stack class
// which can be used on objects of the Stack type in the source file
public:
    Stack();
	void push(string addData);
	string pop();
	bool isEmpty();
	bool contains(string data);
	int size();
	void printStack();
	bool exists();
	string top();

	int bestIndex;
	int worstIndex;
	bool print;
};

// Declares the readFile() method that is used in the .cpp file
Stack readFile(string fileName);


// Constructor for the Stack object
Stack::Stack(){
    head = NULL;
    curr = NULL;
    temp = NULL;
	stackSize = 0;
}

// Unused stack size method for functionality and completeness
int Stack::size(){
	return stackSize;
}

// This function takes in a string, and adds it to the top of the stack
void Stack::push(string addData){
    nodePtr n = new node;
    n->next = NULL;
    n->data = addData;
    if (head != NULL){
        curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
    }
    else {
        head = n;
    }
	stackSize++;
}

// This function returns a string, which gets popped from the top of the stack
string Stack::pop(){
	curr = head;
	string result;
	bool tempVar = false;
	while (curr->next != NULL){
		temp = curr;
		curr = curr->next;
		if(curr->data == ""){
			tempVar = true;
			break;
		}
	}
	if (tempVar){
		result = temp->data;
		temp->data = "";

	}
	else{
		result = curr->data;
		curr->data = "";
	}
	stackSize--;
	return result;
}

// This function takes in a string and checks the entire stack to see if it already exists
bool Stack::contains(string token){
	if (stackSize != 0){
		curr = head;
		while (curr->next != NULL){
			if(curr->data == token){
				return true;
			}
			curr = curr->next;
		}
		if(curr->data == token){
			return true;
		}
		return false;
	}

	return false;
}

// Checks to see if the stack is empty
bool Stack::isEmpty(){
	if (stackSize == 0){
		return true;
	}
	else{
		return false;
	}
}

// Prints the contents of the stack
void Stack::printStack(){

	if (stackSize != 0){
    	while (stackSize != 0){
			cout << " " << pop();
    	}
	}
}

#endif
