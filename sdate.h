#ifndef sdate_h
#define sdate_h
struct sdate{
    unsigned int jour;
    unsigned int mois;
    unsigned int annee;

    inline bool operator==(sdate d){
        return  jour==d.jour &&
                mois==d.mois &&
                annee==d.annee;
    }
};
#endif /* sdate_h */