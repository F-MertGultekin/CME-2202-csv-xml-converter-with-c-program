#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <locale.h>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>IMPORTANT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//arguments must be ordered like assignment folder  
    
     //argv[1];//inpt file
     //argv[2];//outputfile
     //argv[3];// -seperator
     //argv[4];//sepNum
     //argv[5];//-opsys
     //argv[6];//opsysNum
     //argv[7];//-h help

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>IMPORTANT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void readCsv(char *inputFile,char *outputFile,char *sepNum,char *opsysNum);
void split(char input[512],int line,FILE *ptr,char *delim);
void rowSeparator(char *Element,int rowCounter,int lineCounter,FILE *ptr);
void removeChar(char *str, char garbage);
int delimiterCounter(char *input);
void CrLfRemove(char *input,char *opsysNum);
char *DetectDelim(char *sepNum);

int main(int argc, char *argv[])
{	
    printf("Please enter command\n");
    printf("To select seperator please write => seperator <=\n");
    printf("To select operation system please write => opsys <=\n");
    printf("To print information to screen about how other arguments can be used please write =====> h <=====\n");
    printf("To Exit => exit <=\n");
    
     char inputFile[20];
     strcpy(inputFile,argv[1]);
     char outputFile[20];
     strcpy(outputFile,argv[2]);
     char sepNum[20];
     strcpy(sepNum,argv[4]);
     char opsysNum[20];
     strcpy(opsysNum,argv[6]);
     
    


    if(argv[7]!=NULL)//helper 
    {
        printf("To select seperator (1=comma, 2=tab, 3=semicolon)\n");
        printf("To select operation system (1=windows, 2=linux, 3=macos)\n");
    }
    readCsv(inputFile,outputFile, sepNum, opsysNum);
	return 0;

}
void readCsv(char *inputFile,char *outputFile,char *sepNum,char *opsysNum)
{

FILE *pToFile = fopen(inputFile,"r");
	int line = 0;
	char input[512];
	FILE *ptr = fopen(outputFile,"w");


    setlocale(LC_ALL, "en_US.UTF-8");//to encode utf8

    char root[12]="<contacts>\n";//root node

    fputs(root,ptr);
    char delim[3];
    strcpy(delim,DetectDelim(sepNum));

    //line by line reading
	while( fgets( input, 512, pToFile )) {
		line++;
		
        CrLfRemove(input,opsysNum);//deletes carriage rturn and line feed characters
        
        split(input,line,ptr,delim) ;//split up to delim
	}

	char rootClose[12]="</contacts>";//root close
    fputs(rootClose,ptr);
	
	fclose(ptr);
	fclose(pToFile);
	
}
void split(char input[512],int line,FILE *ptr,char *delim)
{  
    char *found;
    int rowCounter=0;
    while( (found = strsep(&input,delim)) != NULL )
    {
        printf("%s\n",found);
        rowSeparator(found,rowCounter,line,ptr);
        rowCounter++;
    }   
}
//after split operation every single element is adding to xml up to row number
 void rowSeparator(char *Element,int rowCounter,int lineCounter,FILE *ptr)
{
    
    switch (rowCounter)
    {
    case 0:;
        char rowId[15]="    <row id='";
        fputs(rowId,ptr);
        fprintf (ptr, "%d",lineCounter);
        char rowIdComp[15]="'>\n";
        fputs(rowIdComp,ptr);
        
        char firstName[21]="        <first_name>";
        fputs(firstName,ptr);
        fprintf (ptr, "%s",Element);
        char firstNameClose[22]="</first_name>\n";
        fputs(firstNameClose,ptr);
        break;
    case 1:;
        char LastName[20]="        <last_name>";
        fputs(LastName,ptr);
        fprintf (ptr, "%s",Element);
        char lastNameClose[15]="</last_name>\n";
        fputs(lastNameClose,ptr);
        break;
    case 2:;
        char email[16]="        <email>";
        fputs(email,ptr);
        fprintf (ptr, "%s",Element);
        char emailclose[15]="</email>\n";
        fputs(emailclose,ptr);
        break;
    case 3:;
        
        char phone_number[22]="        <phone_number>";
        fputs(phone_number,ptr);
        fprintf (ptr, "%s",Element);
        char phone_numberclose[20]="</phone_number>\n";
        fputs(phone_numberclose,ptr);

        break;
    case 4:;
        
        char address[18]="        <address>";
        fputs(address,ptr);
        fprintf(ptr, "%s",Element);
        char addressclose[12]="</address>\n";
        fprintf(ptr,"%s",addressclose);
        //fputs(addressclose,ptr);
        char rowIdClose[15]="    </row>\n";
        fputs(rowIdClose,ptr);

        break;
    }
   
}
//this method removes LF or CR  or both
 void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

// this function removes up to operaion system
void CrLfRemove(char *input,char *opsysNum)
{   
    if(strcmp(opsysNum,"1")==0) //for windows deleting carriage return and line feed characters
    {   
        char garbage2='\r';
        removeChar(input,garbage2);

        char garbage ='\n';
        removeChar(input,garbage);
    }
    if(strcmp(opsysNum,"2")==0)//for Linux deleting line feed character
    {
        char garbage ='\n';
        removeChar(input,garbage);
    }
    if(strcmp(opsysNum,"3")==0)//for MacOs system deleting Carriage return
    {
        char garbage2='\r';
        removeChar(input,garbage2);
    }

} // this function return selected delimeter
char *DetectDelim(char *sepNum)
{
    if(strcmp(sepNum,"1")==0)
    {
        return ",";
    }
    if(strcmp(sepNum,"2")==0)
    {
        return "\t";
     
    }
    if(strcmp(sepNum,"3")==0)
    {
        return ";";
    
    }
}





    