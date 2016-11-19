
//
//  pa3.cpp
//
//  Created by Chad Lim on 11/15/16.
//  Copyright © 2016 Chad Lim. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include "stdio.h"
#include "pa3.h"

using namespace std;

int main(){

	// Creates a new Stack object that will hold the text file
	Stack stack;
	cout << "Please enter the name of the input file:" << endl;
	string fileName;
	cin >> fileName;

	// Sets the created stack object equal to the stack returned by readFile()
	stack = readFile(fileName);

	// Stacks that will hold the different tokens that are found
	Stack keywords;
	Stack identifiers;
	Stack constants;
	Stack operators;
	Stack delimiters;
	Stack syntaxErrors;

	// Counts the number of nested loops
	int depthOfNestedLoops;

	// Counts the number of BEGIN, END, and FOR instances in the code
	// to determine the detph of nested loops
	int countBegin = 0;
	int countFor = 0;
	int countEnd = 0;

	// Determines if something is a syntax error to be output
	bool isSyntaxError;


	// Goes through the entire stack created from the file
	while (stack.isEmpty() != true){

		// Creates a string variable that holds the string that is popped off
		// of the top of the stack
		string temp = stack.pop();
		isSyntaxError = true;

		// Checks for delimiters by going through each individual index of the
		// popped string, searching for ";" or ","
		for (unsigned int i = 0; i < temp.length(); i++){

			char c;
			c = temp.at(i);
			string s(1,c);
			if (s == ";" || s == ","){

				// This line, and all others like it for the remainder of the program
				// Indicates that there are no syntax errors so the element doesn't
				// get pushed into the error stack
				isSyntaxError = false;

				// This line (and all others like it for the remainder of the program)
				// Checks to see if the element to be pushed into a stack already
				// exists in the current stack
				if (!delimiters.contains(s)){
					delimiters.push(s);
				}
			}
		}

		// Checks for the operators by looping through each individual index
		// While also checking the entire popped element for specific instances
		for (unsigned int i = 0; i < temp.length(); i++){

			char c;
			c = temp.at(i);
			string s(1,c);

			// Checks for all possible operators
			if (temp == "++)" || temp == "++;" || temp == "--)" || temp == "--;" || s == "-" || s == "*" || s == "/" ||  s == "%" || s == "+" || s == "="){

				// Handles the specific case of "++)" at the end of a for loop
				if (temp == "++)" || temp == "++;"){
					isSyntaxError = false;
					if (!operators.contains("++")){
						operators.push("++");
					}
				}

				// Handles the specific case of "--)" at the end of a for loop
				else if (temp == "--)" || temp == "--;"){
					isSyntaxError = false;
					if(!operators.contains("--")){
						operators.push("--");
					}
				}

				// Handles all other operator cases
				else{
					isSyntaxError = false;
					if (!operators.contains(s)){
						operators.push(s);
					}
				}
			}
		}


		// Checks for identifiers by going through each index of the popped element
		for (unsigned int i = 0; i < temp.length(); i++){

			char c;
			c = temp.at(i);
			string s(1,c);
			int index;

			// Checks to see if there's an equal sign for the cases such as
			// "sum=sum" by only grabbing the characters up to the operator
			if (s == "="){
				index = temp.find("=");
				temp = temp.substr(0, index);
				isSyntaxError = false;
				if (!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}

			// Follows the same logic as above, but for ";"
			else if (s == ";"){
				index = temp.find(";");
				temp = temp.substr(0, index);
				isSyntaxError = false;
				if (!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}

			// Follows the same logic as above, but for "("
			else if (s == "("){
				temp = temp.at(1);
				isSyntaxError = false;
				if(!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}

			// Handles cases where the identifier is alone and not surrounded
			// by any sort of operator or delimiter
			else if (temp.length() == 1 && c >= 'a' && c <= 'z'){
				isSyntaxError = false;
				if (!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}
		}

		// Handles the keywords "FOR" "BEGIN" and "END"
		// By checking if the popped element is any of the above
		// and pushes it if was found
		if (temp == "FOR" || temp == "BEGIN" || temp == "END"){
			if (!keywords.contains(temp)){
				keywords.push(temp);
			}

			// Increments the number of "FOR" "BEGIN" or "END" keywords found
			// for the purpose of counting the depth of nested loops
			if (temp == "FOR"){
				countFor++;
			}
			else if (temp == "BEGIN"){
				countBegin++;
			}
			else if(temp == "END"){
				countEnd++;
			}
		}

		// Checks for constants (numbers)
		else if(temp.at(0) != '(' && temp.at(temp.length()-1) == ',') {

			// Uses substring to ensure only the constant is pushed into the stack
			if (!constants.contains(temp.substr(0, temp.length()-1))){
				constants.push(temp.substr(0, temp.length()-1));
			}
		}

		// Pushes the popped element in to the syntax error stack if it was never
		// determined that the element is not a syntax error
		else if (isSyntaxError){
			syntaxErrors.push(temp);
		}
	}

	// Decides the depth of nested loops based on the maximum between the
	// "FOR", "BEGIN", and "END" keywords
	depthOfNestedLoops = max(max(countFor, countBegin), countEnd) - 1;


	// Output the information
	cout << "\nThe depth of nested loop(s) is: " << depthOfNestedLoops << "\n" << endl;

	cout << "Keywords:";
	keywords.printStack();
	cout << endl;
	cout << "Identiier:";
	identifiers.printStack();
	cout << endl;
	cout << "Constant:";
	constants.printStack();
	cout << endl;
	cout << "Operators:";
	operators.printStack();
	cout << endl;
	cout << "Delimiters:";
	delimiters.printStack();
	cout << endl;
	cout << "\nSyntax Error(s):";
	syntaxErrors.printStack();
	cout << endl;


	return 0;
}

// Reads in a file based on file name and returns it as a stack
Stack readFile(string fileName){

	Stack stack;
	ifstream inFile;
	inFile.open(fileName.c_str());

	// Provides a message in case a file could not be opened or failed to open
	// and ends the program
	if(inFile.fail()){
		cerr << "Error opening file. Exiting Program" << endl;
		exit(EXIT_FAILURE);
	}
	// Pushes each part of the file into the main stack as a string until the
	// file reader has reached the end of the file
	else{
		string word;
		while (true){
			inFile >> word;
			if(inFile.eof())
			break;
			stack.push(word);

		}
		// Closes the file after completion
		inFile.close();
	}
	return stack;
}
