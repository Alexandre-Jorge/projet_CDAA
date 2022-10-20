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