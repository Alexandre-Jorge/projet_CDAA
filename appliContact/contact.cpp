#include "contact.h"

Contact::Contact(){//constructeur par defaut
    this->nom = "";
    this->prenom = "";
    this->entreprise = "";
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

Contact::Contact(std::string nom, std::string prenom,std::string entreprise ,std::string mail, std::list<unsigned> telephone, std::string photo){
    this->nom = nom;
    this->prenom = prenom;
    this->entreprise = entreprise;
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
    this->entreprise = c.entreprise;
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

std::string Contact::getEntreprise(){
    return this->entreprise;
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

/// @brief Renvoie l'interaction à l'indice i de la liste li.
/// @param i int
/// @return Interaction*
Interaction* Contact::getInteraction(int i){
    int j=0;
	for (std::list<Interaction>::iterator it = this->li.begin(); it != this->li.end(); ++it){
        if (i==j){
            return &(*it);
        }
		j++;
    }
	return new Interaction();//todo throws execption
}

void Contact::setNom(std::string nom){
    this->nom = nom;
    this->updateModification();
}

void Contact::setPrenom(std::string prenom){
    this->prenom = prenom;
    this->updateModification();
}

void Contact::setEntreprise(std::string entreprise){
    this->entreprise = entreprise;
    this->updateModification();
}

void Contact::setMail(std::string mail){
    this->mail = mail;
    this->updateModification();
}

void Contact::setTelephone(std::list<unsigned> telephone){
    this->telephone = telephone;
    this->updateModification();
}

void Contact::setPhoto(std::string photo){
    this->photo = photo;
    this->updateModification();
}

void Contact::setDateCreation(sdate dateCreation){
    this->dateCreation = dateCreation;
}


void Contact::setLi(std::list<Interaction> li){
    this->li = li;
    this->updateModification();
}

void Contact::setDateModification(sdate dateModification){
    this->dateModification = dateModification;
}

/// @brief Met à jour la dateModification à aujourd'hui
void Contact::updateModification(){
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

/// @brief Ajoute l'interaction i à la fin de la liste li.
/// @param i Interaction
void Contact::ajouteInteraction(Interaction i){
	this->li.push_back(i);
    this->updateModification();
}
/// @brief Retire l'interaction i de la liste li.
/// @param i Interaction
void Contact::retireInteraction(Interaction i){
    this->li.remove(i);
    this->updateModification();
}

/// @brief Retire l'interaction à l'indice i de la liste li.
/// @param i int
void Contact::retireInteraction(int i){
    int j=0;
    for (std::list<Interaction>::iterator it = this->li.begin(); it != this->li.end(); ++it){
        if (i==j){
            this->li.remove(*it);
            this->updateModification();
            return;
        }
        j++;
    }
}

std::ostream& operator<<(std::ostream& os, const Contact& contact){
    os << "Nom: " << contact.nom << std::endl;
    os << "Prenom: " << contact.prenom << std::endl;
    os << "Entreprise: " << contact.entreprise << std::endl;
    os << "Mail: " << contact.mail << std::endl;
    os << "Telephone: ";
    for (std::list<unsigned>::const_iterator it = contact.telephone.begin(); it != contact.telephone.end(); ++it){
        os << *it;
    }
    os << std::endl;
    os << "Photo: " << contact.photo << std::endl;
    os << "Date de creation: " << contact.dateCreation.jour << "/" << contact.dateCreation.mois << "/" << contact.dateCreation.annee <<std::endl;
    os << "Date de Modification: " << contact.dateModification.jour << "/" << contact.dateModification.mois << "/" << contact.dateModification.annee <<std::endl;
    os << "Liste d'interactions: " << std::endl;
    for (std::list<Interaction>::const_iterator it = contact.li.begin(); it != contact.li.end(); ++it){
        os << "\t" << *it;
    }
    os << std::endl;
    return os;
}

/// @brief Compare 2 contact si ils sont identiques ou non.
/// @param contact Contact
/// @return bool
bool Contact::operator==(const Contact& contact){
    return  this->nom == contact.nom &&
            this->prenom == contact.prenom &&
            this->entreprise == contact.entreprise &&
            this->mail == contact.mail &&
            this->telephone == contact.telephone &&
            this->photo == contact.photo &&
            this->dateCreation == contact.dateCreation &&
            this->dateModification == contact.dateModification;
}
