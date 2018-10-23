
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	FILE *fp;
	char const* const writeFile = "bbc.txt";
	char const* const fileName = "abc.txt";
    FILE* file = fopen(fileName, "r"); /* should check the result */
	fp = fopen(writeFile,"w+");
    char tweet[1024000]={"lak"};
	
    while (fgets(tweet, sizeof(tweet), file)) {
       
        printf("%s", tweet); 
		
		if(strlen(tweet)<10)
		{
			
			char value[10000];
			
			char *eptr;
			long result,result2=0;
			int even=0;
			int l=strlen(tweet)-2;
			fprintf(fp, "%s", tweet);
			
			for(int i = 0; i<l;i++){
				int ascii = (int)tweet[i];
			//	printf("Ascii for %c is %x\n",(int)tweet[i],ascii);
				char hex[15];
			
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
				fprintf(fp, " Hexvalue: %s\n", hex);
				strcpy(value, hex);
				result = strtol(value, &eptr, 16);
				if((result2+result)<=0xffff){
					result2=result2+result;
				}else{
					
				}
				result2=result2+result;
				fprintf(fp, "     Result2: %lx\n", result2);

				printf("Result2: %lx",result2);
			//	printf("\n");
			//	printf("i is %d, lenght is %d\n",i,strlen(tweet));
			}
			long result3=0xffff-result2;
			
			fprintf(fp, "\n%lx\n", result3);
			//printf("%lx\n",result3);
		}
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);
	fclose(fp);
   
     
    

    return 0;
}
