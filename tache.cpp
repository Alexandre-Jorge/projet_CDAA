#include "tache.h"

Tache::Tache(std::string desc){
	this->desc=desc;
	this->date="";
}

Tache::Tache(std::string desc, std::string date){
	this->desc=desc;
	this->date=date;
}

Tache::~Tache(){
}
