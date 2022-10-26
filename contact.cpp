#include "contact.h"

Contact::Contact(){
    this->nom = "";
    this->prenom = "";
    this->mail = "";
    this->telephone = std::list<unsigned>();
    this->photo = "";
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateCreation = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
    this->li = std::list<Interaction>();
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
    this->li = std::list<Interaction>();
}

Contact::Contact(std::string nom, std::string prenom, std::string mail, std::list<unsigned> telephone, std::string photo){
    this->nom = nom;
    this->prenom = prenom;
    this->mail = mail;
    this->telephone = telephone;
    this->photo = photo;
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateCreation = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
    this->li = std::list<Interaction>();
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
    this->li = std::list<Interaction>();
}

Contact::Contact(const Contact& c){
    this->nom = c.nom;
    this->prenom = c.prenom;
    this->mail = c.mail;
    this->telephone = c.telephone;
    this->photo = c.photo;
    this->dateCreation = c.dateCreation;
    this->li = c.li;
    this->dateModification = c.dateModification;
    this->li = c.li;
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

std::list<unsigned> Contact::getTelephone(){
    return this->telephone;
}

std::string Contact::getPhoto(){
    return this->photo;
}

sdate Contact::getDateCreation(){
    return this->dateCreation;
}

sdate Contact::getDateModification(){
    return this->dateModification;
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

void Contact::setTelephone(std::list<unsigned> telephone){
    this->telephone = telephone;
}

void Contact::setPhoto(std::string photo){
    this->photo = photo;
}

void Contact::setDateCreation(sdate dateCreation){
    this->dateCreation = dateCreation;
}

void Contact::setLi(std::list<Interaction> li){
    this->li = li;
}

void Contact::setDateModification(sdate dateModification){
    this->dateModification = dateModification;
}

void Contact::ajouteInteraction(Interaction i){
//Ajoute une interaction à la fin de la liste
	this->li.push_back(i);
//	this->setDateModification();
}
void Contact::retireInteraction(Interaction i){
//Retire une interaction de la liste
    for (std::list<Interaction>::iterator it = this->li.begin(); it != this->li.end(); ++it){
        if (i==*it){
            this->li.erase(it);
            break;
        }
    }
}
std::ostream& operator<<(std::ostream& os, const Contact& contact){
    os << "Nom: " << contact.nom << std::endl;
    os << "Prenom: " << contact.prenom << std::endl;
    os << "Mail: " << contact.mail << std::endl;
    os << "Telephone: ";
    for (std::list<unsigned>::const_iterator it = contact.telephone.begin(); it != contact.telephone.end(); ++it){
        os << *it;
    }
    os << std::endl;
    os << "Photo: " << contact.photo << std::endl;
    os << "Date de creation: " << contact.dateCreation.jour << "/" << contact.dateCreation.mois << "/" << contact.dateCreation.annee <<std::endl;
    os << "Date de Modification: " << contact.dateModification.jour << "/" << contact.dateModification.mois << "/" << contact.dateModification.annee <<std::endl;
    os << "Liste d'interactions: ";
    for (std::list<Interaction>::const_iterator it = contact.li.begin(); it != contact.li.end(); ++it){
        os << *it;
    }
    os << std::endl;
    return os;
}

bool Contact::operator==(const Contact& contact){
    return  this->nom == contact.nom &&
            this->prenom == contact.prenom &&
            this->mail == contact.mail &&
            this->telephone == contact.telephone &&
            this->photo == contact.photo &&
            this->dateCreation.jour == contact.dateCreation.jour &&
            this->dateCreation.mois == contact.dateCreation.mois &&
            this->dateCreation.annee == contact.dateCreation.annee &&
            this->dateModification.jour == contact.dateModification.jour &&
            this->dateModification.mois == contact.dateModification.mois &&
            this->dateModification.annee == contact.dateModification.annee;
}
