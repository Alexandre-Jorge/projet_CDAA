#include "lienintertache.h"

LienInterTache::LienInterTache(){
	this->li = std::list<Interaction>();
	this->lt = std::list<Tache>();
}

LienInterTache::~LienInterTache(){
}


void LienInterTache::ajouteElt(Interaction i){
//Ajoute une interaction et sa tache liée à la liste
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
			//ss=i.getContenu().substr(n+5,i.getContenu().size()-n+5);
			this->lt.push_back(Tache(i.getContenu(),i.getDateInteract()));
		}			
	}
	else{
	//Aucune tache détectée, donc l'interaction est lié à un pointeur null
		this->lt.push_back(Tache());
	}
}

