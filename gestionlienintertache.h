#include "lienintertache.h"
#include <iostream>
#include <list>
class GestionLienIntertache{
    private:
        std::list<LienInterTache> lit;
    public:
        GestionLienIntertache();
        GestionLienIntertache(std::list<LienInterTache> lit);
        GestionLienIntertache(const GestionLienIntertache& glit);
        ~GestionLienIntertache();
        std::list<LienInterTache> getLit();
        void setLit(std::list<LienInterTache> lit);
        void ajouteLien(LienInterTache lit);
        void retireLien(LienInterTache lit);
        void retireLien(Interaction* i);
        void retireLien(int i);
        LienInterTache getLien(int i);
        void creeLien(Interaction* i);
        friend std::ostream& operator<<(std::ostream& os, const GestionLienIntertache& glit);
        GestionLienIntertache operator+=(const LienInterTache& lientache);
        GestionLienIntertache operator-=(const LienInterTache& lientache);
};