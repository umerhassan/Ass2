/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    char tweet[1024]={"lamb"};
      char value[10];
    char *eptr;
    long result,result2;
    int even=0;
    for(int i = 0; i<strlen(tweet);i++){
        int ascii = (int)tweet[i];
         printf("Ascii %x\n",ascii);
        char hex[5];
        
        sprintf(hex, "%x", ascii);
        if((even%2)==0)
        {
            
            hex[2]=hex[3]='0';
            hex[4]='\0';
        }
        else
        {
            char temp1=hex[0];
            char temp2=hex[1];
            hex[0]=hex[1]='0';
            hex[2]=temp1;
            hex[3]=temp2;
            hex[4]='\0';
            
        }
        even++;
        strcpy(value, hex);
        result = strtol(value, &eptr, 16);
        result2=result2+result;
        printf("%lx",result2);
        printf("\n");
    }
    long result3=0xffff-result2;
    printf("%lx",result3);

    return 0;
}
