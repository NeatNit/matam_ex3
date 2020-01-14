#include <iostream>
#include <set>
#include <assert.h>

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
        if (allVehicles.count(licensePlate)) {
            const ParkedVehicle& vehicle = allVehicles.at(licensePlate);
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

        allVehicles.emplace(std::piecewise_construct,
            std::forward_as_tuple(licensePlate),
            std::forward_as_tuple(licensePlate, vehicleType, spot,
                entranceTime));

        ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate,
            entranceTime);
        ParkingLotPrinter::printEntrySuccess(cout, spot);
        return SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate,
        Time exitTime) {
        if (!allVehicles.count(licensePlate)) {
            ParkingLotPrinter::printExitFailure(cout, licensePlate);
            return ParkingResult::VEHICLE_NOT_FOUND;
        }
        const ParkedVehicle& vehicle = allVehicles.at(licensePlate);
        cout << vehicle;
        ParkingLotPrinter::printExitSuccess(cout, vehicle.getParkingSpot(),
            exitTime, vehicle.getPrice(exitTime));
        allVehicles.erase(licensePlate);
        return ParkingResult::SUCCESS;
    }

    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
        ParkingSpot& parkingSpot) const {
        if (!allVehicles.count(licensePlate)) {
            return ParkingResult::VEHICLE_NOT_FOUND;
        }
        const ParkedVehicle& vehicle = allVehicles.at(licensePlate);
        parkingSpot = vehicle.getParkingSpot();
        return ParkingResult::SUCCESS;
    }

    ostream& operator<<(ostream& os, const ParkingLot& parkingLot) {
        ParkingLotPrinter::printParkingLotTitle(cout);
        std::set<ParkedVehicle> orderedVehicles;
        // Create a sorted set of all the vehicles
        // (vehicles sort by ParkingSpot)
        for (auto const & pair : parkingLot.allVehicles)
        {
            orderedVehicles.emplace(pair.second);
        }
        // Now print them all
        for (ParkedVehicle const & vehicle : orderedVehicles)
        {
            cout << vehicle;
            ParkingLotPrinter::printParkingSpot(cout, vehicle.getParkingSpot());
        }
        return cout;
    }

    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        unsigned int fine_count = 0;
        Time::Hour limit = 24;

        for(auto & pair : allVehicles) {
            ParkedVehicle& vehicle = pair.second;
            if (!vehicle.getHasReceivedFine()
                && (inspectionTime - vehicle.getEntranceTime())
                    .toHours() > limit) {
                vehicle.giveFine(true);
                ++fine_count;
            }
        }

        ParkingLotPrinter::printInspectionResult(cout, inspectionTime,
            fine_count);

#ifndef NDEBUG
        // make sure that it actually modified the stored vehicles
        unsigned int total_fines;
        for(auto & pair : allVehicles) {
            ParkedVehicle& vehicle = pair.second;
            if (vehicle.getHasReceivedFine()){
                ++total_fines;
            }
        }
        assert(total_fines >= fine_count);
#endif
    }
}
