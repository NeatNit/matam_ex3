#ifndef MTMPARKINGLOT_PARKEDVEHICLE_H
#define MTMPARKINGLOT_PARKEDVEHICLE_H

#include "ParkingLotTypes.h"
#include "ParkingSpot.h"
#include "Time.h"

namespace ParkingLotUtils {
    class ParkedVehicle {
        LicensePlate licensePlate;
        VehicleType vehicleType;
        ParkingSpot parkingSpot;
        Time entranceTime;
        bool receivedFine;
    public:
        ParkedVehicle(LicensePlate licensePlate, VehicleType vehicleType,
            ParkingSpot parkingSpot, Time entranceTime);
        ParkedVehicle(const ParkedVehicle&) = default;
        LicensePlate getLicensePlate() const;
        VehicleType getVehicleType() const;
        ParkingSpot getParkingSpot() const;
        Time getEntranceTime() const;
        bool getHasReceivedFine() const;
        unsigned int getPrice(Time exitTime) const;
        void giveFine(bool fine);
        friend ostream& operator<<(ostream& os, const ParkedVehicle& vehicle);
    };

    // comparison between two vehicles will compare their ParkingSpots
    bool operator< (const ParkedVehicle& lhs, const ParkedVehicle& rhs);
}

#endif //MTMPARKINGLOT_PARKEDVEHICLE_H
