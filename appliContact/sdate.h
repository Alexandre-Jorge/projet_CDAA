#ifndef sdate_h
#define sdate_h
#include <iostream>
struct sdate{
    unsigned int jour; //!<Jour JJ
    unsigned int mois; //!<Mois MM
    unsigned int annee; //!<Année AAAA

    /// @brief Compare deux dates si elles sont identiques ou non.
    /// @param d sdate
    /// @return bool
    inline bool operator==(sdate d){
        return  jour==d.jour &&
                mois==d.mois &&
                annee==d.annee;
    }

    inline bool operator<(sdate d){
        if(annee < d.annee)
            return true;
        else if(annee == d.annee && mois < d.mois)
            return true;
        else if(annee == d.annee && mois == d.mois && jour < d.jour)
            return true;
        else
            return false;
    }

    inline bool operator>(sdate d){
        if(annee > d.annee)
            return true;
        else if(annee == d.annee && mois > d.mois)
            return true;
        else if(annee == d.annee && mois == d.mois && jour > d.jour)
            return true;
        else
            return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const sdate& d){
        os << d.jour << "/" << d.mois << "/" << d.annee << std::endl;
        return os;
    }

};
#endif /* sdate_h */
