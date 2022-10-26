#include "tache.h"

Tache::Tache(){
	this->desc = "";
	this->date = {0,0,0};
}
Tache::Tache(std::string desc){
	this->desc=desc;
	this->date={0,0,0};
}

Tache::Tache(std::string desc, sdate date){
	this->desc=desc;
	this->date=date;
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

sdate Tache::strTodate(std::string date){
	sdate d;
	d.jour = date.substr(0,2);
	d.mois = std::stoi(date.substr(3,2));
	d.annee = std::stoi(date.substr(6,4));
	return d;
}
