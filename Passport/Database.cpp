# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
Database::Database() : stateParkList{}, camperList{} {

}

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	// TODO: implement function
	StatePark* park = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(park);

	return;
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function
	Passport* pass = new Passport(camperName, isJuniorPassport);
	camperList.push_back(pass);

	return;
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)
	bool inCampList = false;
	bool inParkList = false;
	int index = 0;
	int indexname = 0;
	
	// TODO: implement function
	for (long unsigned i = 0; i < camperList.size(); ++i) {
		if ((camperList.at(i)->getCamperName()) == camperName) {
			inCampList = true;
			indexname = i;
			break;
		}
	}

	for (long unsigned i = 0; i < stateParkList.size(); ++i) {
		if ((stateParkList.at(i)->getParkName()) == parkName) {
			inParkList = true;
			index = i;
			break;
		}
	}
	
	if (inCampList && inParkList) {
		camperList.at(indexname)->addParkVisited(stateParkList.at(index));
	}
	
	return;
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
