#include "lienintertache.h"

LienInterTache::LienInterTache(){
	this->i = nullptr;
	this->t = nullptr;
}

LienInterTache::LienInterTache(Interaction* i, Tache* t){
	this->i = i;
	this->t = t;
}

LienInterTache::LienInterTache(const LienInterTache& lit){
	this->i = lit.i;
	this->t = lit.t;
}

LienInterTache::~LienInterTache(){
	/*delete this->i;
	delete this->t;*/
}

Interaction* LienInterTache::getI(){
	return this->i;
}

Tache* LienInterTache::getT(){
	return this->t;
}

void LienInterTache::setI(Interaction* i){
	this->i = i;
}

void LienInterTache::setT(Tache* t){
	this->t = t;
}

std::ostream& operator<<(std::ostream& os, const LienInterTache& lientache){
	os << "LienInterTache : " << std::endl;
	os << "Interaction : " << std::endl;
	os << *lientache.i << std::endl;
	os << "Tache : " << std::endl;
	os << *lientache.t << std::endl;
	return os;
}

bool LienInterTache::operator==(const LienInterTache& lientache){
	return (this->i == lientache.i && this->t == lientache.t);
}
