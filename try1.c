#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
  
void compareFiles(FILE *fp1, FILE *fp2) 
{ 
   
    char ch1 = getc(fp1); 
    char ch2 = getc(fp2); 
    int error = 0, pos = 0, line = 1; 
   
  while (ch1 != EOF && ch2 != EOF) 
    { 
        pos++; 
    if (ch1 == '\n' && ch2 == '\n') 
        { 
            line++; 
            pos = 0; 
        } 
  
      if (ch1 != ch2) 
        { 
            error++; 
           
            printf("Line Number Of sensor in which deflection in found : %d \tError"
               " Position of incorrect data : %d \n", line, pos); 
        } 
  
        
        ch1 = getc(fp1); 
        ch2 = getc(fp2); 
    } 
            printf("[+] File send by client recieved... \n");
            printf("[*] Checking for error inside file \n");
            printf("Total Errors in the file transfered by Client : %d\t\n", error); 
            printf("[-] Fault connection client request rejected");
} 
 int main() 
{ 
    // opening both file in read only mode  FILE *fp1 = fopen("all_in_one_labeled.csv", "r"); 
    FILE *fp2 = fopen("malicious.csv", "r"); 
FILE *fp1 =fopen("all_in_one_labeled.csv","r");
  
    if (fp1 == NULL || fp2 == NULL) 
    { 
       printf("Error : Files Send by Client not open"); 
       printf("Client Not Authenticated[Request Rejected]");
       exit(0); 
    } 
 else{
printf("File Matches originl file\n");
printf("Client Authenticated[Request accepted]");
} 
    compareFiles(fp1, fp2); 
   
    fclose(fp1); 
    fclose(fp2); 
    return 0; 
} 

