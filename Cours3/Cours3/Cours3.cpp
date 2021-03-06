// Cours3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "IntArray.hpp"
#include "Util.hpp"
#include <iostream>
#include "List.hpp"
#include "Tree.hpp"

void testFloatTree() {
	FloatTree * tree = new FloatTree();
	Node<float> * leaf = new Node<float>(8);
	leaf->insert(4);
	leaf->insert(300);
	leaf->insert(19);
	leaf->insert(5);
	leaf->insert(80);
	bool d = leaf->Contains(6);
	leaf->remove(19);
	tree->root = leaf;
	tree->dfsPrint();
	int i = 0;
}

void TestIntList() {
	IntList *  l = new IntList(8);
	l->Append(5);
	l->Append(3);
	l = l->Concat(10);
	bool c = l->Contains(5);
	l->Remove(5);
	c = l->Contains(5);
	int j = l->Length();
	c = l->Contains(666);
	int i = 0;
}
int main()
{
	
	testFloatTree();
	/*IntArray A(1024);
	A.FillWithRandom(1024);

	A.InSort();
	double t0 = TimeUtils::getTimestamp();
	int B = A.BinarySearch(666);
	//int C = A.searchposition(666);
	//A.OneSort();
	double t1 = TimeUtils::getTimestamp();
	printf("%f     ", (t1-t0));
	int i = 0;*/
	//TestIntList();
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
