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
    if(type==HANDICAPPED){
        return HANDICAP_FEE;
    }
    if(type==MOTORBIKE){
        return MOTORBIKE_FEE_FIRST+(duration-HOUR)*MOTORBIKE_FEE;
    }
    if(type==CAR){
        return CAR_FEE_FIRST+(duration-HOUR)*CAR_FEE;
    }

    throw // TODO

}

LicensePlate Vehicle::getPlates() {
    return plate;
}
ParkingSpot& Vehicle::getSpot() const {
    return spot;
}

bool Vehicle::operator==(ParkingLotUtils::LicensePlate plate) {
    return this->plate==plate;
}

bool Vehicle::operator==(const Vehicle &vehicle) const {
    return this->plate==vehicle.plate;
}


