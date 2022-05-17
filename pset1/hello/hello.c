#include <stdio.h>
#include <cs50.h>

int main(void)
{ 
//Ask for name
    string answer = get_string("what's your name?\n");
    
//Print answer
    printf("hello, %s\n", answer);
}