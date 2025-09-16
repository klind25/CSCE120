# include "Passport.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
StatePark::StatePark(string name, double fee, double miles) : parkName(name), entranceFee(fee), trailMiles(miles), camperLog{} {
}

string StatePark::getParkName() {
	// TODO: implement getter
	return parkName;
}

double StatePark::getEntranceFee() {
	// TODO: implement getter

	return entranceFee;
}

double StatePark::getTrailMiles() {
	// TODO: implement getter
	
	return trailMiles;
}

void StatePark::addCamper(Passport* camper) {
	INFO(camper)

	// TODO: implement function
	camperLog.push_back(camper);

	return;
}

double StatePark::getRevenue() {
	// TODO: (optional) implement function

	return 0.0;
}
