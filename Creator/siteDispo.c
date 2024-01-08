#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "confirmation.h"

int main(){
    char siteDispo[50][50];
    char line[500];
    printf("Content-type: text/html\n\n");
    printf("<HTML>\n");
    printf("<HEAD>\n");
    printf("<TITLE>CREE SITE</TITLE>");
    printf("</HEAD>\n");
    printf("<BODY>\n");
    FILE* fp=popen("ls /etc/apache2/sites-available","r");
  printf("<H1><U>Les sites disponibles</U></H1>");
  int j=0;
  while(fgets(line,500,fp)!=NULL){
      if(strcmp(line,"exempleSite.conf")==0){
            strcpy(siteDispo[j],"isa");
      }
      else{
        strcpy(siteDispo[j],line);
      }
      j++;
  }
  for(int i=0;i<j;i++){
    printf("<p>%s</p>",siteDispo[i]);
  }
    printf("</BODY>");
    printf("</HTML>");
    pclose(fp);
    return 0;
}