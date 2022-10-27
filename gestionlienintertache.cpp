#include "gestionlienintertache.h"

GestionLienIntertache::GestionLienIntertache(){
    this->lit = std::list<LienInterTache>();
}

GestionLienIntertache::GestionLienIntertache(std::list<LienInterTache> lit){
    this->lit = lit;
}

GestionLienIntertache::GestionLienIntertache(const GestionLienIntertache& glit){
    this->lit = glit.lit;
}

GestionLienIntertache::~GestionLienIntertache(){
}

std::list<LienInterTache> GestionLienIntertache::getLit(){
    return this->lit;
}

void GestionLienIntertache::setLit(std::list<LienInterTache> lit){
    this->lit = lit;
}

void GestionLienIntertache::ajouteLien(LienInterTache lit){
    this->lit.push_back(lit);
}

void GestionLienIntertache::retireLien(LienInterTache lit){
    this->lit.remove(lit);
}

void GestionLienIntertache::retireLien(int i){
    this->retireLien(this->getLien(i));
}

LienInterTache GestionLienIntertache::getLien(int i){
    //Renvoie le lien à l'indice i de la liste
	int j=0;
	for (std::list<LienInterTache>::iterator it = this->lit.begin(); it != this->lit.end(); ++it){
        if (i==j){
            return *it;
        }
		j++;
    }
	return LienInterTache();//todo throws execption
}

void GestionLienIntertache::creeLien(Interaction* i){
    //Crée un lien entre une interaction et une tache
    //todo
    LienInterTache lien = LienInterTache(i, nullptr);
	//Detecte si le contenu de l'interaction contient une tache
	std::string ex = "@todo";
	std::string ss = i->getContenu().substr(0,5);
	if (ss.compare(ex)==0){
		//Detecte si la tache contient une date
		ex = "@date";
		int n = i->getContenu().rfind(ex);
		if (n==i->getContenu().npos){
			//Si @date n'existe pas
			lien.setT(new Tache(i->getContenu()));
		}
		else{
			//Si @date existe
			lien.setT(new Tache(i->getContenu(),i->getDateInteract()));
		}		
	}
	else{
		//Aucune tache détectée, donc l'interaction est lié à une tache vide
		lien.setT(new Tache());
    }
	this->lit.push_back(lien);
}

std::ostream& operator<<(std::ostream& os, const GestionLienIntertache& glit){
    for (std::list<LienInterTache>::const_iterator it = glit.lit.begin(); it != glit.lit.end(); ++it){
        os << *it << std::endl;
    }
    return os;
}

GestionLienIntertache GestionLienIntertache::operator+=(const LienInterTache& lientache){
    this->ajouteLien(lientache);
    return *this;
}

GestionLienIntertache GestionLienIntertache::operator-=(const LienInterTache& lientache){
    this->retireLien(lientache);
    return *this;
}




