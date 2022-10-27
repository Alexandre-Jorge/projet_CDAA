#ifndef interaction_h
#define interaction_h
#include <iostream>
#include "sdate.h"
class Interaction{
    private:
        std::string contenu;
        sdate dateInteract;
    public:
        Interaction();
        Interaction(const std::string contenu);
        Interaction(const std::string contenu, const sdate dateInteract);
        Interaction(const Interaction& interaction);
        ~Interaction();
        std::string getContenu();
        sdate getDateInteract();
        void setContenu(std::string contenu);
        void setDateInteract(sdate dateInteract);
        friend std::ostream& operator<<(std::ostream& os, const Interaction& interaction);
        bool operator==(const Interaction& interaction);
};
#endif /* interaction_h */
