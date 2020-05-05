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

CS_Switch ClockCV(CLOCK);
CS_Switch ResetCV(RESET);

const byte totalSteps = 8;
byte currentStep = 1;
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

void handleConfiguration(byte step)
{
    // Read direction buttons
    if (PlayBackwardSwitch.state()) {
        sequenceDirection = SEQUENCE_DIRECTION_BACKWARD;
    } else if (PlayRandomSwitch.state()) {
        sequenceDirection = SEQUENCE_DIRECTION_RANDOM;
    } else {
        sequenceDirection = SEQUENCE_DIRECTION_FORWARD;
    }

    // Read next button
    pinState = NextSwitch.stateDebounced();
    if (NextSwitch.changed() && pinState == HIGH) {
        realNextStep();
    }

    // Read previous button
    pinState = PreviousSwitch.stateDebounced();
    if (PreviousSwitch.changed() && pinState == HIGH) {
        realPreviousStep();
    }

    // Read sleep button
    pinState = SleepSwitch.stateDebounced();
    if (SleepSwitch.changed()) {
        steps[step].setSleep(pinState == HIGH ? true : false);
    }

    // Read potentiometer 1
    potValue = CV1Pot.value();
    if (CV1Pot.changed()) {
        steps[step].setCV(1, potValue);
    }

    // Read potentiometer 2
    potValue = CV2Pot.value();
    if (CV2Pot.changed()) {
        steps[step].setCV(2, potValue);
    }
}