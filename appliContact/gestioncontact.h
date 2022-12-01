#include "contact.h"

class GestionContact{
    private:
        std::list<Contact> lc;//!< liste de contact
        struct sdate dateModification;//!< date de modification, se met a jour avec un(e) ajout / suppression / modification
    public:
        GestionContact();
        GestionContact(std::list<Contact>);
        GestionContact(std::list<Contact>, sdate);
        GestionContact(const GestionContact&);
        ~GestionContact();

        std::list<Contact> getLc();
        void setLc(std::list<Contact>);
        sdate getDateModification();
        void setDateModification(sdate);
        void updateModification();
        void ajouteContact(Contact);
        void retireContact(Contact);
        void retireContact(int);
        Contact * getContact(int);
        int taille();
        friend std::ostream& operator<<(std::ostream&, const GestionContact&);
        GestionContact operator+=(const Contact&);
        GestionContact operator-=(const Contact&);

};
