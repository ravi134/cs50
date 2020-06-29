// Creates a version of the figure below based on users input of a number 1-8
//        #  #
//       ##  ##
//      ###  ###
//     ####  ####
//    #####  #####
//   ######  ######
//  #######  #######
// ########  ########
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declare integer n
    int n;
    // asks the user for a height between 1 and 8
    do
    {
        n = get_int("Pyramid Height: ");
    }
    while (n < 1 || n > 8);

    // Main loop that prints the overall pyramid
    for (int height = 0; height < n; height++)
    {
        // Prints the spaces for the current row of the pyramid
        for (int spaces = 0; spaces < n - height - 1; spaces++)
            printf(" ");

        // Prints the #'s for the current row of the pyramid
        for (int shape = 0; shape <= height; shape++)
           printf("#");

        // Prints the two spaces in the middle of the pyramid
        printf("  ");

        // Prints the second set of #'s
        for (int shape = 0; shape <= height; shape++)
            printf("#");

        // Goes to the next line of the pyramid
        printf("\n");
    }
}