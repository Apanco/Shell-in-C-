#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <cstdlib> //Funciones estandar de C++ como getenv()
#include <cstring> //Proporciona funciones de manipulacion de cadenas como strdup()
#include <cerrno>	//Proporciona errno

using namespace std;

void start();
string getCommand();
string cleanCommand( string& str );
string getCode(string& str);
string getEcho(string echo, string command);
int busquedaLineal(vector <string> array, string toFind);
//utils
string getEnvVairiable(string envVarName);
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
	bool exist = false;
	string builtinCommandsPrimitive[] = {"exit", "echo", "type"};
	vector <string> builtinCommands(builtinCommandsPrimitive, builtinCommandsPrimitive + sizeof(builtinCommandsPrimitive) / sizeof(std::string));
	string input, command, code;
	input = getCommand();
	command = cleanCommand(input);
	code = getCode(input);
	//builtin commands
	if(command == "exit"){
		exist = true;
		int codeInt = stringToInt(code);
		exit(codeInt);
	}
	if(command == "echo"){
		exist = true;
		string str = getEcho(input, command);
		cout<<str<<endl;
	}
	if(command == "type"){
		exist = true;
		int isBuiltinCommand = busquedaLineal(builtinCommands, code);
		string direction = getEnvVairiable(code);
		if(isBuiltinCommand != -1){
			cout<<code<<" is a shell builtin"<<endl;
		}
		if(isBuiltinCommand == -1 && direction != "xd"){
			cout<<code<<" is "<<direction<<endl;
		}
		else{
			cout << code << ": not found"<<endl;
		}
	}
	
	//Comando no identificado
	else if(!exist){
		cout << command << ": command not found"<<endl;
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
string getEnvVairiable(string envVarName){
	char* envValue = nullptr; //Puntero que contendra el valor de la variable de entorno, definida en null
	size_t len = 0; // Entero no negativo grande
	string result;
	
	envValue = getenv(envVarName.c_str()); //c_str string -> *char
	if(envValue == nullptr){
		return "xd";
	}
	
	char* token = strtok(envValue, ";");
	
	result = token;
	return result;
}
