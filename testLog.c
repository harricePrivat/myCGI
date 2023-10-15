#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dateMG.h"

int main(){
    FILE* fic=fopen("log.txt","w+");
    FILE* file=fopen("database.csv","r");
    if(file==NULL) exit(1);
    char login[50];
    char mdp[50];
    char* query=getenv("QUERY_STRING");
    sscanf(query,"login=%[^&]&mdp=%[^\n]",login,mdp);
    printf("Context-Type: text/html\n\n");
    printf("<!DOCTYPE HTML>\n");
printf("<HTML>\n");
    printf("<HEAD>\n");
        printf("<TITLE>Authentification</TITLE>\n");
        printf("<meta charset=\"UTF-8\">\n");
    printf("</HEAD>\n");
    printf("<BODY>");
   // printf("<H1>%s</H1>",query);
    char nom[50] ,password[50];
    char line[100];
     while(fgets(line,99,file)!=NULL){  
    fgets(line,99,file);
    sscanf(line,"%[^,],%[^\n]",nom,password);
   /* printf("<H1>%s</H1>",line);
   printf("<H1>%s %s\n<H1>",nom,password);
   printf("<H1>%s %s\n<H1>",login,mdp);*/
    int a=strcmp(login,nom);
    int b= strcmp(mdp,password);
    printf("<H1>%d %d\n<H1>",a,b);
    if(strcmp(login,nom)==0 && strcmp(mdp,password)==0){
        fputc('1',fic);
        printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/myCGI/myCGI/recherche.cgi?button=1\"");
        printf("</script>");
    }
}
       printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/myCGI/myCGI/log.html\"");
        printf("</script>"); 
    
    printf("</BODY>");
    printf("</HTML>");
   // fclose(file);
    return 0;
}