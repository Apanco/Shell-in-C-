#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void start();
string getCommand();
string cleanCommand( string& str );
string getCode(string& str);

//utils

int stringToInt(string str);

int main() {
	// Flush after every std::cout / std:cerr
	cout << unitbuf; // Asegurar que cout no esté almacenado en búfer
	cerr << unitbuf; // Asegurar que cerr no esté almacenado en búfer
	// Uncomment this block to pass the first stage
	while(true){
		start();
	}
}

void start(){
	string input, command, code;
	input = getCommand();
	
	command = cleanCommand(input);
	code = getCode(input);
	//Comandos identificados
	
	if(command == "exit"){
		int codeInt = stringToInt(code);
		exit(codeInt);
	}
	if(command == "echo"){
		cout<<code<<endl;
	}
	//Comando no identificado
	else{
		cout << input << ": command not found\n";
	}
}

string getCommand(){
	string input;
	cout << "$ ";
	getline(cin, input);
	return input;
}

string cleanCommand( string& str ){
	istringstream iss(str);
    string firstWord;
    iss >> firstWord;
    return firstWord;
}

string getCode(string& str){
	istringstream iss(str);
	string firstWord, secondWord;
	iss >> firstWord >> secondWord;
	return secondWord;
}



// Utils
int stringToInt(string numString){
	istringstream iss(numString);
	int numInt;
	iss >> numInt;
    return numInt;
}
