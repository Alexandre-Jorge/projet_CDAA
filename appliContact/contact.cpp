#include "contact.h"

/// @brief constructeur par defaut
Contact::Contact(){
    this->setNom("");
    this->setPrenom("");
    this->setEntreprise("");
    this->setMail("");
    this->setTelephone(std::list<unsigned>());
    this->setPhoto("");
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->setDateCreation({(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year});
    this->setGlit(GestionLienIntertache());
    this->setDateModification({(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year});
}
/// @brief constructeur avec paramètre
/// @param std::string nom, std::string prenom, std::string entreprise , std::string mail, std::list<unsigned> telephone, std::string photo
Contact::Contact(std::string nom, std::string prenom, std::string entreprise , std::string mail, std::list<unsigned> telephone, std::string photo){
    this->setNom(nom);
    this->setPrenom(prenom);
    this->setEntreprise(entreprise);
    this->setMail(mail);
    this->setTelephone(telephone);
    this->setPhoto(photo);
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->setDateCreation({(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year});
    this->setGlit(GestionLienIntertache());
    this->setDateModification({(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year});
}
/// @brief constructeur avec paramètre
/// @param std::string nom, std::string prenom, std::string entreprise , std::string mail, std::list<unsigned> telephone, std::string photo, sdate dateC, sdate dateM
Contact::Contact(std::string nom, std::string prenom, std::string entreprise , std::string mail, std::list<unsigned> telephone, std::string photo, sdate dateC, sdate dateM){
    this->setNom(nom);
    this->setPrenom(prenom);
    this->setEntreprise(entreprise);
    this->setMail(mail);
    this->setTelephone(telephone);
    this->setPhoto(photo);
    this->setDateCreation(dateC);
    this->setGlit(GestionLienIntertache());
    this->setDateModification(dateM);
}
/// @brief constructeur par clonage
/// @param const Contact& c
Contact::Contact(const Contact& c){
    this->setNom(c.nom);
    this->setPrenom(c.prenom);
    this->setEntreprise(c.entreprise);
    this->setMail(c.mail);
    this->setTelephone(c.telephone);
    this->setPhoto(c.photo);
    this->setDateCreation(c.dateCreation);
    this->setGlit(c.glit);
    this->setDateModification(c.dateModification);
}
/// @brief destructeur
Contact::~Contact(){
}

/// @brief renvoie le nom du contact
/// @return std::string
std::string Contact::getNom(){
    return this->nom;
}
/// @brief renvoie le prenom du contact
/// @return std::string
std::string Contact::getPrenom(){
    return this->prenom;
}
/// @brief renvoie l'entreprise du contact
/// @return std::string
std::string Contact::getEntreprise(){
    return this->entreprise;
}
/// @brief renvoie le mail du contact
/// @return std::string
std::string Contact::getMail(){
    return this->mail;
}
/// @brief renvoie le telephone du contact
/// @return std::list<unsigned>
std::list<unsigned> Contact::getTelephone(){
    return this->telephone;
}
/// @brief renvoie l'URL/URI de la photo du contact
/// @return std::string
std::string Contact::getPhoto(){
    return this->photo;
}
/// @brief renvoie la date de creation du contact
/// @return sdate
sdate Contact::getDateCreation(){
    return this->dateCreation;
}
/// @brief renvoie la date de modification du contact
/// @return sdate
sdate Contact::getDateModification(){
    return this->dateModification;
}
/// @brief renvoie la liste d'interaction/tache du contact
/// @return GestionLienIntertache
GestionLienIntertache Contact::getGlit(){
    return this->glit;
}
/// @brief modifie le nom du contact
/// @param std::string nom
void Contact::setNom(std::string nom){
    this->nom = nom;
    this->updateModification();
}
/// @brief modifie le prenom du contact
/// @param std::string prenom
void Contact::setPrenom(std::string prenom){
    this->prenom = prenom;
    this->updateModification();
}
/// @brief modifie l'entreprise du contact
/// @param std::string entreprise
void Contact::setEntreprise(std::string entreprise){
    this->entreprise = entreprise;
    this->updateModification();
}
/// @brief modifie le mail du contact
/// @param std::string mail
void Contact::setMail(std::string mail){
    this->mail = mail;
    this->updateModification();
}
/// @brief modifie le telephone du contact
/// @param std::list<unsigned> telephone
void Contact::setTelephone(std::list<unsigned> telephone){
    this->telephone = telephone;
    this->updateModification();
}
/// @brief modifie l'URL/URI de la photo du contact
/// @param std::string photo
void Contact::setPhoto(std::string photo){
    this->photo = photo;
    this->updateModification();
}
/// @brief modifie la date de creation du contact
/// @param sdate dateCreation
void Contact::setDateCreation(sdate dateCreation){
    this->dateCreation = dateCreation;
}
/// @brief modifie la date de modification du contact
/// @param sdate dateModification
void Contact::setDateModification(sdate dateModification){
    this->dateModification = dateModification;
}
/// @brief modifie la liste d'interaction/tache du contact
/// @param GestionLienIntertache glit
void Contact::setGlit(GestionLienIntertache glit){
    this->glit.setLit(glit.getLit());
    this->updateModification();
}
/// @brief Met à jour la dateModification à aujourd'hui
void Contact::updateModification(){
    time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->dateModification = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

/// @brief Surcharge operateur << : affichage d'un contact en console
/// @param std::ostream& os, const Contact& contact
/// @return std::ostream&
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
    os << "Liste Lien Inter Tache : " << contact.glit << std::endl;

    os << std::endl;
    return os;
}

/// @brief surcharge operateur == : verifie si 2 contacts sont égaux
/// @param const Contact& contact
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
