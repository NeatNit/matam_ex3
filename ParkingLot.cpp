#include <iostream>

#include "ParkingLot.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"
#include "ParkedVehicle.h"

namespace MtmParkingLot {
    using std::cout;
    using namespace ParkingLotUtils;

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) {
        for (int i = VehicleType::FIRST; i <= VehicleType::LAST; ++i) {
            parkingBlocks[i] = new ParkingBlock(parkingBlockSizes[i]);
        }
    }

    ParkingLot::~ParkingLot() {
        for (int i = VehicleType::FIRST; i <= VehicleType::LAST; ++i) {
            delete parkingBlocks[i];
        }
    }

    ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
        LicensePlate licensePlate, Time entranceTime) {
        if (AllVehicles.count(licensePlate)) {
            const ParkedVehicle& vehicle =
                AllVehicles.find(licensePlate)->second;
            cout << vehicle;
            ParkingLotPrinter::printEntryFailureAlreadyParked(cout,
                vehicle.getParkingSpot());
            return VEHICLE_ALREADY_PARKED;
        }

        VehicleType parking_block_type = vehicleType;
        ParkingBlock * parking_block =
            parkingBlocks[parking_block_type];

        if (vehicleType == VehicleType::HANDICAPPED
            && parking_block->getCount() == parking_block->getSize()) {
            // handicapped lot is full, fallback to normal parking
            parking_block_type = VehicleType::CAR;
            parking_block = parkingBlocks[parking_block_type];
        }

        unsigned int parking_number;
        try {
            parking_number = parking_block->insert(licensePlate);
        } catch (ParkingBlock::UniqueArrayIsFullException e) {
            ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate,
                entranceTime);
            ParkingLotPrinter::printEntryFailureNoSpot(cout);
            return NO_EMPTY_SPOT;
        }

        ParkingSpot spot(parking_block_type, parking_number);

        AllVehicles.emplace(std::piecewise_construct,
            std::forward_as_tuple(licensePlate),
            std::forward_as_tuple(licensePlate, vehicleType, spot,
                entranceTime));

        return SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate,
        Time exitTime) {
        if (!AllVehicles.count(licensePlate)) {
            ParkingLotPrinter::printExitFailure(cout, licensePlate);
            return ParkingResult::VEHICLE_NOT_FOUND;
        }
        const ParkedVehicle& vehicle = AllVehicles.find(licensePlate)->second;
        cout << vehicle;
        ParkingLotPrinter::printExitSuccess(cout, vehicle.getParkingSpot(),
            exitTime, vehicle.getPrice(exitTime));
        AllVehicles.erase(licensePlate);
        return ParkingResult::SUCCESS;
    }
}
