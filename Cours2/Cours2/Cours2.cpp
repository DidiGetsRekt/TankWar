// Cours2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "IntArray.hpp"
#include <string>

int main()
{  
	std::string nameTab0 = "tab0";
	std::string nameTab1 = "tab1";
	{//variable dynamique
		//auto montableau = new IntArray(16);
		//IntArray * montableau = new IntArray(16);
	//variable locale
		//IntArray Montableau = IntArray(16);
		IntArray tab0 = IntArray(16, nameTab0);
	}
	{
		IntArray * tab1 = new IntArray(16, nameTab1); 
		//delete(tab1);
		//tab1 = nullptr;
		tab1->Ensure(32);
	}
	

	IntArray * tab2 = new IntArray(16, "test1");
	for (int i = 0; i < 16; i++)
	{
		tab2->set(i, i+1);

	}
	for (int i = 0; i < tab2->maxSize; i++)
	{
		printf(" %d", (*tab2)[i]);

	}
	tab2->push_back(17);
	for (int i = 0; i < tab2->maxSize; i++)
	{
		printf(" %d", (*tab2)[i]);

	}
	tab2->push_first(0);
	for (int i = 0; i < tab2->maxSize; i++)
	{
		printf(" %d", (*tab2)[i]);

	}
	
	tab2->insert(5, 666);
	for (int i = 0; i < tab2->maxSize; i++)
	{
		printf(" %d", (*tab2)[i]);

	}
	printf("gud");
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
