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
		Tache(std::string desc);
		Tache(std::string desc, sdate date);
		Tache(const Tache& tache);
		~Tache();
		std::string getDesc();
		sdate getDate();
		void setDesc(std::string desc);
		void setDate(sdate date);
		friend std::ostream& operator<<(std::ostream& os, const Tache& tache);
		bool operator==(const Tache& tache);
};
