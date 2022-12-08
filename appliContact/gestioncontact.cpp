#include "gestioncontact.h"

/// @brief constructeur par defaut
GestionContact::GestionContact(){
    this->lc = std::list<Contact>();
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}
/// @brief constructeur avec paramètre
/// @param std::list<Contact> lc
GestionContact::GestionContact(std::list<Contact> lc){
    this->lc = lc;
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}
/// @brief constructeur avec paramètre
/// @param std::list<Contact> lc, sdate dateModification
GestionContact::GestionContact(std::list<Contact> lc, sdate dateModification){
	this->lc = lc;
	this->dateModification = dateModification;
}
/// @brief constructeur par clonage
/// @param const GestionContact& gc
GestionContact::GestionContact(const GestionContact& gc){
	this->lc = gc.lc;
	this->dateModification = gc.dateModification;
}
/// @brief destructeur
GestionContact::~GestionContact(){
}
/// @brief renvoie la liste de contact
/// @return std::list<Contact>
std::list<Contact> GestionContact::getLc(){
    return this->lc;
}
/// @brief modifie la liste de contact
/// @param std::list<Contact> lc
void GestionContact::setLc(std::list<Contact> lc){
    this->lc = lc;
}
/// @brief renvoie la date de modification
/// @return sdate
sdate GestionContact::getDateModification(){
    return this->dateModification;
}
/// @brief modifie la date de modification
/// @param sdate dateModification
void GestionContact::setDateModification(sdate dateModification){
    this->dateModification = dateModification;
}

/// @brief Met à jour la dateModification à aujourd'hui
void GestionContact::updateModification(){
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

/// @brief Ajoute un contact à la fin de la liste lc.
/// @param Contact c
void GestionContact::ajouteContact(Contact c){
	this->lc.push_back(c);
	this->updateModification();
}

/// @brief Retire le contact c de la liste lc.
/// @param Contact c
void GestionContact::retireContact(Contact c){
    this->lc.remove(c);//todo throw exception si pas trouvé
	this->updateModification();
}

/// @brief Retire le contact à l'indice i de la liste lc.
/// @param unsigned i
void GestionContact::retireContact(unsigned i){
    this->retireContact(*(this->getContact(i)));
}

/// @brief Renvoie le contact à l'indice i de la liste lc.
/// @param unsigned i
/// @return Contact *
Contact * GestionContact::getContact(unsigned i){
    unsigned j=0;
    for (std::list<Contact>::iterator it = this->lc.begin(); it != this->lc.end(); ++it){
        if (i==j){
            return &(*it);
        }
		j++;
    }
    return nullptr;//todo throws exception
}
/// @brief renvoie le nombre de contact dans la liste
/// @return int
int GestionContact::taille(){
    return static_cast<int>(this->lc.size());
}
/// @brief surcharge operateur << : affichage en console de GestionContact
/// @param std::ostream& os, const GestionContact& gc
/// @return std::ostream&
std::ostream& operator<<(std::ostream& os, const GestionContact& gc){
	for (std::list<Contact>::const_iterator it = gc.lc.begin(); it != gc.lc.end(); ++it){
		os << *it << std::endl;
	}
	return os;
}

/// @brief surcharge opérateur += : ajoute un contact à la liste lc
/// @param const Contact& contact
/// @return GestionContact
GestionContact GestionContact::operator+=(const Contact& contact){
	this->ajouteContact(contact);
	return *this;
}

/// @brief surcharge opérateur -= : retire un contact de la liste lc
/// @param const Contact& contact
/// @return  GestionContact
GestionContact GestionContact::operator-=(const Contact& contact){
	this->retireContact(contact);
	return *this;
}
