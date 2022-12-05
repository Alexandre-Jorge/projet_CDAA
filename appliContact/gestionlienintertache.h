#include "lienintertache.h"
#include <iostream>
#include <list>
class GestionLienIntertache{
    private:
        std::list<LienInterTache> lit;//!< liste de LienInterTache
    public:
        GestionLienIntertache();
        GestionLienIntertache(std::list<LienInterTache>);
        GestionLienIntertache(const GestionLienIntertache&);
        ~GestionLienIntertache();
        std::list<LienInterTache> getLit();
        void setLit(std::list<LienInterTache>);
        void ajouteLien(LienInterTache);
        void retireLien(LienInterTache);
        void retireLien(Interaction*);
        void retireLien(int);
        LienInterTache getLien(int);
        void creeLien(Interaction*);
        int taille();
        friend std::ostream& operator<<(std::ostream&, const GestionLienIntertache&);
        GestionLienIntertache operator+=(const LienInterTache&);
        GestionLienIntertache operator-=(const LienInterTache&);
};
