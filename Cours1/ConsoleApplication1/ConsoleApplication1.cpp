// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

static void TestRec();
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
int Max(int a, int b) {
	return (a < b) ? b : a;
}
int Min(int a, int b) {
	return (a < b) ? a : b;
}

int Strcmp(char* tekustoo, char*dororo) {
	int lentek = strlen(tekustoo);
	int lendor = strlen(dororo);

	int max =Max(lentek, lendor);
	int min = Min(lentek, lendor);
	for (int i = 0; i < min; i++) {
		if (tekustoo[i] < dororo[i]) {
			return 1;
		}
		else if (tekustoo[i] > dororo[i]) {
			return -1;
		}
	}
	if (max == min)
		return 0;
	if (max == lentek) return 1;

	return -1;
}
char* StrStr(char* tekusuto, char*dororu) {
	int length = strlen(dororu);
	char cmp[32] = "";
	int i = 0;
	while (tekusuto[i] !=0)
	{
		for (int j = 0; j < length; j++) {
			cmp[j] = tekusuto[i+j];
		}
		if (Strcmp(cmp, dororu) == 0)
			return tekusuto +i;

		i++;
	}

	return nullptr;
	
	
}
char* StrStr2(char*meuleDeFoin, char * aiguille) {
	int lenMeule = strlen(meuleDeFoin);
	int lenAiguille = strlen(aiguille);

	for (int i = 0; i < lenMeule; ++i) {
		bool found = true;
		for (int j = 0; j < lenAiguille; ++j) {
			if (meuleDeFoin[j] != aiguille[j]) {
				found = false;
				break;
			}
		}
		if (found)
			return meuleDeFoin;
		meuleDeFoin++;
	}
	return nullptr;
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


	char Texte[32] = "Lorem ipsum dolor sit amet";
	char token[32] = "dolor";
	char* TokenInText = StrStr(Texte, token);
	int pos = (int)(TokenInText - Texte);
	printf("Le dolor est en position %d \n", pos);

	char d[32] = "guardian";
	char e[32] = "guard";
	char f[32] = "can";
	char g[32] = "cannette";
	char h[32] = "bidule";
	char i[32] = "bidule";

	int a =Strcmp(d, e);
	int b =Strcmp(f, g);
	int c =Strcmp(h, i);
	
	TestRec();
}
int add(int a, int b) {
	int i = 0;
	for ( i = 0; i < a + b; ++i);
	return i;
}
int add2(int a, int b) {
	int val = a;
	for (int i = 0; i < b; ++i)
		val++;
	return val;
}
int add3(int a, int b) {
	if(a==0)
		return b;
	else 
		return add2(a - 1, b + 1);
}

int add4(int a, int b) {
	printf("%i %i ",a,b);
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else {
		int inter = 1 + add4(a - 1, b); //b est sur la pile
		return inter;
	}
	
}

int sub(int a, int b) {
	if (a == 0) return -b;
	if (b == 0) return a;
	if (b > 0) return sub(a,b-1) -1;
	if (b < 0) return sub(a, b+1) +1;

}

int mul(int a, int b) {
	if (a == 0) return 0;
	if (b == 0) return 0;
	//if (a == 1) return b;
	//if (b == 1) return a;
	//if (a == -1) return -b;
	//if (b == -1) return -a;
	if(b<0)return mul(a, b + 1) - a;
	else if(b>0)return mul(a, b - 1) + a;
}

void TestRec() {
	int i = 0;
	int doo = add3(2, 2);
	int foo = add4(10, -2);
	int hoo = mul(-2, 5);
}


