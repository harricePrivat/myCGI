#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "confirmation.h"

int main(){
    char siteActiver[50][50];
    char line[500];
    printf("Content-type: text/html\n\n");
    printf("<HTML>\n");
    printf("<HEAD>\n");
    printf("<TITLE>CREE SITE</TITLE>");
    printf("</HEAD>\n");
    printf("<BODY>\n");
    printf("<H1><U>Les sites enable</U></H1>");
    FILE* fp=popen("ls /etc/apache2/sites-enabled","r");
    int j=0;
  while(fgets(line,500,fp)!=NULL){
      if(strcmp(line,"exempleSite.conf")==0){
            strcpy(siteActiver[j],"isa");
      }
      else{
        strcpy(siteActiver[j],line);
      }
      j++;
  }
  for(int i=0;i<j;i++){
    printf("<p>%s</p>",siteActiver[i]);
  }
    printf("</BODY>\n");
    return 0;
}