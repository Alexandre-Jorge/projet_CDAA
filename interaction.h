#include <iostream>
#include "sdate.h"

class Interaction{
    private:
        sdate dateInteract;
        std::string contenu;
    public:
        Interaction();
        Interaction(const sdate dateInteract,const std::string contenu);
        ~Interaction();
        sdate getDateInteract();
        std::string getContenu();
        void setDateInteract(sdate dateInteract);
        void setContenu(std::string contenu);
        friend std::ostream& operator<<(std::ostream& os, const Interaction& interaction);
};
