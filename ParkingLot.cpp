#include "ParkingLot.h"
#include "ParkingLotPrinter.cpp"
#include "Vehicle.h"

using namespace ParkingLotUtils;
using namespace MtmParkingLot;
using namespace Fees;
using namespace Vehicles;
using std::cout;
using std::ostream;


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
    Vehicle vehicles[]=new UniqueArray(size);
    UniqueArray<ParkingSpot> free_spots=new UniqueArray(size);
    UniqueArray<ParkingSpot> taken_spots=new UniqueArray(size);
    fillParkingSpotsArray(free_spots, parkingBlockSizes);
}

ParkingLot::~ParkingLot() {
    delete vehicles;
    delete free_spots;
    delete taken_spots;
}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
    if(vehicleIsIn(licensePlate)){
        Vehicle& vehicle=getVehicleByPlates(licensePlate);
        ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);
        ParkingLotPrinter::printEntryFailureAlreadyParked(cout, vehicle.getSpot());
    }

    Vehicle vehicle=new Vehicle(vehicleType, licensePlate, entranceTime);
    vehicles->insert(vehicle);

}

Vehicle& ParkingLot::getVehicleByPlates(ParkingLotUtils::LicensePlate license_plate) {
    for (int i=0;i<size;i++){
        if(vehicles[i]==license_plate){
            return vehicles[i];
        }
    }
    throw //TODO
}

