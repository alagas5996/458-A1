Alexander Lagas - alagas1@binghamton.edu
Programming assignment I - CS 458

This program was (not yet but will be) tested on bingsuns.binghamton.edu.

This program can be executed as per the assignment instructions, i.e:
	./mono <inputfile> <outputfile> <seed> 1/0
	- inputfile: input file name
	- outputfile: output file name
	- seed: the seed used to generate the mapping
	- 1/0: encryption/decryption

The algorithm used to generate the encryption is fairly straightforward. Given the seed, the program uses rand() to generate a mapping from each letter to another. Each letter is only used once, ensured by a tracking array bool used[26]. The decryption array is simply the reverse of the encryption array. Once the encryption and decryption arrays have been generated, the program simply loops through the input one letter at a time, translating it into an output string. This string is then saved in the output file.
