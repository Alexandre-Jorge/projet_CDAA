#include "interaction.h"
#include "tache.h"
#include <list>

class LienInterTache{
	private:
		Interaction* i;
		Tache* t;
	public:
		LienInterTache();
		LienInterTache(Interaction* i, Tache* t);
		LienInterTache(const LienInterTache& lit);
		~LienInterTache();
		Interaction* getI();
		Tache* getT();
		void setI(Interaction* i);
		void setT(Tache* t);
		friend std::ostream& operator<<(std::ostream& os, const LienInterTache& lientache);
		bool operator==(const LienInterTache& lientache);
};
