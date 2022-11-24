#ifndef sdate_h
#define sdate_h
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
};
#endif /* sdate_h */