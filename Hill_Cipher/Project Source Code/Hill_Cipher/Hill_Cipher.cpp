#include "Hill_Cipher.h"


Hill_Cipher::Hill_Cipher()
{
	this->message = "";
	this->mod_algorithm_num = 1;
	this->determinant = 0;
	for (int i = 0; i < 3;i++){
		for (int j = 0; j < 3; j++){
			key[i][j] = 0;
		}
	}
}
Hill_Cipher::Hill_Cipher(int* key, string message, int mod_algorithm_num)
{
	
	this->message = message;
	this->mod_algorithm_num = mod_algorithm_num;
	this->determinant = 0;
	for (int i = 0, a = 0; i < 3; i++){
		for (int j = 0; j < 3; j++ , a++){
			this->key[i][j] = key[a];
		}
	}
}
void Hill_Cipher::inverseKey()
{
	//finds the determinant
	determinant = ((key[0][0] * key[1][1] * key[2][2]) + (key[0][1] * key[1][2] * key[2][0]) + (key[0][2] * key[1][0] * key[2][1])) - ((key[2][0] * key[1][1] * key[0][2]) + (key[2][1] * key[1][2] * key[0][0]) + (key[2][2] * key[1][0] * key[0][1]));

	if (determinant == 0){ //if determinant is zero then there is no inverse matrix
		cout << "\n\nDeterminant is zero. No inverse matrix.\n\n";
	}
	double newMatrix[3][3]; //the new key.

	//finds matrix adjugates
	newMatrix[0][0] = ((key[1][1] * key[2][2]) - (key[2][1] * key[1][2])) * (+1);
	newMatrix[0][1] = ((key[1][0] * key[2][2]) - (key[2][0] * key[1][2])) * (-1);
	newMatrix[0][2] = ((key[1][0] * key[2][1]) - (key[2][0] * key[1][1])) * (+1);

	newMatrix[1][0] = ((key[0][1] * key[2][2]) - (key[2][1] * key[0][2])) * (-1);
	newMatrix[1][1] = ((key[0][0] * key[2][2]) - (key[2][0] * key[0][2])) * (+1);
	newMatrix[1][2] = ((key[0][0] * key[2][1]) - (key[2][0] * key[0][1])) * (-1);

	newMatrix[2][0] = ((key[0][1] * key[1][2]) - (key[1][1] * key[0][2])) * (+1);
	newMatrix[2][1] = ((key[0][0] * key[1][2]) - (key[1][0] * key[0][2])) * (-1);
	newMatrix[2][2] = ((key[0][0] * key[1][1]) - (key[1][0] * key[0][1])) * (+1);

	double temp = 0;
	//continued. matrix adjugates
	temp = newMatrix[0][1];
	newMatrix[0][1] = newMatrix[1][0];
	newMatrix[1][0] = temp;


	temp = newMatrix[0][2];
	newMatrix[0][2] = newMatrix[2][0];
	newMatrix[2][0] = temp;


	temp = newMatrix[1][2];
	newMatrix[1][2] = newMatrix[2][1];
	newMatrix[2][1] = temp;

	//finds inverse mod of the determinant using the mod alorithm number.
	int inverseMod = modInverse(mod(determinant, mod_algorithm_num), mod_algorithm_num);

	//sets the oldKey to the newKey.
	key[0][0] = mod(newMatrix[0][0] * inverseMod, mod_algorithm_num);
	key[0][1] = mod(newMatrix[0][1] * inverseMod, mod_algorithm_num);
	key[0][2] = mod(newMatrix[0][2] * inverseMod, mod_algorithm_num);

	key[1][0] = mod(newMatrix[1][0] * inverseMod, mod_algorithm_num);
	key[1][1] = mod(newMatrix[1][1] * inverseMod, mod_algorithm_num);
	key[1][2] = mod(newMatrix[1][2] * inverseMod, mod_algorithm_num);

	key[2][0] = mod(newMatrix[2][0] * inverseMod, mod_algorithm_num);
	key[2][1] = mod(newMatrix[2][1] * inverseMod, mod_algorithm_num);
	key[2][2] = mod(newMatrix[2][2] * inverseMod, mod_algorithm_num);
	//the key is now the inverse key.
}
void Hill_Cipher::encryption()
{
	int messageSize = message.length(); //gets length of message.
	while ((messageSize % 3) != 0){ //message must be a multiple of 3s
		messageSize += 1;
	}
	messageChar = new char[messageSize];
	for (int i = 0; i < messageSize; i++){ //converts the string to a char array
		if (i > message.length()){
			messageChar[i] = 'z'; //fills in empty space in message with z.
		}
		else{
			messageChar[i] = tolower(message[i]); //converts uppercase to lowercase char.
		}
	}

	delete[] messageNum; //delete old messageNum
	messageNum = convertCharToNum(messageChar, messageSize); //converts char to num form.

	for (int i = 0; i < messageSize; i+=3){ //matrix multiplication
		
		double temp1 = mod(((key[0][0] * messageNum[i]) + (key[0][1] * messageNum[i + 1]) + (key[0][2] * messageNum[i + 2])), mod_algorithm_num);
		double temp2 = mod(((key[1][0] * messageNum[i]) + (key[1][1] * messageNum[i + 1]) + (key[1][2] * messageNum[i + 2])), mod_algorithm_num);
		double temp3 = mod(((key[2][0] * messageNum[i]) + (key[2][1] * messageNum[i + 1]) + (key[2][2] * messageNum[i + 2])), mod_algorithm_num);

		messageNum[i] = temp1;
		messageNum[i + 1] = temp2;
		messageNum[i + 2] = temp3;
	}
	
	delete[] messageChar; //delete old char
	messageChar = convertNumToChar(messageNum, messageSize); //replace old char array with the encrypted one.

	message = string(messageChar,messageSize); //converts char array to string.

}
void Hill_Cipher::decryption()
{
	inverseKey(); //inverse the key then use key to encrypt message.
	encryption(); //encryption method using the inverse key will result in decryption.
}
double* Hill_Cipher::getMessageNum(){
	return messageNum;
}
string Hill_Cipher::getMessage(){
	return message;
}
void Hill_Cipher::printKey(){
	cout << "Key: \n";
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			cout << key[i][j] << " ";
		}
		cout << endl;
	}
}
double* Hill_Cipher::convertCharToNum(char* messageChar, int messageSize){
	double* messageNumNew = new double[messageSize];
	for (int i = 0; i < messageSize; i++){
		switch (messageChar[i]){
		case 'a':
			messageNumNew[i] = 0;
			break;
		case 'b':
			messageNumNew[i] = 1;
			break;
		case 'c':
			messageNumNew[i] = 2;
			break;
		case 'd':
			messageNumNew[i] = 3;
			break;
		case 'e':
			messageNumNew[i] = 4;
			break;
		case 'f':
			messageNumNew[i] = 5;
			break;
		case 'g':
			messageNumNew[i] = 6;
			break;
		case 'h':
			messageNumNew[i] = 7;
			break;
		case 'i':
			messageNumNew[i] = 8;
			break;
		case 'j':
			messageNumNew[i] = 9;
			break;
		case 'k':
			messageNumNew[i] = 10;
			break;
		case 'l':
			messageNumNew[i] = 11;
			break;
		case 'm':
			messageNumNew[i] = 12;
			break;
		case 'n':
			messageNumNew[i] = 13;
			break;
		case 'o':
			messageNumNew[i] = 14;
			break;
		case 'p':
			messageNumNew[i] = 15;
			break;
		case 'q':
			messageNumNew[i] = 16;
			break;
		case 'r':
			messageNumNew[i] = 17;
			break;
		case 's':
			messageNumNew[i] = 18;
			break;
		case 't':
			messageNumNew[i] = 19;
			break;
		case 'u':
			messageNumNew[i] = 20;
			break;
		case 'v':
			messageNumNew[i] = 21;
			break;
		case 'w':
			messageNumNew[i] = 22;
			break;
		case 'x':
			messageNumNew[i] = 23;
			break;
		case 'y':
			messageNumNew[i] = 24;
			break;
		case 'z':
			messageNumNew[i] = 25;
			break;
		default:
			messageNumNew[i] = 25;
			break;
		}
	}
	return messageNumNew;
}
char* Hill_Cipher::convertNumToChar(double* messageNum, int messageSize){
	char* messageCharNew = new char[messageSize];
	for (int i = 0; i < messageSize; i++){
		switch ((int)messageNum[i]){
		case 0:
			messageCharNew[i] = 'a';
			break;
		case 1:
			messageCharNew[i] = 'b';
			break;
		case 2:
			messageCharNew[i] = 'c';
			break;
		case 3:
			messageCharNew[i] = 'd';
			break;
		case 4:
			messageCharNew[i] = 'e';
			break;
		case 5:
			messageCharNew[i] = 'f';
			break;
		case 6:
			messageCharNew[i] = 'g';
			break;
		case 7:
			messageCharNew[i] = 'h';
			break;
		case 8:
			messageCharNew[i] = 'i';
			break;
		case 9:
			messageCharNew[i] = 'j';
			break;
		case 10:
			messageCharNew[i] = 'k';
			break;
		case 11:
			messageCharNew[i] = 'l';
			break;
		case 12:
			messageCharNew[i] = 'm';
			break;
		case 13:
			messageCharNew[i] = 'n';
			break;
		case 14:
			messageCharNew[i] = 'o';
			break;
		case 15:
			messageCharNew[i] = 'p';
			break;
		case 16:
			messageCharNew[i] = 'q';
			break;
		case 17:
			messageCharNew[i] = 'r';
			break;
		case 18:
			messageCharNew[i] = 's';
			break;
		case 19:
			messageCharNew[i] = 't';
			break;
		case 20:
			messageCharNew[i] = 'u';
			break;
		case 21:
			messageCharNew[i] = 'v';
			break;
		case 22:
			messageCharNew[i] = 'w';
			break;
		case 23:
			messageCharNew[i] = 'x';
			break;
		case 24:
			messageCharNew[i] = 'y';
			break;
		case 25:
			messageCharNew[i] = 'z';
			break;
		default:
			messageCharNew[i] = 'z';
			break;
		}
	}
	return messageCharNew;
}
int Hill_Cipher::modInverse(int a, int m) {
	// Inverse of mod.a*x = 1 (mod b)
	a %= m;
	for (int x = 1; x < m; x++) {
		if ((a*x) % m == 1) return x;
	}
}

double Hill_Cipher::mod(double a, double b){
	return fmod((fmod(a , b) + b) , b); //Will work with negative values of a.
}

Hill_Cipher::~Hill_Cipher(){
	delete[] messageChar;
	delete[] messageNum;
}