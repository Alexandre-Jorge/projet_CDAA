#include "gestionlienintertache.h"

///@brief constructeur par defaut
GestionLienIntertache::GestionLienIntertache(){
    this->lit = std::list<LienInterTache>();
}
/// @brief constructeur avec paramètre
/// @param std::list<LienInterTache> lit
GestionLienIntertache::GestionLienIntertache(std::list<LienInterTache> lit){
    this->lit = lit;
    this->lit.sort();
}
/// @brief constructeur par clonage
/// @param const GestionLienIntertache& glit
GestionLienIntertache::GestionLienIntertache(const GestionLienIntertache& glit){
    this->lit = glit.lit;
    this->lit.sort();
}
/// @brief destructeur
GestionLienIntertache::~GestionLienIntertache(){
}
/// @brief renvoie la liste de LienInterTache
/// @return std::list<LienInterTache>
std::list<LienInterTache> GestionLienIntertache::getLit(){
    return this->lit;
}
/// @brief modifie la liste de LienInterTache
/// @param std::list<LienInterTache> lit
void GestionLienIntertache::setLit(std::list<LienInterTache> lit){
    this->lit = lit;
    this->lit.sort();
}

/// @brief Ajoute le LienInterTache passé en paramètre
/// @param LienInterTache lit
void GestionLienIntertache::ajouteLien(LienInterTache lit){
    this->lit.push_back(lit);
    this->lit.sort();
}

/// @brief Retire le LienInterTache passé en paramètre
/// @param LienInterTache lit
void GestionLienIntertache::retireLien(LienInterTache lit){
    this->lit.remove(lit);
}

/// @brief Retire le LienInterTache associé à l'interaction i
/// @param Interaction* i
void GestionLienIntertache::retireLien(Interaction* i){
    for (unsigned long j=0;j<lit.size();j++){
        if(this->getLien(j).getI() == i){
            this->retireLien(this->getLien(j));
        }
    }
}
///@brief Retire le LienInterTache d'indice i
/// @param int i
void GestionLienIntertache::retireLien(int i){
    this->retireLien(this->getLien(i));
}

/// @brief Renvoie le LienInterTache à l'indice i
/// @param int i
/// @return LienInterTache
LienInterTache GestionLienIntertache::getLien(int i){
	int j=0;
	for (std::list<LienInterTache>::iterator it = this->lit.begin(); it != this->lit.end(); ++it){
        if (i==j){
            return *it;
        }
		j++;
    }
	return LienInterTache();//todo throws execption
}


/** @brief  Permet la création d'un lien liant l'interaction passée en paramètre ainsi que la tache
 *          associée.
 *          Détection automatique du contenu de l'interaction pour créer la tache équivalente.

 @param Interaction* i
*/
void GestionLienIntertache::creeLien(Interaction* i){
    //Crée un lien entre une interaction et une tache
    LienInterTache lien = LienInterTache(i, nullptr);
	//Detecte si le contenu de l'interaction contient une tache
	std::string ex = "@todo";
	std::string ss = i->getContenu().substr(0,5);
	if (ss.compare(ex)==0){
		//Detecte si la tache contient une date
		ex = "@date";
        unsigned long n = i->getContenu().rfind(ex);
		if (n==i->getContenu().npos){
			//Si @date n'existe pas
			lien.setT(new Tache(i->getContenu().substr(6,i->getContenu().size()-6)));//contenu de la tache sans le @todo
		}
		else{
			//Si @date existe convertit le texte "jj/mm/aaaa" en 3 unsigned int utilisé pour créé la date
            unsigned int j = std::stoi(i->getContenu().substr(n+6,2),nullptr,10);
            unsigned int m = std::stoi(i->getContenu().substr(n+9,2),nullptr,10);
            unsigned int a = std::stoi(i->getContenu().substr(n+12,4),nullptr,10);
			lien.setT(new Tache(i->getContenu().substr(6,n-6),{j,m,a}));//contenu de la tache sans le @todo et @date + date
		}
	}
	else{
        //Aucune tache détectée, donc l'interaction est lié à un pointeur nul
        lien.setT(nullptr);
    }
	this->ajouteLien(lien);
    this->lit.sort();
}
///@brief renvoie le nombre de LienInterTache dans la liste
/// @return int
int GestionLienIntertache::taille(){
    return this->lit.size();
}
///@brief surcharge operateur << : affichage en console de GestionLienIntertache
/// @param std::ostream& os, const GestionLienIntertache& glit
/// @return std::ostream&
std::ostream& operator<<(std::ostream& os, const GestionLienIntertache& glit){
    for (std::list<LienInterTache>::const_iterator it = glit.lit.begin(); it != glit.lit.end(); ++it){
        os << *it << std::endl;
    }
    return os;
}

/// @brief surcharge oprateur += : ajoute un LienInterTache
/// @param const LienInterTache& lientache
/// @return GestionLienInterTache
GestionLienIntertache GestionLienIntertache::operator+=(const LienInterTache& lientache){
    this->ajouteLien(lientache);
    return *this;
}

/// @brief surcharge operateur -= : retire un LienInterTache
/// @param const LienInterTache& lientache
/// @return GestionLienIntertache
GestionLienIntertache GestionLienIntertache::operator-=(const LienInterTache& lientache){
    this->retireLien(lientache);
    return *this;
}
/// @brief surcharge operateur = : affecte la GestionLienInterTache en paramètre a this
/// @param const GestionLienIntertache& glit
/// @return GestionLienIntertache
GestionLienIntertache GestionLienIntertache::operator=(const GestionLienIntertache& glit){
    return glit;
}




