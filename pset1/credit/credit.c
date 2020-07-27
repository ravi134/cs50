// Returns AMEX\n, MASTERCARD\n, VISA\n or INVALID\n based on a user inputted credit card number
// AMEX has numbers 15 digits long starting with 34 OR 37
// MASTERCARD has numbers 16 digits long starting with 51, 52, 53, 54, 55
// VISA has numbers 13 OR 16 digits long starting with 4
// Checksum (applies to all card brands):
//  Step 1: Multiply every other digit by 2 starting with second to last digit and then add the digits of those products together
//  Step 2: Add sum to sum of digits not multiplied by 2
//  Step 3: If this value's last digit is 0, then number is valid
#include <cs50.h>
#include <stdio.h>

// declare funtions
bool check_sum(long ccnumber);
int card_length(long ccnumber);
int start_digits(long ccnumber);

int main(void)
{
    // get user credit card number
    long ccnumber = get_long("Number: ");

    // Assigning the integers
    bool last_digit = check_sum(ccnumber);
    int length = card_length(ccnumber);
    int start = start_digits(ccnumber);

    // Prints out card type
    if (last_digit == true && length == 15 && start == 1)
        printf("AMEX\n");
    else if (last_digit == true && length == 16 && start == 2)
        printf("MASTERCARD\n");
    else if (last_digit == true && (length == 13 || length == 16) && start == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
}

// Uses Luhn's algorithm to determine if the number is valid
bool check_sum(long ccnumber)
{
    bool last_digit;
    int value = 0;
    int count = 0;

    // Step 1: Multiply every other digit by 2 starting with second to last digit and then add the digits of those products together
    for (long i = 10; i <= 1e16; i *= 100)
    {
        int tempsum = 0;
        tempsum += (((ccnumber / i) % 10) * 2);
        count += ((tempsum / 10) + (tempsum % 10));
    }

    // Step 2: Add sum to sum of digits not multiplied by 2
    for (long i = 1; i <= 1e16; i *= 100)
        value += ((ccnumber / i) % 10);
    value += count;

    // Step 3: If this value's last digit is 0, then number is valid
    if ((value % 10) == 0)
        last_digit = true;
    else
        last_digit = false;
    return last_digit;
}

// Determines the length of the number
int card_length(long ccnumber)
{
    int length = 0;

    if (ccnumber >= 34e13 && ccnumber < 38e13)
        length = 15;
    if (ccnumber >= 4e12 && ccnumber < 5e12)
        length = 13;
    if ((ccnumber >= 4e15 && ccnumber < 5e15) || (ccnumber >= 51e14 && ccnumber < 56e14))
        length = 16;
    return length;
}

// Determines the starting digits of the number
int start_digits(long ccnumber)
{
    int start = 0;

    // AMEX
    if (ccnumber / 10000000000000 == 34 || ccnumber / 10000000000000 == 37)
        start = 1;
    // MASTERCARD
    if (ccnumber / 100000000000000 >= 51 && ccnumber / 100000000000000 <= 55)
        start = 2;
    // VISA
    if (ccnumber / 1000000000000 == 4 || ccnumber / 1000000000000000 == 4)
        start = 4;

    return start;
}