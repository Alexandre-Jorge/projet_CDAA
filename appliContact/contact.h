#include <iostream>
#include <ctime>
#include <list>
#include <chrono>
#include "gestionlienintertache.h"

/// @class Contact
/// @brief classe representant un Contact
class Contact{
    private:
        std::string nom; //!<Nom du contact
        std::string prenom; //!<Prenom du contact
        std::string entreprise; //!<Nom de l'entreprise
        std::string mail; //!<Addresse email
        std::list<unsigned> telephone; //!<Liste unsigned du numéro de téléphone
        std::string photo; //!<URL de la photo
        struct sdate dateCreation; //!<Date de création du contact
        struct sdate dateModification; //!<Date de dernière modification du contact
        GestionLienIntertache glit; //!<Liste des interactions/taches du contact
    public:
        Contact();
        Contact(std::string, std::string, std::string, std::string, std::list<unsigned>, std::string);
        Contact(std::string, std::string, std::string, std::string, std::list<unsigned>, std::string, sdate, sdate);
        Contact(const Contact&);
        ~Contact();
        std::string getNom();
        std::string getPrenom();
        std::string getEntreprise();
        std::string getMail();
        std::list<unsigned> getTelephone();
        std::string getPhoto();
        sdate getDateCreation();
        sdate getDateModification();
        GestionLienIntertache getGlit();
        void setNom(std::string);
        void setPrenom(std::string);
        void setEntreprise(std::string);
        void setMail(std::string);
        void setTelephone(std::list<unsigned>);
        void setPhoto(std::string);
        void setDateCreation(sdate);
        void setGlit(GestionLienIntertache);
        void setDateModification(sdate);
        void updateModification();
        friend std::ostream& operator<<(std::ostream&, const Contact&);
        bool operator==(const Contact&);
};
