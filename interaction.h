#include <iostream>

class Interaction{
    private:
        Date dateInteract;
        std::string contenu;
    public:
        Interaction();
        Interaction(const Date dateInteract,const std::string contenu);
        ~Interaction();
        Date getDateInteract();
        std::string getContenu();
        void setDateInteract(Date dateInteract);
        void setContenu(std::string contenu);
        friend std::ostream& operator<<(std::ostream& os, const Interaction& interaction);
}