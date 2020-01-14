#include "ParkedVehicle.h"
#include "ParkingLotTypes.h"
#include "ParkingSpot.h"
#include "Time.h"

namespace ParkingLotUtils {
    ParkedVehicle::ParkedVehicle(LicensePlate licensePlate, VehicleType vehicleType,
        ParkingSpot parkingSpot, Time entranceTime) :
        licensePlate(licensePlate), vehicleType(vehicleType),
        parkingSpot(parkingSpot), entranceTime(entranceTime),
        receivedFine(false) {}

    LicensePlate ParkedVehicle::getLicensePlate() const {
        return licensePlate;
    }

    VehicleType ParkedVehicle::getVehicleType() const {
        return vehicleType;
    }

    ParkingSpot ParkedVehicle::getParkingSpot() const {
        return parkingSpot;
    }

    Time ParkedVehicle::getEntranceTime() const {
        return entranceTime;
    }

    bool ParkedVehicle::getHasReceivedFine() const {
        return receivedFine;
    }

    void ParkedVehicle::giveFine(bool fine) {
        receivedFine = fine;
    }

    unsigned int ParkedVehicle::getPrice(Time exitTime) const {
        const Time::Hour max_hours = 6;

        const unsigned int motorbike_first_hour_cost = 10;
        const unsigned int motorbike_hourly_cost = 5;

        const unsigned int car_first_hour_cost = 20;
        const unsigned int car_hourly_cost = 10;

        const unsigned int handicapped_cost = 15;

        const unsigned int fine_cost = 250;

        unsigned int hourly_cost, first_hour_cost;

        switch(vehicleType) {
        case VehicleType::HANDICAPPED:
            return handicapped_cost + (receivedFine ? fine_cost : 0);
        case VehicleType::MOTORBIKE:
            first_hour_cost = motorbike_first_hour_cost;
            hourly_cost = motorbike_hourly_cost;
        case VehicleType::CAR:
            first_hour_cost = car_first_hour_cost;
            hourly_cost = car_hourly_cost;
        }

        Time::Hour parked_hours = (exitTime - entranceTime).toHours();
        if (parked_hours > max_hours) {
            parked_hours = max_hours;
        }

        unsigned int total_cost = first_hour_cost;
        --parked_hours;

        total_cost += parked_hours * hourly_cost;
        total_cost += receivedFine ? fine_cost : 0;

        return total_cost;
    }
}
