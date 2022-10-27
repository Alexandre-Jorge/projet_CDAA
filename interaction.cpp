#include "interaction.h"
#include <iostream>

Interaction::Interaction(){
    this->contenu = "";
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateInteract = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

Interaction::Interaction(const std::string contenu){
    this->contenu = contenu;
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateInteract = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

Interaction::Interaction(const std::string contenu,const sdate dateInteract){
    this->contenu = contenu;
    this->dateInteract = dateInteract;
}

Interaction::Interaction(const Interaction& interaction){
    this->contenu = interaction.contenu;
    this->dateInteract = interaction.dateInteract;
}

Interaction::~Interaction(){
}

sdate Interaction::getDateInteract(){
    return this->dateInteract;
}

std::string Interaction::getContenu(){
    return this->contenu;
}

void Interaction::setDateInteract(sdate dateInteract){
    this->dateInteract = dateInteract;
}

void Interaction::setContenu(std::string contenu){
    this->contenu = contenu;
}


std::ostream& operator<<(std::ostream& os, const Interaction& interaction){
        os << "Date de l'interaction : " << interaction.dateInteract.jour << "/" << interaction.dateInteract.mois << "/" << interaction.dateInteract.annee << std::endl;
        os << "Contenu de l'interaction : " << interaction.contenu << std::endl;
        return os;
}

bool Interaction::operator==(const Interaction& interaction){
    return  this->dateInteract == interaction.dateInteract &&
            this->contenu == interaction.contenu;
}