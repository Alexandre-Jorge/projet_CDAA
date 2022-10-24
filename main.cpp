#include "gestioncontact.h"

/*void testConstructeur(){
	//Créer un contact
	Contact c1;
	c1.println();
	delete c1;

	
	//Créer une interaction
	Interaction i1;
	i1.println();
	delete i1;
	
	//Créer une tache
	Tache t1;
	t1.println();
	delete t1;
	
	return;
}*/


int main()
{
	GestionContact g;
	//testConstructeur();
	Contact c1;
	c1.setNom("Doe");
	c1.setPrenom("John");
	c1.setMail("Doe.John@gmail.com");
	c1.setTelephone({0,6,1,2,3,4,5,6,7,8});
	c1.setPhoto("DoeJohnPic.jpg");
	std::cout << c1 << std::endl;
	//g.Ajoute(new Contact());
	
	return 0;
}

