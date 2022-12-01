#include <iostream>
#include <ctime>
#include <chrono>
#include "sdate.h"

class Tache{
	private:
		std::string desc; //!<Description de la tache
		struct sdate date; //!<Date à laquelle effectuer la tache
	public:
		Tache();
        Tache(std::string);
        Tache(std::string, sdate);
        Tache(const Tache&);
		~Tache();
		std::string getDesc();
		sdate getDate();
        void setDesc(std::string);
        void setDate(sdate);
        friend std::ostream& operator<<(std::ostream&, const Tache&);
        bool operator==(const Tache&);
};
