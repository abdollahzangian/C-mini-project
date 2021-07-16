#include <stdio.h>
#include <string.h>
void reverse_string(char*, int, int);
int main()
{
    
    char string_array[150];
    printf("Enter the number:");
    scanf("%s", &string_array);
    reverse_string(string_array,0,strlen(string_array)-1);
    printf("\nReversed number is: %s",string_array);
    return 0;

}
 
void reverse_string(char *x, int start, int end)
{
    char ch;
    if (start >=end)
       return;

    ch = *(x+start);
    *(x+start) = *(x+end);
    *(x+end) = ch;

    reverse_string(x, ++start, --end);
}