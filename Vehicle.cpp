#include "Vehicle.h"

using namespace Vehicles;
using namespace ParkingLotUtils;
using namespace Fees;

Vehicle::Vehicle(Time arrival_time, VehicleType type, LicensePlate plate, const ParkingSpot spot){
    this->arrival_time=arrival_time;
    this->type=type;
    this->plate=plate;
    this->spot=spot;
    debt=0;
    fined = false;
}

void Vehicle::addDebt(Time departure) {
    debt+=calculateDebt(departure);
}
void Vehicle::giveTicket() {
    debt+=FINE;
}
int Vehicle::calculateDebt(Time departure_time) const {
    Time duration = (departure_time-arrival_time).toHours();
    Time hour(1, 0, 0);
    if(type == HANDICAPPED){
        return HANDICAP_FEE;
    }
    if(type == MOTORBIKE){
        return MOTORBIKE_FEE_FIRST+(duration-hour)*MOTORBIKE_FEE;
    }
    if(type == CAR){
        return CAR_FEE_FIRST+(duration-hour)*CAR_FEE;
    }

    throw // TODO

}

LicensePlate Vehicle::getPlates() const {
    return plate;
}
ParkingSpot& Vehicle::getSpot() const {
    return spot;
}

void Vehicle::inspection(ParkingLotUtils::Time inspection_time) {
    Time duration = inspection_time-arrival_time;
    int day(24);
    if(duration.toHours()>day&&!fined){
        this->giveTicket();
        fined = true;
    }
}
ParkingSpot& Vehicle::getType() const {
    return type;
}

int Vehicle::getDebt() const {
    return debt;
}

Time Vehicle::getTime() const {
    return arrival_time;
}


