#ifndef MTMPARKINGLOT_PARKEDVEHICLE_H
#define MTMPARKINGLOT_PARKEDVEHICLE_H

#include "ParkingLotTypes.h"

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
        void giveFine(bool fine);
        friend ostream& operator<<(ostream& os, const ParkedVehicle& vehicle);
    };
}

#endif //MTMPARKINGLOT_PARKEDVEHICLE_H
