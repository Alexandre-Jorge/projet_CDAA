#include "sdate.h"
#include <iostream>

class Tache{
	private:
		std::string desc;
		struct sdate date;
	public:
		Tache();
		Tache(std::string desc);
		Tache(std::string desc, sdate date);
		~Tache();
		std::string getDesc();
		sdate getDate();
		void setDesc(std::string desc);
		void setDate(sdate date);
		sdate strTodate(std::string date);
		friend std::ostream& operator<<(std::ostream& os, const Tache& tache);
};
