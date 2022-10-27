#include <iostream>
#include <ctime>
#include <list>
#include <chrono>
#include "interaction.h"


class Contact{
    private:
        std::string nom; //!<Nom du contact
        std::string prenom; //!<Prénom du contact
        std::string entreprise; //!<Nom de l'entreprise
        std::string mail; //!<Addresse email
        std::list<unsigned> telephone; //!<Liste unsigned du numéro de téléphone
        std::string photo; //!<URL de la photo
        struct sdate dateCreation; //!<Date de création du contact
        struct sdate dateModification; //!<Date de dernière modification du contact
        std::list<Interaction> li; //!<Liste des interactions du contact
    public:
        Contact();
        Contact(std::string nom, std::string prenom,std::string entreprise ,std::string mail, std::list<unsigned> telephone, std::string photo);
        Contact(const Contact& c);
        ~Contact();
        std::string getNom();
        std::string getPrenom();
        std::string getEntreprise();
        std::string getMail();
        std::list<unsigned> getTelephone();
        std::string getPhoto();
        sdate getDateCreation();
        sdate getDateModification();
        std::list<Interaction> getLi();
        Interaction* getInteraction(int i);
        void setNom(std::string nom);
        void setPrenom(std::string prenom);
        void setEntreprise(std::string entreprise);
        void setMail(std::string mail);
        void setTelephone(std::list<unsigned> telephone);
        void setPhoto(std::string photo);
        void setDateCreation(sdate dateCreation);
        void setLi(std::list<Interaction> li);
        void setDateModification(sdate dateModification);
        void updateModification();
        void ajouteInteraction(Interaction i);
        void retireInteraction(Interaction i);
        void retireInteraction(int i);
        friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
        bool operator==(const Contact& contact);
};
