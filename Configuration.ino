void handleConfiguration(byte step)
{
    setConfigurationStep();
    setSequenceDirection();
    setCVOutput();
    setSleepMode();
    setCVValues();
    displayConfigurationStep();
}

void changeConfigurationStep(byte step)
{
    currentConfigurationStep = step;
}

void nextConfigurationStep()
{
    if (currentConfigurationStep == totalSteps) {
        changeConfigurationStep(1);
    } else {
        changeConfigurationStep(currentStep + 1);
    }
}

void previousConfigurationStep()
{
    if (currentConfigurationStep == 1) {
        changeConfigurationStep(totalSteps);
    } else {
        changeConfigurationStep(currentConfigurationStep - 1);
    }
}

void setConfigurationStep()
{
    // Read next button
    pinState = NextSwitch.stateDebounced();
    if (NextSwitch.changed() && pinState == HIGH) {
        nextStep();
    }

    // Read previous button
    pinState = PreviousSwitch.stateDebounced();
    if (PreviousSwitch.changed() && pinState == HIGH) {
        previousStep();
    }
}

void setSequenceDirection()
{
    // Read direction buttons
    if (PlayBackwardSwitch.state()) {
        sequenceDirection = SEQUENCE_DIRECTION_BACKWARD;
    } else if (PlayRandomSwitch.state()) {
        sequenceDirection = SEQUENCE_DIRECTION_RANDOM;
    } else {
        sequenceDirection = SEQUENCE_DIRECTION_FORWARD;
    }
}

void setCVOutput()
{
    boolean cv = false;

    // Read CV output switch
    pinState = CVOutput1Switch.state();
    if (pinState == HIGH) {
        steps[currentConfigurationStep].setCVOutput(CV_OUTPUT_1);
        cv = true;
    }

    pinState = CVOutput2Switch.state();
    if (pinState == HIGH) {
        steps[currentConfigurationStep].setCVOutput(CV_OUTPUT_2);
        cv = true;
    }

    if (cv = false) {
        steps[currentConfigurationStep].setCVOutput(CV_OUTPUT_BOTH);
    }
}

void setCVValues()
{
    // Read potentiometer 1
    potValue = CV1Pot.value();
    if (CV1Pot.changed()) {
        steps[currentConfigurationStep].setCV(1, potValue);
    }

    // Read potentiometer 2
    potValue = CV2Pot.value();
    if (CV2Pot.changed()) {
        steps[currentConfigurationStep].setCV(2, potValue);
    }
}

void setSleepMode()
{
    // Read sleep button
    pinState = SleepSwitch.stateDebounced();
    if (SleepSwitch.changed()) {
        steps[currentConfigurationStep].setSleep(pinState == HIGH ? true : false);
    }
}

void displayConfigurationStep()
{
    displayDigit(DIGIT_RIGHT, currentConfigurationStep);

    if (steps[currentConfigurationStep].getSleep()) {
        displayDot(DIGIT_RIGHT);
    }
}