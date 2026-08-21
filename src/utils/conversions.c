void int_to_string(int n, char *buffer) 
{
    // should maybe use a pow method but too lazy

    int ten_to_power_of_digitcount = 1, cn = n;
    while (cn > 0)
    {
        cn = cn / 10;
        ten_to_power_of_digitcount *= 10;
    }

    // start with first digit
    int i = 0;
    ten_to_power_of_digitcount /= 10;
    while (ten_to_power_of_digitcount >= 1)
    {
        *(buffer + i) = (char) (n / ten_to_power_of_digitcount % 10) + '0';
        ten_to_power_of_digitcount /= 10;
        i++;
    }

}