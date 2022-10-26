#include "interaction.h"
#include "tache.h"
#include <list>

class LienInterTache{
	private:
		std::list<Interaction> li;
		std::list<Tache> lt;
	public:
		LienInterTache();
		LienInterTache(std::list<Interaction> li, std::list<Tache> lt);
		LienInterTache(const LienInterTache& lit);
		~LienInterTache();
		std::list<Interaction> getLi();
		std::list<Tache> getLt();
		friend std::ostream& operator<<(std::ostream& os, const LienInterTache& lientache);
		void ajouteElt(Interaction i);
};
