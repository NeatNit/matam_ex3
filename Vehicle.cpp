#include "Vehicle.h"

using namespace Vehicles;
using namespace ParkingLotUtils;

Vehicle::VehicleType (Time arrival_time, VehicleType type, LicensePlate plate, const ParkingSpot spot){
    this->arrival_time=arrival_time;
    this->type=type;
    this->plate=plate;
    this->spot=spot;
    debt=0;
}

void Vehicle::addDebt(Time departure) {
    debt+=calculateDebt(arrival_time, type);
}
void Vehicle::giveTicket() {
    debt+=FINE;
}
int Vehicle::calculateDebt(Time departure_time, VehicleType type) const {
    Time duration=(departure_time-arrival_time).toHours();
    Time hour(1, 0, 0);
    if(type==HANDICAPPED){
        return HANDICAP_FEE;
    }
    if(type==MOTORBIKE){
        return MOTORBIKE_FEE_FIRST+(duration-hour)*MOTORBIKE_FEE;
    }
    if(type==CAR){
        return CAR_FEE_FIRST+(duration-hour)*CAR_FEE;
    }

    throw // TODO

}

LicensePlate Vehicle::getPlates() {
    return plate;
}
ParkingSpot& Vehicle::getSpot() const {
    return spot;
}

bool Vehicle::operator==(const ParkingLotUtils::LicensePlate plate) const {
    return this->plate==plate;
}

bool Vehicle::operator==(const Vehicle &vehicle) const {
    return this->plate==vehicle.plate;
}

void Vehicle::inspection(ParkingLotUtils::Time inspection_time) {
    Time duration = inspection_time-arrival_time;
    int day(24);
    if(duration.toHours()>day){
        this->giveTicket();
    }
}
ParkingSpot& Vehicle::getType() const {
    return type;
}

int Vehicle::getDebt() {
    return debt;
}

Time Vehicle::getTime() {
    return arrival_time;
}


