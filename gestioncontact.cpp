#include "gestioncontact.h"

GestionContact::GestionContact(){
    this->lc = std::list<Contact>();
}

GestionContact::~GestionContact(){
}

GestionContact::GestionContact(std::list<Contact> lc){
    this->lc = lc;
}

std::list<Contact> GestionContact::getLc(){
    return this->lc;
}

void GestionContact::setLc(std::list<Contact> lc){
    this->lc = lc;
}

void GestionContact::ajouteContact(Contact c){
	this->lc.pushback(c);
//	this->setDateModification();
}

void GestionContact::retireContact(Contact c){
	for (int i=0; i<this->lc.size(); i++){
		if (c=std::advance(this->lc,i){
			this->lc.erase(i);
//			this->setDateModification();
			break;
		}
	}
}
