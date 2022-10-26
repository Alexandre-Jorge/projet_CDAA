#include "interaction.h"
#include <iostream>

Interaction::Interaction(){
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateInteract = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
    this->contenu = "";
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
    return  this->dateInteract.jour == interaction.dateInteract.jour &&
            this->dateInteract.mois == interaction.dateInteract.mois &&
            this->dateInteract.annee == interaction.dateInteract.annee &&
            this->contenu == interaction.contenu;
}