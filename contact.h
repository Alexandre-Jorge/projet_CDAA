#include <iostream>
#include <ctime>
#include <list>
#include <chrono>
#include "interaction.h"


class Contact{
    private:
        std::string nom;
        std::string prenom;
        std::string mail;
        std::list<unsigned> telephone;
        std::string photo;
        struct sdate dateCreation;
        struct sdate dateModification;
        std::list<Interaction> li;
    public:
        Contact();
        ~Contact();
        std::string getNom();
        std::string getPrenom();
        std::string getMail();
        std::list<unsigned> getTelephone();
        std::string getPhoto();
        sdate getDateCreation();
        sdate getDateModification();
        std::list<Interaction> getLi();
        void setNom(std::string nom);
        void setPrenom(std::string prenom);
        void setMail(std::string mail);
        void setTelephone(std::list<unsigned> telephone);
        void setPhoto(std::string photo);
        void setDateCreation(sdate dateCreation);
        void setLi(std::list<Interaction> li);
        void setDateModification(sdate dateModification);
        void ajouteInteraction(Interaction i);
        void retireInteraction(Interaction i);
        friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
};
