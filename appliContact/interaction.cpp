#include "interaction.h"
#include <iostream>
/// @brief constructeur par defaut
Interaction::Interaction(){
    this->contenu = "";
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateInteract = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}
/// @brief constructeur avec paramètre
/// @param const std::string contenu
Interaction::Interaction(const std::string contenu){
    this->contenu = contenu;
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateInteract = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}
/// @brief constructeur avec paramètre
/// @param const std::string contenu,const sdate dateInteract
Interaction::Interaction(const std::string contenu,const sdate dateInteract){
    this->contenu = contenu;
    this->dateInteract = dateInteract;
}
/// @brief constructeur par clonage
/// @param const Interaction& interaction
Interaction::Interaction(const Interaction& interaction){
    this->contenu = interaction.contenu;
    this->dateInteract = interaction.dateInteract;
}
/// @brief destructeur
Interaction::~Interaction(){
}
/// @brief renvoie la date de l'interaction
/// @return sdate
sdate Interaction::getDateInteract(){
    return this->dateInteract;
}
/// @brief renvoie le contenu de l'interaction
/// @return std::string
std::string Interaction::getContenu(){
    return this->contenu;
}
/// @brief modifie la date de l'interaction
/// @param sdate dateInteract
void Interaction::setDateInteract(sdate dateInteract){
    this->dateInteract = dateInteract;
}
/// @brief modifie le contenu de l'interaction
/// @param std::string contenu
void Interaction::setContenu(std::string contenu){
    this->contenu = contenu;
}

/// @brief Surcharge operateur << : affichage d'une interaction en console
/// @param std::ostream& os, const Interaction& interaction
/// @return std::ostream&
std::ostream& operator<<(std::ostream& os, const Interaction& interaction){
        os << "Date de l'interaction : " << interaction.dateInteract.jour << "/" << interaction.dateInteract.mois << "/" << interaction.dateInteract.annee << std::endl;
        os << "Contenu de l'interaction : " << interaction.contenu << std::endl;
        return os;
}

/// @brief surcharge operateur == : verifie si 2 Interactions sont égales
/// @param const Interaction& interaction
/// @return bool
bool Interaction::operator==(const Interaction& interaction){
    return  this->dateInteract == interaction.dateInteract &&
            this->contenu == interaction.contenu;
}
