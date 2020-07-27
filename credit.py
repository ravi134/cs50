from cs50 import get_int

def main():
    ccn = get_int("Number: ")
    l = 0
    s = 0
    sum1 = 0
    sum2 = ccn // 10
    total_sum = 0

    # checks for length of ccn
    if ccn >= 34e13 and ccn < 38e13:
        l = 15
    if ccn >= 4e12 and ccn < 5e12:
        l = 13
    if ccn >= 4e15 and ccn < 5e15 or ccn >= 51e14 and ccn < 56e14:
        l = 16

    # determines the starting digits of ccn
    # AMEX
    if ccn // 1e13 == 34 or ccn // 1e13 == 37:
        s = 1
    # MASTERCARD
    if ccn // 1e14 >= 51 and ccn // 1e14 <= 55:
        s = 2
    # VISA
    if ccn // 1e12 == 4 or ccn // 1e15 == 4:
        s = 4

    # uses Luhn's algorithm to dtermien if a card number is real
    if l % 2 == 0:
        for i in range((l // 2)):
            tempsum = 0;
            tempsum += (((ccn % (10**(i*2 + 2))) // (10**(i*2 + 1)))*2)
            sum1 += ((tempsum // 10) + (tempsum % 10))
            sum2 += (ccn % 10**(i*2 + 3) // (10**(i*2 + 2)))
            total_sum = sum1 + sum2
    is_valid = (total_sum) % 10 == 0

    # prints credit card type based on parameters
    if is_valid and l == 15 and s == 1:
        print("AMEX\n")
    elif is_valid and l == 16 and s == 2:
        print("MASTERCARD\n");
    elif is_valid and l == 13 or l == 16 and s == 4:
        print("VISA\n");
    else:
        print("INVALID\n");
main()