#include "gmock/gmock.h"
#include "car.h"
#include <string>
using namespace std;

TEST(Group, TC1) {
	CarFactory carfactory;
	string msg, reason;
	bool ret1, ret2;

	carfactory.selectCarType(SEDAN);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(MANDO);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, true);
	EXPECT_EQ(ret2, true);

	carfactory.selectCarType(SUV);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(MANDO);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, true);
	EXPECT_EQ(ret2, true);

	carfactory.selectCarType(TRUCK);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(MANDO);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, false);
	EXPECT_EQ(ret2, false);


	carfactory.selectCarType(SEDAN);
	carfactory.selectEngine(TOYOTA);
	carfactory.selectBrakeSystem(MANDO);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, true);
	EXPECT_EQ(ret2, true);

	carfactory.selectCarType(SEDAN);
	carfactory.selectEngine(WIA);
	carfactory.selectBrakeSystem(MANDO);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, true);
	EXPECT_EQ(ret2, true);


	carfactory.selectCarType(SEDAN);
	carfactory.selectEngine(DAMAGED);
	carfactory.selectBrakeSystem(MANDO);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, false);
	EXPECT_EQ(ret2, true);


	carfactory.selectCarType(SUV);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(CONTINENTAL);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, true);
	EXPECT_EQ(ret2, true);

	carfactory.selectCarType(SUV);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(BOSCH_B);
	carfactory.selectSteeringSystem(BOSCH_S);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, true);
	EXPECT_EQ(ret2, true);

	carfactory.selectCarType(SEDAN);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(CONTINENTAL);
	carfactory.selectSteeringSystem(MOBIS);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, false);
	EXPECT_EQ(ret2, false);

	carfactory.selectCarType(SUV);
	carfactory.selectEngine(TOYOTA);
	carfactory.selectBrakeSystem(CONTINENTAL);
	carfactory.selectSteeringSystem(MOBIS);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, false);
	EXPECT_EQ(ret2, false);

	carfactory.selectCarType(TRUCK);
	carfactory.selectEngine(WIA);
	carfactory.selectBrakeSystem(CONTINENTAL);
	carfactory.selectSteeringSystem(MOBIS);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, false);
	EXPECT_EQ(ret2, false);

	carfactory.selectCarType(SEDAN);
	carfactory.selectEngine(GM);
	carfactory.selectBrakeSystem(BOSCH_B);
	carfactory.selectSteeringSystem(MOBIS);
	ret1 = carfactory.runProducedCar(&msg);
	ret2 = carfactory.testProducedCar(&msg, &reason);

	EXPECT_EQ(ret1, false);
	EXPECT_EQ(ret2, false);
}