OBJS = MtmParkingLot.o ParkedVehicle.o ParkingLot.o ParkingLotPrinter.o \
 ParkingSpot.o Time.o
EXEC = MtmParkingLot
DEBUG_FLAG = -g
CPPFLAGS = -std=c++11 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)

$(EXEC): $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h \
 ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h \
 UniqueArrayImp.h ParkedVehicle.h
ParkedVehicle.o: ParkedVehicle.cpp ParkedVehicle.h ParkingLotTypes.h \
 ParkingSpot.h Time.h ParkingLotPrinter.h
ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h \
 ParkingSpot.h UniqueArray.h UniqueArrayImp.h ParkedVehicle.h \
 ParkingLotPrinter.h
ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h \
 ParkingSpot.h ParkingLotTypes.h
ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
Time.o: Time.cpp Time.h

clean:
	rm -f $(EXEC) $(OBJS)
