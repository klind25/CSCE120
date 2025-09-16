# include "Passport.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
Passport::Passport(string name, bool jr) : camperName(name), isJuniorPassport(jr), parksVisited{} {
	
}

string Passport::getCamperName() {
	// TODO: implement getter

	return camperName;
}

bool Passport::checkJuniorPassport() {
	// TODO: implement getter

	return isJuniorPassport;
}

void Passport::addParkVisited(StatePark* park) {
	INFO(park)

	// TODO: implement function
	parksVisited.push_back(park);
	park->addCamper(this);

	return;
}

double Passport::getMilesHiked() {
	// TODO: (optional) implement function

	return 0.0;
}

int Passport::getHikerLevel() {
	// TODO: (optional) implement function

	return 0;
}
