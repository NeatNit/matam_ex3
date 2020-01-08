#ifndef MTMPARKINGLOT_VEHICLE_H
#define MTMPARKINGLOT_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"

namespace Vehicles{
    using namespace ParkingLotUtils;

    class Vehicle {
    private:
        Time arrival_time;
        VehicleType type;
        LicensePlate plate;
        int debt;
        ParkingSpot spot;
        int calculateDebt(Time departure, VehicleType type) const;
    public:
        Vehicle(Time arrival_time, VehicleType type, LicensePlate plate, const ParkingSpot spot);
        ~Vehicle();
        void addDebt(Time departure_time);
        void giveTicket();
        bool operator==(const Vehicle &vehicle) const;
        bool operator==(LicensePlate plate);
        LicensePlate getPlates() const;
        ParkingSpot& getSpot() const;
    }
}
#endif //MTMPARKINGLOT_VEHICLE_H