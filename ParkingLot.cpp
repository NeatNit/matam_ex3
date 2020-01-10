#include "ParkingLot.h"
#include "ParkingLotPrinter.cpp"
#include "Vehicle.h"

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

bool ParkingLot::isFull(UniqueArray vehicles, ParkingLotUtils::VehicleType type) {

}
void fillParkingSpotsArray(UniqueArray array, unsigned int* parkingBlockSizes){
    int handicap_num=parkingBlockSizes[HANDICAPPED], motorbike_num=parkingBlockSizes[MOTORBIKE],
    car_num=parkingBlockSizes[CAR];
    unsigned int curr_spot_num=0;
    VehicleType curr_type=FIRST;
    for (int i=0; i<handicap_num; i++, curr_spot_num++){
        if(curr_spot_num>motorbike_num&&curr_spot_num<=handicap_num){
            curr_type=HANDICAPPED;
        }
        if(curr_spot_num>handicap_num){
            curr_type=CAR;
        }
        ParkingSpot spot(curr_type, curr_spot_num);
        array.insert(spot);
    }
}

ParkingLot::ParkingLot(unsigned int *parkingBlockSizes) {
    size=numberOfSpots(parkingBlockSizes);
    Vehicle* vehicles[]=new Vehicle[size];
    UniqueArray<ParkingSpot> free_spots=new UniqueArray(size);
    UniqueArray<ParkingSpot> taken_spots=new UniqueArray(size);
    fillParkingSpotsArray(free_spots, parkingBlockSizes);
}

ParkingLot::~ParkingLot() {
    delete[] vehicles;
    delete free_spots;
    delete taken_spots;
}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
    if(vehicleIsIn(licensePlate)){
        Vehicle& vehicle=getVehicleByPlates(licensePlate);
        ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);
        ParkingLotPrinter::printEntryFailureAlreadyParked(cout, vehicle.getSpot());
        return VEHICLE_ALREADY_PARKED;
    }
    UniqueArray filtered = filterFreeSpots(vehicleType);
    if(filtered.getSize()==0){
        ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);
        ParkingLotPrinter::printEntryFailureNoSpot(cout);
        return NO_EMPTY_SPOT;
    }
    //TODO get spot from filtered, remove spot from free to taken
    Vehicle vehicle=new Vehicle(vehicleType, licensePlate, entranceTime, );
    changeSpotStatus(/***********************************/);
   // vehicles->insert(vehicle);
    return SUCCESS;

}

Vehicle& ParkingLot::getVehicleByPlates(ParkingLotUtils::LicensePlate license_plate) {
    for (int i=0;i<size;i++){
        if(*vehicles[i]==license_plate){
            return *vehicles[i];
        }
    }
    return NULL;
    throw //TODO
}
void ParkingLot::inspectParkingLot(ParkingLotUtils::Time inspectionTime) {
    for(int i=1; i<size; i++){
        vehicles[i]->giveTicket();
    }
}

UniqueArray& ParkingLot::filterFreeSpots(ParkingLotUtils::VehicleType type) {
    <ParkingSpot>UniqueArray filtered = free_spots.filter(TypeFreeSpots());
    return filtered;
}
void ParkingLot::changeSpotStatus(ParkingLotUtils::ParkingSpot spot) {
    if(free_spots[spot]){
        taken_spots.insert(spot);
        free_spots.remove(spot);
    } else{
        free_spots.insert(spot);
        taken_spots.remove(spot);
    }
}
ParkingResult ParkingLot::getParkingSpot(ParkingLotUtils::LicensePlate licensePlate,
                                         ParkingLotUtils::ParkingSpot &parkingSpot) const {
    Vehicle& curr_vehicle = getVehicleByPlates(licensePlate);
    if(!curr_vehicle){
        return VEHICLE_NOT_FOUND
    }
    parkingSpot = curr_vehicle.getSpot();
    return SUCCESS;
    /*
    for(int i=0; i<size; i++){
        if(*vehicles[i]==licensePlate){
            parkingSpot=vehicles[i]->getSpot();
            return SUCCESS;
        }
    }
    return VEHICLE_NOT_FOUND;
     */
}

ParkingResult ParkingLot::exitParking(ParkingLotUtils::LicensePlate licensePlate, ParkingLotUtils::Time exitTime) {
    if(!vehicleIsIn(licensePlate)){
        ParkingLotPrinter::printExitFailure(cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }

    Vehicle& exiting_vehicle = getVehicleByPlates(licensePlate);

    ParkingLotPrinter::printVehicle(cout, exiting_vehicle.getType(), licensePlate, exiting_vehicle.getTime());
    ParkingLotPrinter::printExitSuccess(cout, exitTime, exiting_vehicle.getDebt());

}

ostream & ParkingLot::operator<<(ostream &os, const MtmParkingLot::ParkingLot &parkingLot) {
    ParkingLotPrinter::printParkingLotTitle(cout);

}
