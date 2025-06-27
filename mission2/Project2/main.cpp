#include "car.h"
#include <string>

using namespace std;
#ifdef _DEBUG
//#if 0
#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"
#define INVALID_PARAM (0xFFFFFFFF)

CarFactory carFactory;

void printCurrentStep(int step);
int inputParam(char* pBuf);
bool checkAnswerValidity(int step, int answer);
int getNextStep(int step, int answer);

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);


void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int main()
{
    char buf[100];
    int step = CarType_Q;

    while (true)
    {
        printCurrentStep(step);
        int answer = inputParam(buf);

        if (false == checkAnswerValidity(step, answer))
            continue;

        step = getNextStep(step, answer);
        if (step == INVALID_PARAM)
            continue;

        switch (step)
        {
        case CarType_Q:
            selectCarType(answer);
            delay(800);
            step = Engine_Q;
            break;
        case Engine_Q:
            selectEngine(answer);
            delay(800);
            step = brakeSystem_Q;
            break;
        case brakeSystem_Q:
            selectbrakeSystem(answer);
            delay(800);
            step = SteeringSystem_Q;
            break;
        case SteeringSystem_Q:
            selectSteeringSystem(answer);
            delay(800);
            step = Run_Test;
            break;
        case  Run_Test:
        {
            if (answer == 1)
            {
                runProducedCar();
                delay(2000);
            }
            else if (answer == 2)
            {
                printf("Test...\n");
                delay(1500);
                testProducedCar();
                delay(2000);
            }
        }
            break;
        default:
            break;
        };
    }
}

void printCurrentStep(int step)
{
    if (step == CarType_Q)
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (step == brakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
}

int inputParam(char* pBuf)
{
    printf("INPUT > ");
    fgets(pBuf, sizeof(pBuf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(pBuf, "\r", &context);
    strtok_s(pBuf, "\n", &context);

    if (!strcmp(pBuf, "exit"))
    {
        printf("바이바이\n");
        return INVALID_PARAM;
    }

    // 숫자로 된 대답인지 확인
    char* checkNumber = nullptr;
    int answer = strtol(pBuf, &checkNumber, 10); // 문자열을 10진수로 변환
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return INVALID_PARAM;
    }

    return answer;
}

bool checkAnswerValidity(int step, int answer)
{
    if (answer == INVALID_PARAM)
    {
        delay(800);
        return false;
    }

    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return false;
    }

    return true;
}

int getNextStep(int step, int answer)
{
    // 처음으로 돌아가기
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return INVALID_PARAM;
    }

    // 이전으로 돌아가기
    if (answer == 0 && step >= 1)
    {
        step -= 1;
        return INVALID_PARAM;
    }

    return step;
}

void selectCarType(int answer)
{
    printf(carFactory.selectCarType(answer).c_str());
}

void selectEngine(int answer)
{
    printf(carFactory.selectEngine(answer).c_str());
}

void selectbrakeSystem(int answer)
{
    printf(carFactory.selectBrakeSystem(answer).c_str());
}

void selectSteeringSystem(int answer)
{
    printf(carFactory.selectSteeringSystem(answer).c_str());
}

void runProducedCar()
{
    string retmsg;
    if (carFactory.runProducedCar(&retmsg) == false)
    {
        printf(retmsg.c_str());
        return;
    }

    string msg;
    carFactory.getSelectedCarType(&msg);
    printf(msg.c_str());
    carFactory.getSelectedEngine(&msg);
    printf(msg.c_str());
    carFactory.getSelectedBrakeSystem(&msg);
    printf(msg.c_str());
    carFactory.getSelectedSteeringSystem(&msg);
    printf(msg.c_str());

    printf(retmsg.c_str());
}

void testProducedCar()
{
    string result;
    string reason;
    carFactory.testProducedCar(&result, &reason);
}

#endif