#include "ParkingLot.h"
#include "ParkingLotPrinter.cpp"

using namespace ParkingLotUtils;
using namespace MtmParkingLot;
using namespace Fees;
Vehicle::VehicleType (Time arrival_time, VehicleType type, LicensePlate plate, const ParkingSpot spot){
    this.arrival_time=arrival_time;
    this.type=type;
    this.LicensePlate=plate;
    this.spot=spot;
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
    throw /*TODO*/
}

int numberOfSpots(unsigned int* parkingBlockSizes){
    sum=0
    for(int i=0;i<3;i++){
        sum+=parkingBlockSizes[i];
    }
    return sum;
}

ParkingLot::ParkingLot(unsigned int *parkingBlockSizes) {
    size=numberOfSpots(parkingBlockSizes);
    UniqueArray vehicles=new UniqueArray(size);
    UniqueArray free_spots=new UniqueArray(size);
    UniqueArray taken_spots=new UniqueArray(size);
}

ParkingLot::~ParkingLot() {
    delete vehicles;
    delete free_spots;
    delete taken_spots;
}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
    if(vehicleIsIn(licensePlate)){
        ParkingLotPrinter::printVehicle(cout, )
        ParkingLotPrinter::printEntryFailureAlreadyParked()
    }
}

Vehicle& ParkingLot::getVehicleByPlates(ParkingLotUtils::LicensePlate license_plate) {
    for (int i=0;i<size;i++){
        if(vehicles[i].)
    }
}

