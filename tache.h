#include <iostream>
#include <ctime>
#include <chrono>
#include "sdate.h"

class Tache{
	private:
		std::string desc;
		struct sdate date;
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
};
