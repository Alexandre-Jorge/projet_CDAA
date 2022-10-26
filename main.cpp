#include "gestioncontact.h"

bool testContact(){
	Contact c1 = Contact("Doe", "John", "Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
}

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

