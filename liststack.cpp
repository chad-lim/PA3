#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "liststack.h"

using namespace std;


int main(){

	// Creates a new Stack object that will hold the text file
	Stack stack;
	cout << "Please enter the name of the input file:" << endl;
	string fileName;
	cin >> fileName;

	// Sets the created stack object equal to the stack returned by readFile()
	stack = readFile(fileName);



	Stack keywords;
	Stack identifiers;
	Stack constants;
	Stack operators;
	Stack delimiters;
	Stack syntaxErrors;

	int depthOfNestedLoops;
	int countBegin = 0;
	int countFor = 0;
	int countEnd = 0;
	bool isSyntaxError;
	// Errors loop through the stack and find anything that isn't right and automatically say it's wrong


	//Find a way to check if something is already in the stack
	while (stack.isEmpty() != true){

		string temp = stack.pop();
		isSyntaxError = true;

		// DELIMITERS WORK DON'T TOUCH
		for (int i = 0; i < temp.length(); i++){
			char c;
			c = temp.at(i);
			string s(1,c);
			if (s == ";" || s == ","){

				isSyntaxError = false;

				if (!delimiters.contains(s)){
					delimiters.push(s);
				}
			}
		}

		// Operators - Put into the if-else statements to correctly do syntax Errors
		for (int i = 0; i < temp.length(); i++){
			char c;
			c = temp.at(i);
			string s(1,c);

			//if (!operators.contains(s) && !operators.contains(temp)){

				if (temp == "++)" || temp == "++;" || temp == "--)" || temp == "--;" || s == "-" || s == "*" || s == "/" ||  s == "%" || s == "+" || s == "="){

					if (temp == "++)" || temp == "++;"){

						isSyntaxError = false;
						if (!operators.contains("++")){
							operators.push("++");
						}
					}

					else if (temp == "--)" || temp == "--;"){

						isSyntaxError = false;
						if(!operators.contains("--")){
							operators.push("--");
						}
					}

					else{

						isSyntaxError = false;

						if (!operators.contains(s)){
							operators.push(s);
						}

					}
				}
			}
		//}

		// TODO: FIX THIS
		// check to see if the amountz] of letters equals the length of the popped object
		for (int i = 0; i < temp.length(); i++){
			int count = 0;
			char c;
			c = temp.at(i);
			string s(1,c);
			int index;
			if (s == "="){
				index = temp.find("=");
				temp = temp.substr(0, index);
				isSyntaxError = false;
				if (!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}
			else if (s == ";"){
				index = temp.find(";");
				temp = temp.substr(0, index);
				isSyntaxError = false;
				if (!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}

			else if (s == "("){
				temp = temp.at(1);
				isSyntaxError = false;
				if(!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}

			else if (temp.length() == 1 && c >= 'a' && c <= 'z'){
				isSyntaxError = false;
				if (!identifiers.contains(temp)){
					identifiers.push(temp);
				}
			}

		}


		// KEYWORDS WORK DON'T TOUCH
		if (temp == "FOR" || temp == "BEGIN" || temp == "END"){
			if (!keywords.contains(temp)){
				keywords.push(temp);
			}
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

		// Constants
		else if(temp.at(0) != '(' && temp.at(temp.length()-1) == ',') {

			if (!constants.contains(temp.substr(0, temp.length()-1))){
				constants.push(temp.substr(0, temp.length()-1));
			}

		}

		else if (isSyntaxError){
			syntaxErrors.push(temp);
		}

		// Identifiers will be by themselves they'll have an equal sign direclty in the middle or they will have an open paren to the left and a comma to the right


	}


	depthOfNestedLoops = max(max(countFor, countBegin), countEnd) - 1;


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




Stack readFile(string fileName){

	Stack stack;
	ifstream inFile;
	inFile.open(fileName.c_str());

	if(inFile.fail()){
		cerr << "Error opening file. Exiting Program" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		string word;
		while (true){
			inFile >> word;
			if(inFile.eof())
			break;
			stack.push(word);

		}
		inFile.close();
	}
	return stack;
}

