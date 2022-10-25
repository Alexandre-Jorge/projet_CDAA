#include "contact.h"

class GestionContact{
    private:
        std::list<Contact> lc;
        struct sdate dateModification;//dernier ajout / suppression / modification
    public:
        GestionContact();
        ~GestionContact();
        GestionContact(std::list<Contact> lc);

        std::list<Contact> getLc();
        void setLc(std::list<Contact> lc);
        sdate getDateModification();
        void setDateModification(sdate dateModification);
        void ajouteContact(Contact c);
        void retireContact(Contact c);

};
