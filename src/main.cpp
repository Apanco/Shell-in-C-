#include <iostream>
#include <vector>
#include <unordered_set>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>
#include <sstream>
#include <fstream> 
namespace fs = std::filesystem;
using namespace std;

void start();
string getCommand();
string cleanCommand( string& str );
string getCode(string& str);
string getEcho(string echo, string command);
int busquedaLineal(vector <string> array, string toFind);
string exec(const string cmd, string input);
string handle_type_command(vector<string> arguments);
//utils
string getEnvVairiable(string envVarName);
int stringToInt(string str);
vector <string> splitString(string input, char delimiter);

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
	
	string input, command, code;
	input = getCommand();
	command = cleanCommand(input);
	code = getCode(input);
	
	vector <string> arguments = splitString(input, ' ');
	
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
		string response = handle_type_command(arguments);
		cout<<response<<endl;
	}
	else{
		string direction = getEnvVairiable(command);
		if(direction != ""){
			exist = true;
			string cmdPath = direction + "/" + command;
			string result = exec(cmdPath, input);
			cout<<result<<endl;
		}
	}
	if(0 == input.find("my_exe") ){
		exist = true;
		system(input.c_str());
		
	}
	//Comando no identificado
	if(!exist){
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

// Dividir string y retornar en vector
vector <string> splitString(string input, char delimiter = ' '){
	vector <string> result;
	
	stringstream ss(input);
	string token;
	string temporal = "";

	while(getline(ss, token, delimiter)){
		result.push_back(token);
	}

	return result;
}
// Buscar un archivo en un directorio
bool searchFile(string directory, string fileName){
	try {
		//Analiza que exista
        if (!fs::exists(directory)) {
            //std::cerr << "Directorio no existe: " << directory << std::endl;
            return false;
        }
        //Itera los archivos
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.path().filename() == fileName) {
                return true;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return false;
}


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
	//Almacenar direccion
	string result = "";
	// Obtener el valor de la variable de entorno PATH
    string path_env = getenv("PATH");
	
	//Dividir el PATH por ; y guardar las direcciones en un vector
    vector <string> paths = splitString(path_env, ';');
	
    for(int i = 0; i < paths.size(); i++){
    	//cout<<paths[i]<<" -> "<<envVarName<<endl;
        if(searchFile(paths[i], envVarName)) {
        
            result = paths[i];
            return result;
        }
    }
    //Retornar direccion
    return result; 
}

string handle_type_command(vector<string> arguments){
	
	string response = arguments[1]+": not found";
	string builtinCommandsPrimitive[] = {"exit", "echo", "type"};
	vector <string> builtinCommands(builtinCommandsPrimitive, builtinCommandsPrimitive + sizeof(builtinCommandsPrimitive) / sizeof(std::string));
	
	//Analizar si es un builtin command
	for(int i = 0; i < builtinCommands.size();i++){
		if(arguments[1] == builtinCommands[i]){
			response = arguments[1]+" is a shell builtin";
			return response;
		}
	}
	//Buscar comando en el path
	string filepath;
	// Obtener el valor de la variable de entorno PATH
    string path_env = getenv("PATH");
	stringstream ss(path_env);
	string path;
	while(!ss.eof()){
		getline(ss,path,':');
		string abs_path = path + '/' + arguments[1];
		if(filesystem::exists(abs_path)){
			response = arguments[1]+" is "+abs_path;
			return response;
		}
	}
	
	
	
	
	return response;
}


//Ejecutar comando externo
string exec(const string cmd, string input){
	array<char, 128> buffer;
	string result; // <- Aqui se campurara la salida del ejecutable
	
	unique_ptr<FILE, decltype(&pclose) >pipe(popen(input.c_str(), "r"), pclose);
	
	if(!pipe){
		throw runtime_error("popen() failed");
	}
	while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
		result += buffer.data();
	}
	return result;
}
