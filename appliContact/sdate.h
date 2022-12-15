#ifndef sdate_h
#define sdate_h
#include <iostream>

/// @struct sdate
/// @brief structure representant une date
struct sdate{
    unsigned int jour; //!<Jour JJ
    unsigned int mois; //!<Mois MM
    unsigned int annee; //!<Année AAAA

    /// @brief surcharge operateur == : verifie si 2 sdate sont egales
    /// @param sdate d
    /// @return bool
    inline bool operator==(sdate d){
        return  jour==d.jour &&
                mois==d.mois &&
                annee==d.annee;
    }

    /// @brief surcharge operateur < : compare deux date pour voir si l'une est inferieur a l'autre
    /// @param sdate d
    /// @return bool
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

    /// @brief surcharge operateur > : compare deux date pour voir si l'une est superieur a l'autre
    /// @param sdate d
    /// @return bool
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

    /// @brief surcharge operateur << :  affichage d'une sdate en console
    /// @param sdate d
    /// @return bool
    friend std::ostream& operator<<(std::ostream& os, const sdate& d){
        if(d.jour<10) os << "0" << d.jour ;
        else os << d.jour ;
        if(d.mois<10) os << "/" << "0" << d.mois;
        else os << "/" << d.mois;
        os << "/" << d.annee << std::endl;
        return os;
    }

};
#endif /* sdate_h */
