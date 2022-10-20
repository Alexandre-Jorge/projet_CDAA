#include "contact.h"

Contact::Contact(){
    this->nom = "";
    this->prenom = "";
    this->mail = "";
    this->telephone = "";
    this->photo = "";
    this->dateCreation = Date();
    this->li = std::list<Interaction>();
}

Contact::~Contact(){
}

std::string Contact::getNom(){
    return this->nom;
}

std::string Contact::getPrenom(){
    return this->prenom;
}

std::string Contact::getMail(){
    return this->mail;
}

std::string Contact::getTelephone(){
    return this->telephone;
}

std::string Contact::getPhoto(){
    return this->photo;
}

Date Contact::getDateCreation(){
    return this->dateCreation;
}

std::list<Interaction> Contact::getLi(){
    return this->li;
}

void Contact::setNom(std::string nom){
    this->nom = nom;
}

void Contact::setPrenom(std::string prenom){
    this->prenom = prenom;
}

void Contact::setMail(std::string mail){
    this->mail = mail;
}

void Contact::setTelephone(std::string telephone){
    this->telephone = telephone;
}

void Contact::setPhoto(std::string photo){
    this->photo = photo;
}

void Contact::setDateCreation(Date dateCreation){
    this->dateCreation = dateCreation;
}

void Contact::setLi(std::list<Interaction> li){
    this->li = li;
}
