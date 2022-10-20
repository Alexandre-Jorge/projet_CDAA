#include <iostream>

class Contact{
    private:
        std::string nom;
        std::string prenom;
        std::string mail;
        std::string telephone;
        std:string photo;
        Date dateCreation;
        std::list<Interaction> li;
    public:
        Contact();
        ~Contact();
        std::string getNom();
        std::string getPrenom();
        std::string getMail();
        std::string getTelephone();
        std::string getPhoto();
        Date getDateCreation();
        std::list<Interaction> getLi();
        void setNom(std::string nom);
        void setPrenom(std::string prenom);
        void setMail(std::string mail);
        void setTelephone(std::string telephone);
        void setPhoto(std::string photo);
        void setDateCreation(Date dateCreation);
        void setLi(std::list<Interaction> li);
        friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
}