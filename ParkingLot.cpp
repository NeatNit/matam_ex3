#include "ParkingLot.h"
#include "ParkingLotTypes.h"

namespace MtmParkingLot {
    using std::cout;

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) {
        for (int i = VehicleType::FIRST; i <= VehicleType::LAST; ++i) {
            ParkingBlocks[i] =
            new UniqueArray<LicensePlate>(parkingBlockSizes[i]);
        }
    }

    ParkingLot::~ParkingLot() {
        for (int i = VehicleType::FIRST; i <= VehicleType::LAST; ++i) {
            delete ParkingBlocks[i];
        }
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
