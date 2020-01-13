#include "ParkingLot.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"

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
        if (AllVehicles.count(licensePlate)) {
            Vehicle vehicle = AllVehicles[licensePlate];
            cout << vehicle;
            ParkingLotPrinter::printEntryFailureAlreadyParked(cout,
                vehicle.getParkingSpot());
            return VEHICLE_ALREADY_PARKED;
        }

        VehicleType parking_block_type = vehicleType;
        UniqueArray<LicensePlate> *parking_block =
            ParkingBlocks[parking_block_type];

        if (vehicleType == VehicleType::HANDICAPPED
            && parking_block->getCount() == parking_block->getSize()) {
            // handicapped full, fallback to normal parking
            parking_block_type = VehicleType::CAR;
            parking_block = &ParkingBlocks[parking_block_type];
        }

        if (parking_block->getCount() == parking_block->getSize()) {
            ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate,
                entranceTime);
            ParkingLotPrinter::printEntryFailureNoSpot(cout);
            return NO_EMPTY_SPOT;
        }

        unsigned int parking_number = parking_block.insert(licensePlate);

        AllVehicles[licensePlate] = Vehicle(licensePlate, type, parking_number, entranceTime);

        return SUCCESS;
    }
}
