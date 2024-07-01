#include <iostream>
using namespace std;

string getComand();

int main() {
	
	string notFound = "command not found";
	
	string input;
	// Flush after every std::cout / std:cerr
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
	
	// Uncomment this block to pass the first stage
	input = getComand();
	cout<<"\n"<<input<<": "<<notFound;
}
string getComand(){
	string input;
	cout<<"$ ";cin>>input;
	return input;
}


