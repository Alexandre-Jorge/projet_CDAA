#include "contact.h"

class GestionContact{
    private:
        std::list<Contact> lc;
        struct sdate dateModification;//dernier ajout / suppression / modification
    public:
        GestionContact();
        GestionContact(std::list<Contact> lc);
        GestionContact(std::list<Contact> lc, sdate dateModification);
        GestionContact(const GestionContact& gc);
        ~GestionContact();

        std::list<Contact> getLc();
        void setLc(std::list<Contact> lc);
        sdate getDateModification();
        void setDateModification(sdate dateModification);
        void updateModification();
        void ajouteContact(Contact c);
        void retireContact(Contact c);
        void retireContact(int i);
        Contact getContact(int i);
        friend std::ostream& operator<<(std::ostream& os, const GestionContact& gc);

};
