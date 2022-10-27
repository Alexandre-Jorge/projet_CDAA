#include "gestioncontact.h"


GestionContact::GestionContact(){
    this->lc = std::list<Contact>();
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

GestionContact::GestionContact(std::list<Contact> lc){
    this->lc = lc;
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

GestionContact::GestionContact(std::list<Contact> lc, sdate dateModification){
	this->lc = lc;
	this->dateModification = dateModification;
}

GestionContact::GestionContact(const GestionContact& gc){
	this->lc = gc.lc;
	this->dateModification = gc.dateModification;
}

GestionContact::~GestionContact(){
}

std::list<Contact> GestionContact::getLc(){
    return this->lc;
}

void GestionContact::setLc(std::list<Contact> lc){
    this->lc = lc;
}

void GestionContact::updateModification(){
	//Défini dateModification au jour actuel
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

void GestionContact::ajouteContact(Contact c){
	//Ajoute un contact à la fin de la liste
	this->lc.push_back(c);
	this->updateModification();
}


void GestionContact::retireContact(Contact c){
	//Retire le contact de la liste et chage la date de modification
	this->lc.remove(c);//todo throw exception if not found
	this->updateModification();
}

void GestionContact::retireContact(int i){
	//Retire le contact à l'indice i de la liste
	this->retireContact(this->getContact(i));
}

Contact GestionContact::getContact(int i){
	//Renvoie le contact à l'indice i de la liste
	int j=0;
	for (std::list<Contact>::iterator it = this->lc.begin(); it != this->lc.end(); ++it){
        if (i==j){
            return *it;
        }
		j++;
    }
	return Contact();//todo throws execption
}

std::ostream& operator<<(std::ostream& os, const GestionContact& gc){
	for (std::list<Contact>::const_iterator it = gc.lc.begin(); it != gc.lc.end(); ++it){
		os << *it << std::endl;
	}
	return os;
}

GestionContact GestionContact::operator+=(const Contact& contact){
	//Ajoute un contact à la fin de la liste
	this->ajouteContact(contact);
	return *this;
}

GestionContact GestionContact::operator-=(const Contact& contact){
	//Retire le contact de la liste et chage la date de modification
	this->retireContact(contact);
	return *this;
}