#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "Vehicle.h"
#include <map>
#include <iostream>
namespace  Fees{
    const int FINE=250;
    const int HANDICAP_FEE=15;
    const int MOTORBIKE_FEE_FIRST=10;
    const int MOTORBIKE_FEE=5;
    const int CAR_FEE_FIRST=20;
    const int CAR_FEE=10;
}
namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using namespace Vehicles;
    using std::ostream;
    using std::cout;
    using std::map;

    int numberOfSpots(unsigned int* parkingBlockSizes);
    class ParkingLot {
    private:
        UniqueArray<LicensePlate> motorbikes;
        UniqueArray<LicensePlate> handicaps;
        UniqueArray<LicensePlate> cars;
        map<LicensePlate, Vehicle> plates_to_vehicles;
        map<int, Vehicle> spots_to_vehicles;
        unsigned int size;
        UniqueArray<LicensePlate>& uniqueArrayByType(VehicleType type) const;
        ParkingSpot findSpot(VehicleType type, int index);
    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);


        //bool vehicleIsIn(LicensePlate plate) const;
        //Vehicle& getVehicleByPlates(LicensePlate license_plate) const;

    };
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
