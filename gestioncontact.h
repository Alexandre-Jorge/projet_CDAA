#include "contact.h"

class GestionContact{
    private:
        std::list<Contact> lc;
    public:
        GestionContact();
        ~GestionContact();
        GestionContact(std::list<Contact> lc);

        std::list<Contact> getLc();
        void setLc(std::list<Contact> lc);
}