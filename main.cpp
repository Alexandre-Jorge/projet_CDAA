#include "gestioncontact.h"
#include "gestionlienintertache.h"
using namespace std;

bool testContact(){
//Test des différentes fonctions de la classe contact
	bool res = true;
	Contact c1 = Contact("Doe", "John","google" ,"Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
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
	Contact c1 = Contact("Doe", "John","google" ,"Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
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
	gc1+=c1;
	cout << "Taille :" <<gc1.getLc().size() << endl;
	cout << gc1 << endl;
	gc1-=c1;
	cout << "Taille :" <<gc1.getLc().size() << endl;
	cout << gc1 << endl;
}

void testInteraction(){
	Contact c1 = Contact("Doe", "John","google" ,"Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
	GestionLienIntertache gli1;
	c1.setDateModification({15,12,2022});
	//cout << "c1 : " << c1 << endl;
	Interaction i("test de contenu");
	Interaction i2("@todo test de contenu2");
	Interaction i3("@todo test de contenu3 @date 15/12/2022");
	c1.ajouteInteraction(i);
	gli1.creeLien(c1.getInteraction(0));
	cout << "gli1 : " << gli1 << endl;
	cout << "c1 : " << c1 << endl;
	gli1.retireLien(c1.getInteraction(0));
	c1.retireInteraction(i);
	cout << "gli1 : " << gli1 << endl;
	cout << "c1 : " << c1 << endl;
	c1.ajouteInteraction(i2);
	gli1.creeLien(c1.getInteraction(0));
	c1.ajouteInteraction(i3);
	gli1.creeLien(c1.getInteraction(1));
	cout << "gli1 : " << gli1 << endl;
	cout << "c1 : " << c1 << endl;
}

int main()
{
	cout << "testContact : " << testContact() << endl;
	testGestionContact();
	testInteraction();


	//gerer toutes les exceptions y compris dans les setteurs
	return 0;
}

