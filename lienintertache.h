#include "interaction.h"

class LienInterTache{
	private:
		std::list<Interaction> li;
		std::list<Tache> lt;
	public:
		LienInterTache();
		~LienInterTache();		
		void ajouteElt(Interaction i);
};
