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
        bool fined;
        ParkingSpot spot;
        int calculateDebt(Time departure) const;
        void giveTicket();
    public:
        Vehicle(Time arrival_time, VehicleType type, LicensePlate plate, const ParkingSpot spot);
        void addDebt(const Time departure_time);
        LicensePlate getPlates() const;
        ParkingSpot& getSpot() const;
        void inspection(Time inspection_time);
        int getDebt() const;
        Time getTime() const;
        VehicleType getType() const;
    }
}
#endif //MTMPARKINGLOT_VEHICLE_H