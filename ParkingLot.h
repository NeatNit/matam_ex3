#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {
    private:
        UniqueArray vehicles[];
        UniqueArray free_spots[];
        UniqueArray taken_spots[];
    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

    class Vehicle{
    private:
        Time arrival_time;
        VehicleType type;
        LicensePlate plate;
        int debt;
        ParkingSpot spot;
        int calculateDebt(Time departure, VehicleType type);
    public:
        VehicleType (Time arrival_time, VehicleType type, LicensePlate plate, ParkingSpot spot);
        ~Vehicle();
        void addDebt(Time departure);
        void giveTicket();


    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
