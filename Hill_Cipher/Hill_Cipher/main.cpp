// Name: Wei Wu  CSC/MTH 228  Lab2   Date:5/4/16

/*Notes:
1) Any size of message will work.
2) Allows spaces in message and does not need to be muliple of 3.
3) Any spaces in message will be filled in by the letter z or number 25.
4) The determinant must not be zero inorder to find a inverse key.
5) Number to character conversion: a=0, b=1 ..... z=25
*/
#include<iostream>
#include<string>
#include<cmath>
#include"Hill_Cipher.h"
using namespace std;

void main(){
	

	int key[9] = {17,21,2,    //R1
		          17,18,2,    //R2
				  5, 21, 19}; //R3

	string message = "heloworld"; //Message to use

	int mod_algorithm_num = 26; //The mod alorithm value.

	Hill_Cipher testObj(key, message, mod_algorithm_num);

	cout << "\nOriginal Message: " << testObj.getMessage() << "\n\n";


	testObj.printKey();// outputs the key in row order format

	testObj.encryption(); //encrypts message using key;


	cout << "\nMessage after encryption: " << testObj.getMessage();
	cout << "\nMessage after encryption Number form: ";
	for (int i = 0; i < message.length();i++){
		cout << testObj.getMessageNum()[i] << " ";
	}
	cout << "\n\n"; //text formating for easier reading.

	testObj.decryption(); //decrypts message.

	cout << "\nInverse of key: \n";

	testObj.printKey(); //outputs the inverse of key.

	cout << "\nMessage after decryption: " << testObj.getMessage();
	cout << "\nMessage after decryption Number form: ";
	for (int i = 0; i < message.length(); i++){
		cout << testObj.getMessageNum()[i] << " ";
	}
	cout << "\n\n"; //text formating for easier reading.
	
	system("pause");//stops window from closing to fast.
}

