const byte digits[8][7] = {
    {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},
    {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},
    {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},
    {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},
    {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},
    {HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH},
    {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}
};

void display(byte digit, boolean displayDot)
{
    for (byte i = 0; i < 7; i++) {
        digitalWrite(0, digits[digit - 1][i]);
    }

    digitalWrite(0, displayDot ? HIGH : LOW);
}