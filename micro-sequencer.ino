#define POT1 A0 // Analog Input
#define POT2 A1 // Analog Input

#define CV1 A4 // Analog Output
#define CV2 A5 // Analog Output

#define CLOCK 0 // Digital Input
#define RESET 1 // Digital Input
#define PREV 2 // Digital Input
#define NEXT 3 // Digital Input
#define SLEEP 4 // Digital Input

#define PLAY_BACKWARD 8 // Digital Input
#define PLAY_RANDOM 9 // Digital Input

#define CV_OUTPUT_BOTH 0
#define CV_OUTPUT_1 1
#define CV_OUTPUT_2 2
#define CV_OUT_1 10 // Digital Input
#define CV_OUT_2 11 // Digital Input

#define TRIGGER 5 // PWM Output

#include "CS_Switch.h"
#include "CS_Pot.h"
#include "Step.h"

CS_Pot CV1Pot(POT1, 3);
CS_Pot CV2Pot(POT2, 3);

CS_Switch PreviousSwitch(PREV);
CS_Switch NextSwitch(NEXT);
CS_Switch SleepSwitch(SLEEP);

CS_Switch PlayBackwardSwitch(PLAY_BACKWARD);
CS_Switch PlayRandomSwitch(PLAY_RANDOM);

CS_Switch CVOutput1Switch(CV_OUT_1);
CS_Switch CVOutput2Switch(CV_OUT_2);

CS_Switch ClockCV(CLOCK);
CS_Switch ResetCV(RESET);

const byte totalSteps = 8;
byte currentStep = 1;
byte currentConfigurationStep = 1;
Step steps[totalSteps];

#define SEQUENCE_DIRECTION_FORWARD 0
#define SEQUENCE_DIRECTION_BACKWARD 1
#define SEQUENCE_DIRECTION_RANDOM 2
byte sequenceDirection = SEQUENCE_DIRECTION_FORWARD;

byte pinState;
int potValue;

void setup()
{
    Serial.begin(9600);

    pinMode(CV1, OUTPUT);
    pinMode(CV2, OUTPUT);
    pinMode(TRIGGER, OUTPUT);

    CV1Pot.begin();
    CV2Pot.begin();

    while (PreviousSwitch.stateDebounced() == 0);
    while (NextSwitch.stateDebounced() == 0);
    while (SleepSwitch.stateDebounced() == 0);
}

void loop()
{
    // Stop trigger
    digitalWrite(TRIGGER, LOW);

    // Read reset CV input
    pinState = ResetCV.state();
    if (ResetCV.changed() && pinState == HIGH) {
        resetSequence();
    }

    handleConfiguration(currentStep);

    // Read clock
    handleStep(currentStep);

    delay(10);
}