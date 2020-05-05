

const byte digits[2][10][7][2] = {
        {
                {{COL_1,ROW_4},{COL_1,ROW_2},{COL_1,ROW_3},{COL_2,ROW_1},{COL_2,ROW_2},{COL_1,ROW_1}},                // 0
                {{COL_1,ROW_2},{COL_1,ROW_3}},                                                                        // 1
                {{COL_1,ROW_4},{COL_1,ROW_2},{COL_1,ROW_5},{COL_2,ROW_2},{COL_2,ROW_1}},                              // 2
                {{COL_1,ROW_4},{COL_1,ROW_2},{COL_1,ROW_3},{COL_2,ROW_1},{COL_1,ROW_5}},                              // 3
                {{COL_1,ROW_1},{COL_1,ROW_5},{COL_1,ROW_2},{COL_1,ROW_3}},                                            // 4
                {{COL_1,ROW_4},{COL_1,ROW_1},{COL_1,ROW_5},{COL_1,ROW_3},{COL_2,ROW_1}},                              // 5
                {{COL_1,ROW_5},{COL_1,ROW_3},{COL_2,ROW_1},{COL_2,ROW_2},{COL_1,ROW_1},{COL_1,ROW_4}},                // 6
                {{COL_1,ROW_4},{COL_1,ROW_2},{COL_1,ROW_3}},                                                          // 7
                {{COL_1,ROW_4},{COL_1,ROW_2},{COL_1,ROW_3},{COL_2,ROW_1},{COL_2,ROW_2},{COL_1,ROW_1},{COL_1,ROW_5}},  // 8
                {{COL_1,ROW_4},{COL_1,ROW_2},{COL_1,ROW_3},{COL_2,ROW_1},{COL_1,ROW_1},{COL_1,ROW_5}},                // 9
        },
        {
                {{COL_5,ROW_1},{COL_5,ROW_4},{COL_5,ROW_3},{COL_5,ROW_2},{COL_4,ROW_3},{COL_4,ROW_2}},                // 0
                {{COL_5,ROW_3},{COL_5,ROW_2}},                                                                        // 1
                {{COL_5,ROW_4},{COL_5,ROW_3},{COL_4,ROW_4},{COL_4,ROW_2},{COL_4,ROW_3}},                              // 2
                {{COL_5,ROW_4},{COL_5,ROW_3},{COL_4,ROW_4},{COL_5,ROW_2},{COL_4,ROW_3}},                              // 3
                {{COL_5,ROW_1},{COL_4,ROW_4},{COL_5,ROW_3},{COL_5,ROW_2}},                                            // 4
                {{COL_5,ROW_4},{COL_5,ROW_1},{COL_4,ROW_4},{COL_5,ROW_2},{COL_4,ROW_3}},                              // 5
                {{COL_5,ROW_4},{COL_5,ROW_1},{COL_4,ROW_2},{COL_4,ROW_4},{COL_5,ROW_2},{COL_4,ROW_3}},                // 6
                {{COL_5,ROW_3},{COL_5,ROW_2},{COL_5,ROW_4}},                                                          // 7
                {{COL_5,ROW_1},{COL_5,ROW_4},{COL_5,ROW_3},{COL_5,ROW_2},{COL_4,ROW_3},{COL_4,ROW_2},{COL_4,ROW_4}},  // 8
                {{COL_5,ROW_1},{COL_5,ROW_4},{COL_5,ROW_3},{COL_5,ROW_2},{COL_4,ROW_3},{COL_4,ROW_4}},                // 9
        }
};

const byte digitLength[10] = {
        6, // 0
        2, // 1
        5, // 2
        5, // 3
        4, // 4
        5, // 5
        6, // 6
        3, // 7
        7, // 8
        6, // 9
};

void initDisplay()
{
    pinMode(COL_1, OUTPUT);
    pinMode(COL_2, OUTPUT);
    pinMode(COL_3, OUTPUT);
    pinMode(COL_4, OUTPUT);
    pinMode(COL_5, OUTPUT);

    pinMode(ROW_1, OUTPUT);
    pinMode(ROW_2, OUTPUT);
    pinMode(ROW_3, OUTPUT);
    pinMode(ROW_4, OUTPUT);
    pinMode(ROW_5, OUTPUT);
}

void displayDigit(byte pos, byte digit)
{
    for (byte i = 0; i < digitLength[digit]; i++) {
        digitalWrite(digits[pos][digit][i][0], LOW);
        digitalWrite(digits[pos][digit][i][1], HIGH);
        resetAll();
    }
}

void displaySeparator()
{
    digitalWrite(COL_3, LOW);
    digitalWrite(ROW_3, HIGH);
    resetAll();
}

void displayDot(byte pos)
{
    if (pos == DIGIT_LEFT) {
        digitalWrite(COL_2, LOW);
        digitalWrite(ROW_3, HIGH);
    } else {
        digitalWrite(COL_5, LOW);
        digitalWrite(ROW_5, HIGH);
    }

    resetAll();
}

void resetAll()
{
    digitalWrite(COL_1, HIGH);
    digitalWrite(COL_2, HIGH);
    digitalWrite(COL_3, HIGH);
    digitalWrite(COL_4, HIGH);
    digitalWrite(COL_5, HIGH);
    digitalWrite(ROW_1, LOW);
    digitalWrite(ROW_2, LOW);
    digitalWrite(ROW_3, LOW);
    digitalWrite(ROW_4, LOW);
    digitalWrite(ROW_5, LOW);
}