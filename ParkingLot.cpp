#include "ParkingLot.h"
#include "ParkingLotPrinter.cpp"
#include "Vehicle.h"
#include <map>

using namespace ParkingLotUtils;
using namespace MtmParkingLot;
using namespace Fees;
using namespace Vehicles;
using std::cout;
using std::ostream;

class TypeFreeSpots : public <ParkingSpot>UniqueArray::Filter{
        public:
        virtual bool operator() (const ParkingSpot& spot) const override{
            return spot.getParkingBlock()==type;
        }
};

/**
 * @brief returns the total number of parking spots in the block sizes array
 *
 * @param parkingBlockSizes bloc sizes array
 * @return int total number
 */

int numberOfSpots(unsigned int* parkingBlockSizes){
    sum=0
    for(int i=0;i<3;i++){
        sum+=parkingBlockSizes[i];
    }
    return sum;
}

ParkingLot::ParkingLot(unsigned int *parkingBlockSizes):
motorbikes(new UniqueArray<LicensePlate>(parkingBlockSizes[MOTORBIKE])),
handicaps(new UniqueArray<LicensePlate>(parkingBlockSizes[HANDICAPPED])),
cars(new UniqueArray<LicensePlate>(parkingBlockSizes[CAR])),
plates_to_vehicles(new map<LicensePlate, Vehicle>),
spots_to_vehicles(new map<int, Vehicle>){
    size = numberOfSpots(parkingBlockSizes);
}

ParkingLot::~ParkingLot() {
    delete motorbikes;
    delete handicaps;
    delete cars;
    delete plates_to_vehicles;
    delete spots_to_vehicles;
}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
    UniqueArray<LicensePlate> current_type = uniqueArrayByType(vehicleType);
    if(!current_type[licensePlate]){
        ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate, entranceTime);
        ParkingSpot curr_spot = plates_to_vehicles[licensePlate].getSpot;
        ParkingLotPrinter::printEntryFailureAlreadyParked(cout, curr_spot);
        return VEHICLE_ALREADY_PARKED;
    }
    if(current_type.getCount() == current_type.getSize()){
        ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate, entranceTime);
        ParkingLotPrinter::printEntryFailureNoSpot(cout);
        return NO_EMPTY_SPOT;
    }
    current_type.insert(LicensePlate);
    int index = current_type.getIndex(LicensePlate, index);
    ParkingSpot new_spot = findSpot(vehicleType, current_type);
    Vehicle vehicle = new Vehicle(vehicleType, licensePlate, entranceTime, new_spot);
    plates_to_vehicles[LicensePlate] = vehicle;
    spots_to_vehicles[new_spot.getParkingNumber()] = vehicle;
    return SUCCESS;
}
void ParkingLot::inspectParkingLot(ParkingLotUtils::Time inspectionTime) {
    map<int, Vehicle>::iterator it;
    for ( it = spots_to_vehicles.begin(); it != spots_to_vehicles.end(); it++ ){
        it->second.inspection(inspectionTime);
    }
}

ParkingResult ParkingLot::getParkingSpot(ParkingLotUtils::LicensePlate licensePlate,
                                         ParkingLotUtils::ParkingSpot &parkingSpot) const {
    Vehicle& curr_vehicle = plates_to_vehicles[licensePlate];
    if(!curr_vehicle){
        return VEHICLE_NOT_FOUND
    }
    parkingSpot = curr_vehicle.getSpot();
    return SUCCESS;
}

ParkingResult ParkingLot::exitParking(ParkingLotUtils::LicensePlate licensePlate, ParkingLotUtils::Time exitTime) {
    if(!(motorbikes[licensePlate] || handicaps[licensePlate] || cars[licensePlate])){
        ParkingLotPrinter::printExitFailure(cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }
    Vehicle& exiting_vehicle = plates_to_vehicles[licensePlate];
    UniqueArray<LicensePlate> current_type = uniqueArrayByType(exiting_vehicle.getType());
    current_type.remove(LicensePlate);
    plates_to_vehicles.erase(LicensePlate);
    spots_to_vehicles.erase(exiting_vehicle.getSpot().getParkingNumber());
    exiting_vehicle.addDebt(exitTime);
    ParkingLotPrinter::printVehicle(cout, exiting_vehicle.getType(), licensePlate, exiting_vehicle.getTime());
    ParkingLotPrinter::printExitSuccess(cout, exitTime, exiting_vehicle.getDebt());
    delete exiting_vehicle;
    return SUCCESS;
}

ostream & ParkingLot::operator<<(ostream &os, const MtmParkingLot::ParkingLot &parkingLot) {
    ParkingLotPrinter::printParkingLotTitle(cout);
    map<int, Vehicle>::iterator it;
    for ( it = spots_to_vehicles.begin(); it != spots_to_vehicles.end(); it++ ){
        Vehicle vehicle = it->second;
        ParkingLotPrinter::printVehicle(os, vehicle.getPlates(), vehicle.getType(), vehicle.getTime());
        ParkingLotPrinter::printParkingSpot(os, spot);
    }
    return os;
}

UniqueArray<LicensePlate> & ParkingLot::uniqueArrayByType(ParkingLotUtils::VehicleType type) const {
    switch (type){
        case (MOTORBIKE):
            return motorbikes;
        case (HANDICAPPED):
            return handicaps;
        case (CAR):
            return cars;
    }
}

ParkingSpot ParkingLot::findSpot(ParkingLotUtils::VehicleType type, int index) {
    int factor = int(type);
    factor *= size;
    ParkingSpot spot = new ParkingSpot(type, index+factor);
    return spot;

}