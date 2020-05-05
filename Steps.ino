void changeStep(byte step)
{
    currentStep = step;
}

void realNextStep()
{
    if (currentStep == totalSteps) {
        changeStep(1);
    } else {
        changeStep(currentStep + 1);
    }
}

void realPreviousStep()
{
    if (currentStep == 1) {
        changeStep(totalSteps);
    } else {
        changeStep(currentStep - 1);
    }
}

void resetSequence()
{
    switch (sequenceDirection) {
        case SEQUENCE_DIRECTION_FORWARD:
            changeStep(1);
            break;

        case SEQUENCE_DIRECTION_BACKWARD:
            changeStep(totalSteps);
            break;
    }
}

void handleStep(byte step)
{
    pinState = ClockCV.state();
    if (ClockCV.changed() && pinState == HIGH) {

        // Output a trigger when the gate just opened
        digitalWrite(TRIGGER, HIGH);

        // Go to next step when the gate just opened
        switch (sequenceDirection) {
            case SEQUENCE_DIRECTION_FORWARD:
                realNextStep();
                break;

            case SEQUENCE_DIRECTION_BACKWARD:
                realPreviousStep();
                break;

            case SEQUENCE_DIRECTION_RANDOM:
                changeStep(random(1, totalSteps));
                break;
        }
    }

    // Output CV for the step if not sleeping
    if (!steps[step].getSleep()) {
        analogWrite(CV1, steps[step].getCV(1));
        analogWrite(CV2, steps[step].getCV(2));
    }

    // Display the current step + the dot if the step is asleep
    display(step, steps[step].getSleep());
}