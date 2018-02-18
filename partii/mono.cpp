#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <random>

int main(int argc, char** argv){
	//Bulletproofing
	if((argc != 4) && (argc != 5)){
		fprintf(stderr, "Incorrect number of arguments. Proper use of this program is as follows:\n./mono <inputfile> <outputfile> <seed> 0/1\n");
		exit(1);
	}

	//Grab in/out file from command line
	std::ifstream inputFile(argv[1], std::ios_base::in);
	std::ofstream outputFile(argv[2], std::ios_base::out);

	//Select encryption or decryption
	bool encrypting;
	if(argc == 4){
		if(atoi(argv[3]) == 0){
			encrypting = false;
		}
		else if(atoi(argv[3]) == 1){
			encrypting = true;
		}
		else{
			fprintf(stderr, "Incorrect argument format. Exiting...\n");
			exit(1);
		}
	}
	else if(argc == 5){
		if(atoi(argv[4]) == 0){
			encrypting = false;
		}
		else if(atoi(argv[4]) == 1){
			encrypting = true;
		}
		else{
			fprintf(stderr, "Incorrect argument format. Exiting...\n");
			exit(1);
		}
	}
	else{
		fprintf(stderr, "How did you even get here?");
		exit(1);
	}

	//Set random seed from command line, if used. Otherwise, default value is 1.
	int seed = 1;
	if(argc == 5){
		seed = atoi(argv[3]);
	}
	srand(seed);

	//Get data from inputFile
	std::string stringIn;
	inputFile >> stringIn;

	//Convert string to chars for easy conversion
	const char* charsIn = stringIn.c_str();

	/*Generate letter mapping. bool used[26] keeps track of which letters have been
	assigned, encyptionMap keeps track of which letter is assigned to what.*/
	bool used[26];
	for(int i = 0; i < 26; i++){
		used[i] = false;
	}

	char encryptionMap[26];
	for(int i = 0; i < 26; i++){
		int mapping = rand() % 26 + 97;
		while(used[mapping - 97]){
			mapping = rand() % 26 + 97;
		}
		encryptionMap[i] = mapping;
		used[mapping - 97] = true;
	}

	//Generate decryption mapping
	char decryptionMap[26];
	for(int i = 0; i < 26; i++){
		decryptionMap[encryptionMap[i] - 97] = (i + 97);
	}

	//Encrypt or decrypt
	char* charsOut = new char[10000];
	if(encrypting){
		for(size_t i = 0; i < (10000); i++){
			charsOut[i] = encryptionMap[(int)charsIn[i] - 97];
		}
	}
	else{
		for(size_t i = 0; i < (10000); i++){
			charsOut[i] = decryptionMap[(int)charsIn[i] - 97];
		}
	}

	outputFile << charsOut;

	//Print out cipher
	for(int i = 0; i < 26; i++){
		printf("%c-%c", (char) (i + 97), (char) (encryptionMap[i]));
		if(i != 25){
			printf(", ");
		}
	}
	printf("\n");
	return 0;
}
