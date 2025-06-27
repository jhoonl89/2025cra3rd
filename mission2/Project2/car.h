#pragma once

#include <string>
using namespace std;
enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    CarTypeNone,
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    EngineNone,
    GM = 1,
    TOYOTA,
    WIA,
    DAMAGED,
};

enum BrakeSystem
{
    BrakeSystemNone,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    SteeringSystemNone,
    BOSCH_S = 1,
    MOBIS
};

struct SelectedItem {
    CarType m_CarType{ CarTypeNone };
    Engine m_Engine{ EngineNone };
    BrakeSystem m_BrakeSystem{ BrakeSystemNone };
    SteeringSystem m_SteeringSystem{ SteeringSystemNone };
};

class CarParts {
public:
    CarParts() = default;
    virtual string GetMsg() = 0;

    void setType(int type) { m_type = type; }
    int getType() { return m_type; }
private:
    int m_type;
};

class SedanCarBody : public CarParts {
public:
    SedanCarBody() = default;
    string GetMsg() override
    {
        return "���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n";
    }
};

class SuvCarBody : public CarParts {
public:
    SuvCarBody() = default;
    string GetMsg() override
    {
        char msg[100] = "���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n";
        return msg;
    }
};

class TruckCarBody : public CarParts {
public:
    TruckCarBody() = default;
    string GetMsg() override
    {
        char msg[100] = "���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n";
        return msg;
    }
};

class GMEngine : public CarParts {
public:
    GMEngine() = default;
    string GetMsg() override
    {
        return "GM ������ �����ϼ̽��ϴ�.\n";
    }
};

class TOYOTAEngine : public CarParts {
public:
    TOYOTAEngine() = default;
    string GetMsg() override
    {
        return "GM ������ �����ϼ̽��ϴ�.\n";
    }
};

class WIAEngine : public CarParts {
public:
    WIAEngine() = default;
    string GetMsg() override
    {
        return "GM ������ �����ϼ̽��ϴ�.\n";
    }
};

class MANDOBrake : public CarParts {
public:
    MANDOBrake() = default;
    string GetMsg() override
    {
        return "MANDO ������ġ�� �����ϼ̽��ϴ�.\n";
    }
};
class CONTINENTALBrake : public CarParts {
public:
    CONTINENTALBrake() = default;
    string GetMsg() override
    {
        return "CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n";
    }
};
class BOSCH_BBrake : public CarParts {
public:
    BOSCH_BBrake() = default;
    string GetMsg() override
    {
        return "BOSCH ������ġ�� �����ϼ̽��ϴ�.\n";
    }
};

class BOSCH_SSteering : public CarParts {
public:
    BOSCH_SSteering() = default;
    string GetMsg() override
    {
        return "BOSCH ������ġ�� �����ϼ̽��ϴ�.\n";
    }
};
class MOBISSteering : public CarParts {
public:
    MOBISSteering() = default;
    string GetMsg() override
    {
        return "MOBIS ������ġ�� �����ϼ̽��ϴ�.\n";
    }
};

class CarFactory {
public:
    string selectCarType(int answer);
    string selectEngine(int answer);
    string selectBrakeSystem(int answer);
    string selectSteeringSystem(int answer);

    int getSelectedCarType(string* msg);
    int getSelectedEngine(string* msg);
    int getSelectedBrakeSystem(string* msg);
    int getSelectedSteeringSystem(string* msg);

    bool isValidCheck(string* msg);

    bool runProducedCar(string* msg);
    bool testProducedCar(string* result, string* reason);

private:
    SelectedItem m_SelectedItem;
    CarParts* m_carbody{ nullptr };
    CarParts* m_Engine{ nullptr };
    CarParts* m_brakeSystem{ nullptr };
    CarParts* m_SteeringSystem{ nullptr };
};

