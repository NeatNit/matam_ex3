#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
namespace  Fees{
    const int FINE=250;
    const int HANDICAP_FEE=15;
    const int MOTORBIKE_FEE_FIRST=10;
    const int MOTORBIKE_FEE=5;
    const int CAR_FEE_FIRST=20;
    const int CAR_FEE=10;
    const int HOUR=1;
}
namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    int numberOfSpots(unsigned int* parkingBlockSizes);
    class ParkingLot {
    private:
        UniqueArray vehicles[];
        UniqueArray free_spots[];
        UniqueArray taken_spots[];
        static int size;
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

    class Vehicle{
    private:
        Time arrival_time;
        VehicleType type;
        LicensePlate plate;
        int debt;
        ParkingSpot spot;
        int calculateDebt(Time departure, VehicleType type) const;
    public:
        Vehicle (Time arrival_time, VehicleType type, LicensePlate plate, const ParkingSpot spot);
        ~Vehicle();
        void addDebt(Time departure_time);
        void giveTicket();
        Vehicle operator==(const Vehicle& vehicle) const;
        LicensePlate getPlates();
    };
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
