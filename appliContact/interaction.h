#ifndef interaction_h
#define interaction_h
#include <iostream>
#include "sdate.h"
class Interaction{
    private:
        std::string contenu;//!< contenu de l'interaction (texte)
        sdate dateInteract;//!< date de l'interaction, peut etre préciser avec @date
    public:
        Interaction();
        Interaction(const std::string);
        Interaction(const std::string, const sdate);
        Interaction(const Interaction&);
        ~Interaction();
        std::string getContenu();
        sdate getDateInteract();
        void setContenu(std::string);
        void setDateInteract(sdate);
        friend std::ostream& operator<<(std::ostream&, const Interaction&);
        bool operator==(const Interaction&);
};
#endif /* interaction_h */
