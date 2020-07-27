//Asks the user fr their name and greets them by printing 'hello, (userinput)'
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Asks user for their name
    string name = get_string("What's your name?\n");

    // Prints hello, (users input)
    printf("hello, %s\n", name);
}
