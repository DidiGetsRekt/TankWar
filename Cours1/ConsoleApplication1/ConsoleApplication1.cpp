// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

void Memcpy(char * dest, char * src, int size) {
	while (size != 0) {
		size--;
		dest[size] = src[size];
	}
}
void Memcpy2(char * dest, char * src, int size) {
	for (int i = 0; i < size; i++) {
		dest[i] = src[i];
	}
}

int Strchr(char *grange, char chat) {
	int length = strlen(grange);
	for (int i = 0; i < length; i++) {
		if (grange[i] == chat)
			return(i);
	}
	return(-1);
}
int Strchr2(char*grange, char chat) {
	int length = strlen(grange);
	int i = 0;
	while (i < length) {
		if (grange[i] == chat)
			return(i);
		i++;
	}
	return(-1);
}

int Strchr3(char*grange, char chat) {
	int i = 0;
	while (grange[i] != 0) {
		if (grange[i] == chat) {
			return i;
		}
		i++;
	}
	return -1;
}
int main()
{
    std::cout << "Hello World!\n"; 
	char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	//Memcpy(licorne, vomi, strlen(licorne)+1);
	Memcpy2(licorne, vomi, strlen(licorne) + 1);
	printf("licorne %s\n", licorne);
	char chateau[32] = "chateau";
	char soldat = 'e';
	int posSoldat = Strchr3(chateau, soldat);
	printf("Le soldat est en position %d \n", posSoldat);
}

