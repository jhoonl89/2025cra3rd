#include "car.h"

string CarFactory::selectCarType(int answer)
{
    m_SelectedItem.m_CarType = static_cast<CarType>(answer);

    switch (m_SelectedItem.m_CarType)
    {
    case SEDAN:
        m_carbody = new SedanCarBody();
        break;
    case SUV:
        m_carbody = new SuvCarBody();
        break;
    case TRUCK:
        m_carbody = new TruckCarBody();
        break;
    default:
        break;
    };
    m_carbody->setType(m_SelectedItem.m_CarType);
    return m_carbody->GetMsg();
}

string CarFactory::selectEngine(int answer)
{
    m_SelectedItem.m_Engine = static_cast<Engine>(answer);

    switch (m_SelectedItem.m_CarType)
    {
    case GM:
        m_Engine = new GMEngine();
        break;
    case TOYOTA:
        m_Engine = new TOYOTAEngine();
        break;
    case WIA:
        m_Engine = new WIAEngine();
        break;
    default:
        break;
    };
    m_Engine->setType(m_SelectedItem.m_Engine);
    return m_Engine->GetMsg();
}

string CarFactory::selectBrakeSystem(int answer)
{
    m_SelectedItem.m_BrakeSystem = static_cast<BrakeSystem>(answer);

    switch (m_SelectedItem.m_BrakeSystem)
    {
    case GM:
        m_brakeSystem = new MANDOBrake();
        break;
    case TOYOTA:
        m_brakeSystem = new CONTINENTALBrake();
        break;
    case WIA:
        m_brakeSystem = new BOSCH_BBrake();
        break;
    default:
        break;
    };
    m_brakeSystem->setType(m_SelectedItem.m_BrakeSystem);
    return m_brakeSystem->GetMsg();
}

string CarFactory::selectSteeringSystem(int answer)
{
    m_SelectedItem.m_SteeringSystem = static_cast<SteeringSystem>(answer);

    switch (m_SelectedItem.m_SteeringSystem)
    {
    case GM:
        m_SteeringSystem = new BOSCH_SSteering();
        break;
    case TOYOTA:
        m_SteeringSystem = new MOBISSteering();
        break;
        break;
    default:
        break;
    };
    m_SteeringSystem->setType(m_SelectedItem.m_SteeringSystem);
    return m_SteeringSystem->GetMsg();
}

int CarFactory::getSelectedCarType(string* msg)
{
    return static_cast<int>(m_SelectedItem.m_CarType);
}

int CarFactory::getSelectedEngine(string* msg)
{
    return static_cast<int>(m_SelectedItem.m_Engine);
}

int CarFactory::getSelectedBrakeSystem(string* msg)
{
    return static_cast<int>(m_SelectedItem.m_BrakeSystem);
}

int CarFactory::getSelectedSteeringSystem(string* msg)
{
    return static_cast<int>(m_SelectedItem.m_SteeringSystem);
}

bool CarFactory::isValidCheck(string* msg)
{
    bool ret = true;
    if (m_SelectedItem.m_CarType == SEDAN && m_SelectedItem.m_BrakeSystem == CONTINENTAL)
        ret = false;

    if (m_SelectedItem.m_CarType == SUV && m_SelectedItem.m_Engine == TOYOTA)
        ret = false;

    if (m_SelectedItem.m_CarType == TRUCK && m_SelectedItem.m_Engine == WIA)
        ret = false;

    if (m_SelectedItem.m_CarType == TRUCK && m_SelectedItem.m_BrakeSystem == MANDO)
        ret = false;

    if (m_SelectedItem.m_BrakeSystem == BOSCH_B && m_SelectedItem.m_SteeringSystem != BOSCH_S)
        ret = false;

    if (m_SelectedItem.m_Engine == DAMAGED)
        ret = false;
    
    *msg = (ret == false) ? ("�ڵ����� ���۵��� �ʽ��ϴ�\n") : ("�ڵ����� ���۵˴ϴ�.\n");

    return ret;
}

bool CarFactory::runProducedCar(string* msg)
{
    if (false == isValidCheck(msg))
        return false;

    return true;
}

bool CarFactory::testProducedCar(string* result, string* reason)
{
    bool ret = true;
    *result = "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
    if (m_carbody->getType() == SEDAN && m_brakeSystem->getType() == CONTINENTAL)
    {
        *reason = "Sedan���� Continental������ġ ��� �Ұ�\n";
        ret = false;
    }
    else if (m_carbody->getType() == SUV && m_Engine->getType() == TOYOTA)
    {
        *reason = "SUV���� TOYOTA���� ��� �Ұ�\n";
        ret = false;
    }
    else if (m_carbody->getType() == TRUCK && m_Engine->getType() == WIA)
    {
        *reason = "Truck���� WIA���� ��� �Ұ�\n";
        ret = false;
    }
    else if (m_carbody->getType() == TRUCK && m_brakeSystem->getType() == MANDO)
    {
        *reason = "Truck���� Mando������ġ ��� �Ұ�\n";
        ret = false;
    }
    else if (m_brakeSystem->getType() == BOSCH_B && m_SteeringSystem->getType() != BOSCH_S)
    {
        *reason = "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n";
        ret = false;
    }
    else
    {
        *result = "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n";
    }

    return ret;
}

