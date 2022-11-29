#include "tache.h"

Tache::Tache(){
	this->desc = "";
	this->date = {0,0,0};
}
Tache::Tache(std::string desc){
	this->desc=desc;
	time_t t = time(0);//nb sec depuis 1970
    tm * ltm = localtime(&t);//conversion
    this->date = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
}

Tache::Tache(std::string desc, sdate date){
	this->desc=desc;
	this->date=date;
}

Tache::Tache(const Tache& t){
	this->desc=t.desc;
	this->date=t.date;
}

Tache::~Tache(){
}

std::string Tache::getDesc(){
	return this->desc;
}

sdate Tache::getDate(){
	return this->date;
}

void Tache::setDesc(std::string desc){
	this->desc=desc;
}

void Tache::setDate(sdate date){
	this->date=date;
}

std::ostream& operator<<(std::ostream& os, const Tache& tache){
	os << "Description de la tache : " << tache.desc << std::endl;
	os << "Date de la tache : " << tache.date.jour << "/" << tache.date.mois << "/" << tache.date.annee << std::endl;
	return os;
}

/// @brief Compare deux taches si elles sont identiques ou non.
/// @param t Tache&
/// @return bool
bool Tache::operator==(const Tache& t){
	return this->desc==t.desc && this->date==t.date;
}