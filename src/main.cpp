#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void start();
string getCommand();
string cleanCommand( string& str );
string getCode(string& str);
string getEcho(string echo, string command);
int busquedaLineal(vector <string> array, string toFind);
//utils

int stringToInt(string str);

int main() {
	// Flush after every std::cout / std:cerr
	cout << unitbuf; // Asegurar que cout no est� almacenado en b�fer
	cerr << unitbuf; // Asegurar que cerr no est� almacenado en b�fer
	// Uncomment this block to pass the first stage
	while(true){
		start();
	}
}

void start(){
	
	string builtinCommandsPrimitive[] = {"exit", "echo", "type"};
	vector <string> builtinCommands(builtinCommandsPrimitive, builtinCommandsPrimitive + sizeof(builtinCommandsPrimitive) / sizeof(std::string));
	string input, command, code;
	input = getCommand();
	command = cleanCommand(input);
	code = getCode(input);
	//builtin commands
	
	if(command == "exit"){
		int codeInt = stringToInt(code);
		exit(codeInt);
	}
	if(command == "echo"){
		string str = getEcho(input, command);
		cout<<str<<endl;
	}
	if(command == "type"){
		int isBuiltinCommand = busquedaLineal(builtinCommands, code);
		if(isBuiltinCommand != -1){
			cout<<code<<" is a shell builtin"<<endl;
		}
		else{
			cout << code << ": not found"<<endl;
		}
	}
	
	//Comando no identificado
	else{
		cout << input << ": command not found"<<endl;
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

string getEcho(string echo, string command){
	string result = echo;
	int pos = result.find(command);
	if(pos != string::npos){
		result.erase(pos,command.length());
		if(pos < result.length() && result[pos] == ' ' ){
			result.erase(pos, 1);
		}
	}
	return result;
}

// Utils
int stringToInt(string numString){
	istringstream iss(numString);
	int numInt;
	iss >> numInt;
    return numInt;
}
int busquedaLineal(vector <string> array, string toFind){
	int position = -1;
	int length = array.size();
	for(int i = 0; i < length; i++){
		if(array[i] == toFind){
			position = i;
		}
	}
	return position;
}
