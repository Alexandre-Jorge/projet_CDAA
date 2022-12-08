#include "lienintertache.h"
/// @brief constructeur par defaut
LienInterTache::LienInterTache(){
	this->i = nullptr;
	this->t = nullptr;
}
/// @brief constructeur avec paramètre
/// @param Interaction* i, Tache* t
LienInterTache::LienInterTache(Interaction* i, Tache* t){
	this->i = i;
	this->t = t;
}
/// @brief constructeur par clonage
/// @param const LienInterTache& lit
LienInterTache::LienInterTache(const LienInterTache& lit){
	this->i = lit.i;
	this->t = lit.t;
}
/// @brief destructeur
LienInterTache::~LienInterTache(){
}
/// @brief renvoie l'interaction du LienInterTache
/// @return Interaction *
Interaction * LienInterTache::getI(){
	return this->i;
}
/// @brief renvoie la tache du LienInterTache
/// @return Tache *
Tache * LienInterTache::getT(){
	return this->t;
}
/// @brief modifie l'interaction du LienInterTache
/// @param Interaction* i
void LienInterTache::setI(Interaction * i){
	this->i = i;
}
/// @brief modifie la tache du LienInterTache
/// @param tache * i
void LienInterTache::setT(Tache * t){
	this->t = t;
}
/// @brief Surcharge operateur << : affichage d'un LienInterTache en console
/// @param std::ostream& os, const LienInterTache& lientache
/// @return std::ostream&
std::ostream& operator<<(std::ostream& os, const LienInterTache& lientache){
	os << "LienInterTache : " << std::endl;
	os << "Interaction : " << std::endl;
	os << *lientache.i << std::endl;
	os << "Tache : " << std::endl;
	os << *lientache.t << std::endl;
	return os;
}

/// @brief surcharge operateur == : verifie si 2 LienInterTache sont égaux
/// @param const LienInterTache& lientache
/// @return bool
bool LienInterTache::operator==(const LienInterTache& lientache){
	return (this->i == lientache.i && this->t == lientache.t);
}
/// @brief surcharge operateur < : verifie si this est inferieur au lien en paramètre (compare les dates)
/// @param const LienInterTache& lientache
/// @return bool
bool LienInterTache::operator<(const LienInterTache& lientache){
    if(lientache.t!=nullptr && this->getT()!=nullptr)
        if(this->getT()->getDate() < lientache.t->getDate())
            return true;
    return false;
}
/// @brief surcharge operateur > : verifie si this est superieur au lien en paramètre (compare les dates)
/// @param const LienInterTache& lientache
/// @return bool
bool LienInterTache::operator>(const LienInterTache& lientache){
    if(lientache.t!=nullptr && this->getT()!=nullptr)
        if(this->getT()->getDate() > lientache.t->getDate())
            return true;
    return false;
}
