#include "tache.h"

/// @brief constructeur par defaut
Tache::Tache(){
	this->desc = "";
	this->date = {0,0,0};
}
/// @brief constructeur avec parametre
/// @param std::string desc
Tache::Tache(std::string desc){
	this->desc=desc;
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->date = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}
/// @brief constructeur avec parametre
/// @param std::string desc, sdate date
Tache::Tache(std::string desc, sdate date){
	this->desc=desc;
	this->date=date;
}
/// @brief construteur par clonage
/// @param const Tache& t
Tache::Tache(const Tache& t){
	this->desc=t.desc;
	this->date=t.date;
}
/// @brief destructeur
Tache::~Tache(){
}
/// @brief renvoie la description de la tache
/// @return std::string
std::string Tache::getDesc(){
	return this->desc;
}
/// @brief renvoie la date de la tache
/// @return sdate
sdate Tache::getDate(){
	return this->date;
}
/// @brief modifie la description de la tache
/// @param std::string desc
void Tache::setDesc(std::string desc){
	this->desc=desc;
}
/// @brief modifie la date de la tache
/// @param sdate date
void Tache::setDate(sdate date){
	this->date=date;
}
/// @brief Surcharge operateur << : affichage d'une tache en console
/// @param std::ostream& os, const Tache& tache
/// @return std::ostream&
std::ostream& operator<<(std::ostream& os, const Tache& tache){
	os << "Description de la tache : " << tache.desc << std::endl;
    os << "Date de la tache : " << tache.date << std::endl;
	return os;
}

/// @brief surcharge operateur == : verifie si 2 tache sont égales
/// @param const Tache& t
/// @return bool
bool Tache::operator==(const Tache& t){
	return this->desc==t.desc && this->date==t.date;
}
