#include <iostream>
using namespace std;

void start();

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
	cout << "$ ";
	  
	string input;
	getline(cin, input);
	cout << input << ": command not found\n";
}
