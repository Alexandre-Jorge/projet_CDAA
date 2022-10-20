#include "contact.h"
#include "interraction.h"
#include "tache.h"
#include "gestioncontact.h"

void testConstructeur(){
	//Créer un contact
	Contact c1;
	c1.println();
	delete c1;

	
	//Créer une interraction
	Interraction i1;
	i1.println();
	delete i1;
	
	//Créer une tache
	Tache t1;
	t1.println();
	delete t1;
	
	return;
}


int main()
{
	GestionContact g;
	testConstructeur();
	
	g.Ajoute(new Contact());
	
	

	return 0;
}

