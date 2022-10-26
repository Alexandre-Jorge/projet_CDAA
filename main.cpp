#include "gestioncontact.h"
using namespace std;

bool testContact(){
//Test des différentes fonctions de la classe contact
	bool res = true;
	Contact c1 = Contact("Doe", "John", "Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
	Contact c2 = Contact(c1);
	res = (c1==c2);
	c2.setNom("Doe2");
	res = res && !(c1==c2);
	c2.setTelephone({0,6,1,2,3,4,5,6,6,8});
	c2.setNom("Doe");
	res = res && !(c1==c2);
	Contact c3 = Contact();
	c3.setTelephone({0,6,1,2,3,4,5,6,7,8});
	res = res && c1.getTelephone()==c3.getTelephone();
	c3.setDateModification({15,12,2022});
	res = res && !(c1.getDateModification()==c3.getDateModification());
	return res;
}

void testGestionContact(){
//Test des différentes fonctions de la classe GestionContact
	Contact c1 = Contact("Doe", "John", "Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
	GestionContact gc1;
	gc1.ajouteContact(c1);
	Contact c2 = Contact();
	gc1.ajouteContact(c2);
	cout << "Taille :" <<gc1.getLc().size() << endl;
	cout << gc1 << endl;
	gc1.retireContact(c2);
	cout << "Taille :" <<gc1.getLc().size() << endl;
	cout << gc1 << endl;
	gc1.retireContact(0);
	cout << "Taille :" <<gc1.getLc().size() << endl;
	cout << gc1 << endl;
}

int main()
{
	cout << "testContact : " << testContact() << endl;
	//testGestionContact();


	//GestionContact.cpp: fonction retire contact: retirer (ou modifier) la boucle en commentaire
	//Ajouter updateDateInteraction dans contact (et décommenter ajouteInteraction/retireInteraction)
	//Ajouter SupprimerElt dans LienInterTache
	return 0;
}

