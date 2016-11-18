#ifndef PA3_H
#define PA3_H
#include <iostream>
#include <string>
#include "stdio.h"

using namespace std;


// Linked Stack class called "Stack"
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

Stack readFile(string fileName);


// Constructor for the Stack object
Stack::Stack(){
    head = NULL;
    curr = NULL;
    temp = NULL;
	stackSize = 0;
}

int Stack::size(){
	return stackSize;
}
// This function takes in a string, and adds a node to the linked Stack that
// contains this string as its stored data
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

bool Stack::isEmpty(){
	if (stackSize == 0){
		return true;
	}
	else{
		return false;
	}
}

// Prints the linked Stack using nested for loops.
void Stack::printStack(){

	if (stackSize != 0){
    	while (stackSize != 0){
			cout << " " << pop();
    	}
	}
}

string Stack::top(){
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
		return result;

	}
	else{
		result = curr->data;
		return result;
	}

	return result;
}


#endif
