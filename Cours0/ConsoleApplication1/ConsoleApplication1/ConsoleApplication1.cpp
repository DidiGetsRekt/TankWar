// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
//#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <chrono>


int appel(int s){
	s++;
	return 0;
	}

Vec3 incrX(Vec3 _in) { // Ajouter & entre Vec3 et _in pour faire une reference et que le calcul sorte de la struct
	_in.x++;
	return _in;
}
Vec3 StackOverflow(Vec3 _in) {
	Vec3 temp = _in;
	temp.y++;
	return StackOverflow(temp);
}
int main()
{
   // std::cout << "Hello World!\n"; 

	//int foo = 0;
	//const char * label = "sapin";
	//const char label2[6] = { 's','a','p','i','n', 0 }; //0 très important!!! Finit le tableau
	//printf("Hello world this is a test: %d label : %s\n", foo, label);
	//printf("Hello world this is a test: label2 : %s\n", label2);
	//Vec3 toto = {1,2,3};
	//incrX(toto);
	//printf("x : %f", toto.x);
	//int i = 66;
	//i++;
	//Vec3 Bob = { 1,2,3 };
	//Bob = StackOverflow(Bob);
	//printf("val x: %f\n, bob.x");

	Vec3 VecTab[3];
	VecTab[0]= {1,2,3};
	VecTab[1]= {4,5,6};
	VecTab[2]= {7,8,9};
	
	printf("v0x %f\n", VecTab[0].x);

	Vec3 * t0 = 0;
	Vec3 * t1 = nullptr;
	Vec3 * t2 = &VecTab[1];

	(*t2).y = 777; //Change valeur du pointeur
	t2->y = 888; //pareil
	t2++; // ptr+1 => *ptr+= SizeOf(T)
	Vec3* iter = &VecTab[0];
	int i = 0;
	for (i = 0; i < 3; ++i) {
		printf("val vec x: %d \n", iter->x);
		iter++;
	}
	int _i = 0;
	auto start = std::chrono::system_clock::now();
	int * bigBlock = (int*)malloc(1024 * 1024 * 1024);
	for (int k = 0; k < 256 * 1024 * 1024; ++k) {
		bigBlock[k] = 0xdeadbeef;
	}

	printf("beef ? : %x \n", bigBlock[1024*1024]);

	auto end = std::chrono::system_clock::now();

	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	printf("time ? : %d\n", millis);

}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
