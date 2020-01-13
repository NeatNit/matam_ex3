#include "ParkingLot.h"
#include "ParkingLotTypes.h"

namespace MtmParkingLot {
    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) {}

    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
        ParkingSpot& parkingSpot) const {
        if (!AllVehicles.count(licensePlate)) {
            // car is not in the parking lot
            return "some kind of error";
        }
        Vehicle vehicle = AllVehicles[licensePlate];

        parkingSpot = ParkingSpot(vehicle.type, vehicle.parkingSpot);
        return SUCCESS;

        /*
        // select according to type
        UniqueArray<LicensePlate> parking_block& = Motorbikes;
        if (type == CAR) {
            parking_block = Cars;
        } else if (type == HANDICAPPED) {
            parking_block = Handicaps;
        }

        unsigned int parking_number = parking_block.getIndex(licensePlate);

        parkingSpot = ParkingSpot(type, parking_number);
        return SUCCESS;
        */
    }

    ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
        LicensePlate licensePlate, Time entranceTime) {

        UniqueArray<LicensePlate> parking_block& = Motorbikes;
        if (type == CAR) {
            parking_block = Cars;
        } else if (type == HANDICAPPED) {
            parking_block = Handicaps;
        }

        if (parking_block.getCount() == parking_block.getSize()) {
            return NO_ROOM;
        }

        unsigned int parking_number = parking_block.insert(licensePlate);

        AllVehicles[licensePlate] = Vehicle(licensePlate, type, parking_number, entranceTime);

        return SUCCESS;
    }
}
