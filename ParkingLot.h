#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include <map>

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "ParkedVehicle.h"

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    typedef UniqueArray<LicensePlate> ParkingBlock;
    typedef std::map<LicensePlate, ParkedVehicle> VehicleMap;

    class ParkingLot {
        ParkingBlock *parkingBlocks[VehicleType::LAST-VehicleType::FIRST+1];
        VehicleMap allVehicles;
    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
