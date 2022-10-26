#include "lienintertache.h"

LienInterTache::LienInterTache(){
	this->li = std::list<Interaction>();
	this->lt = std::list<Tache>();
}

LienInterTache::LienInterTache(std::list<Interaction> li, std::list<Tache> lt){
	this->li = li;
	this->lt = lt;
}

LienInterTache::LienInterTache(const LienInterTache& lit){
	this->li = lit.li;
	this->lt = lit.lt;
}

LienInterTache::~LienInterTache(){
}


void LienInterTache::ajouteElt(Interaction i){
	//Ajoute une interaction et sa tache liée aux listes
	this->li.push_back(i);
	//Detecte si le contenu de l'interaction contient une tache
	std::string ex = "@todo";
	std::string ss = i.getContenu().substr(0,5);
	if (ss.compare(ex)==0){
		//Detecte si la tache contient une date
		ex = "@date";
		int n = i.getContenu().rfind(ex);
		if (n==i.getContenu().npos){
			//Si @date n'existe pas
			this->lt.push_back(Tache(i.getContenu()));
		}
		else{
			//Si @date existe
			this->lt.push_back(Tache(i.getContenu(),i.getDateInteract()));
		}			
	}
	else{
		//Aucune tache détectée, donc l'interaction est lié à une tache vide
		this->lt.push_back(Tache());
	}
}

