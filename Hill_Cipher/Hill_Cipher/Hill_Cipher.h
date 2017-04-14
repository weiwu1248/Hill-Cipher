// Name: Wei Wu
/*Notes: 
1) Any size of message will work.
2) Allows spaces in message and does not need to be muliple of 3.
3) Any spaces in message will be filled in by the letter z or number 25.
4) The determinant must not be zero inorder to find a inverse key.
5) Number to character conversion: a=0, b=1 ..... z=25
*/

#ifndef Hill_CIPHER_H
#define HILL_CIPHER_H
#include<cmath>
#include<string>
#include<iostream>
using namespace std;
class Hill_Cipher
{
private:
	double key[3][3]; //The key.
	string message;   //The message.
	double* messageNum; //The message in number format.
	char* messageChar; //The message in character format.
	int mod_algorithm_num; //The mod algorithm to use.
	double determinant;
public:
	Hill_Cipher();
	Hill_Cipher(int* key, string message, int mod_algorithm_num);
	void inverseKey(); //Will inverse the key and replace key with the inverse key.
	void encryption(); //encrypts the message using the key.
	void decryption(); //Will use the inverse key to decrypt the message.
	double* convertCharToNum(char* messageChar, int messageSize); //Char to num convertion
	char* convertNumToChar(double* messageNum, int messageSize); //Num to char convertion
	int modInverse(int a, int m); //Inverse of mod. a*x = 1 (mod b)
	string getMessage(); //returns the message
	double* getMessageNum(); //returns the message in number form
	void printKey(); //outputs the key.
	double mod(double a, double b); //must use custom mod function because c++ mod/% does not work well with negative values.
	~Hill_Cipher(); //frees up memory

};

#endif
