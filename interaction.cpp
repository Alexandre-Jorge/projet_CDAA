#include "interaction.h"

Interaction::Interaction(){
    this->dateInteract = Date();
    this->contenu = "";
}

Interaction::~Interaction(){
}

Date Interaction::getDateInteract(){
    return this->dateInteract;
}

std::string Interaction::getContenu(){
    return this->contenu;
}

void Interaction::setDateInteract(Date dateInteract){
    this->dateInteract = dateInteract;
}

void Interaction::setContenu(std::string contenu){
    this->contenu = contenu;
}
