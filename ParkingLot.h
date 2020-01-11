#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "Vehicle.h"
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

    int numberOfSpots(unsigned int* parkingBlockSizes);
    void fillParkingSpotsArray(UniqueArray array, unsigned int* parkingBlockSizes);
    class ParkingLot {
    private:
        Vehicle *vehicles[];
        UniqueArray free_spots;
        UniqueArray taken_spots;
        static int size;
        bool filterFreeSpots(VehicleType type);
        void changeSpotStatus(ParkingSpot spot)
    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        bool vehicleIsIn(LicensePlate plate);
        Vehicle& getVehicleByPlates(LicensePlate license_plate);

    };
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
