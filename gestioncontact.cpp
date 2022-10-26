#include "gestioncontact.h"


GestionContact::GestionContact(){
    this->lc = std::list<Contact>();
}

GestionContact::GestionContact(std::list<Contact> lc){
    this->lc = lc;
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



void GestionContact::ajouteContact(Contact c){
//Ajoute un contact à la fin de la liste
	this->lc.push_back(c);
//	this->setDateModification();
}


void GestionContact::retireContact(Contact c){
//Retire le contact de la liste
	for(std::list<Contact>::iterator it = this->lc.begin(); it != this->lc.end(); ++it){
		if (c==*it){
			this->lc.erase(it);
		}
	}
}
