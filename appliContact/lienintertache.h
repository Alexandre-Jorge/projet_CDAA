#include "interaction.h"
#include "tache.h"
#include <list>

/// @class LienInterTache
/// @brief classe liant une Interaction a une Tache
class LienInterTache{
	private:
		Interaction* i; //!<Pointeur d'une interaction
		Tache* t; //!<Pointeur d'une tache
	public:
		LienInterTache();
        LienInterTache(Interaction*, Tache*);
        LienInterTache(const LienInterTache&);
		~LienInterTache();
		Interaction* getI();
		Tache* getT();
        void setI(Interaction*);
        void setT(Tache*);
        friend std::ostream& operator<<(std::ostream&, const LienInterTache&);
        bool operator==(const LienInterTache&);
        bool operator<(const LienInterTache&);
        bool operator>(const LienInterTache&);
};
