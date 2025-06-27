
#ifdef _DEBUG

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

int command[10];

void printCurrentStep(int step);
int inputParam(char* pBuf);
bool checkAnswerValidity(int step, int answer);
int getNextStep(int step, int answer);

void runTest(int answer);
void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

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
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

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
            runTest(answer);
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

void runTest(int answer)
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

void selectCarType(int answer)
{
    command[CarType_Q] = answer;
    if (answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    command[Engine_Q] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    command[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    command[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
{
    if (command[CarType_Q] == SEDAN && command[brakeSystem_Q] == CONTINENTAL)
        return false;

    if (command[CarType_Q] == SUV && command[Engine_Q] == TOYOTA)
        return false;

    if (command[CarType_Q] == TRUCK && command[Engine_Q] == WIA)
        return false;

    if (command[CarType_Q] == TRUCK && command[brakeSystem_Q] == MANDO)
        return false;

    if (command[brakeSystem_Q] == BOSCH_B && command[SteeringSystem_Q] != BOSCH_S)
        return false;

    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (command[Engine_Q] == 4)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    if (command[CarType_Q] == 1)
        printf("Car Type : Sedan\n");
    if (command[CarType_Q] == 2)
        printf("Car Type : SUV\n");
    if (command[CarType_Q] == 3)
        printf("Car Type : Truck\n");
    if (command[Engine_Q] == 1)
        printf("Engine : GM\n");
    if (command[Engine_Q] == 2)
        printf("Engine : TOYOTA\n");
    if (command[Engine_Q] == 3)
        printf("Engine : WIA\n");
    if (command[brakeSystem_Q] == 1)
        printf("Brake System : Mando");
    if (command[brakeSystem_Q] == 2)
        printf("Brake System : Continental\n");
    if (command[brakeSystem_Q] == 3)
        printf("Brake System : Bosch\n");
    if (command[SteeringSystem_Q] == 1)
        printf("SteeringSystem : Bosch\n");
    if (command[SteeringSystem_Q] == 2)
        printf("SteeringSystem : Mobis\n");

    printf("자동차가 동작됩니다.\n");
}

void testProducedCar()
{
    if (command[CarType_Q] == SEDAN && command[brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (command[CarType_Q] == SUV && command[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (command[CarType_Q] == TRUCK && command[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (command[CarType_Q] == TRUCK && command[brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (command[brakeSystem_Q] == BOSCH_B && command[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}

#endif