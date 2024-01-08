#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "confirmation.h"

int main(){
    char siteDispo[50][50];
    char siteEnable[50][50];
    FILE* fichier=fopen("/etc/hosts","a+");
    FILE* file=fopen("/etc/apache2/sites-available/monSite.conf","w");
    FILE* fic=fopen("/home/mit/siteBrice//exempleSite.conf","r");
   if(fic==NULL || file==NULL || fichier==NULL) exit(1);
    char* query=getenv("QUERY_STRING");
    //char query[50]="nom=brice&dns=www.brice.mg";
  char nomSite[30],dns[30],documentRoot[50],execCGI[10],followSymLinks[10],line[500];
    char* site=malloc(75);
    sscanf(query,"nom=%[^&]&documentRoot=%[^&]&dns=%[^\n]",nomSite,documentRoot,dns);
   site=addSite(nomSite);
   char cmd[50]="sudo a2ensite ";
   strcat(cmd,nomSite);
   char cmd1[50]="sudo mkdir ";
   char cmd2[50]="sudo cp /home/mit/siteBrice/index.html ";
   // strcat(nomSite,".conf");
    strcat(cmd1,DocumentRoot(documentRoot));
    strcat(cmd2,DocumentRoot(documentRoot));
    printf("Content-type: text/html\n\n");
    printf("<HTML>\n");
    printf("<HEAD>\n");
    printf("<TITLE>CREE SITE</TITLE>");
    printf("</HEAD>\n");
    printf("<BODY>\n");
  FILE* fp=popen("ls /etc/apache2/sites-available","r");
  int j=0;
  while(fgets(line,500,fp)!=NULL){
      strcpy(siteDispo[j],line);
      j++;
  }
  for(int i=0;i<j;i++){
    printf("%s</BR>",siteDispo[i]);
  }

printf("</BR></BR>");
  FILE* fe=popen("ls /etc/apache2/sites-enabled","r");
  int k=0;
  while(fgets(line,500,fe)!=NULL){
      strcpy(siteEnable[k],line);
      k++;
  }
  for(int i=0;i<k;i++){
    printf("%s</BR>",siteEnable[i]);
  }
  /*  printf("<P>Bonjour</P>\n");
    printf("<P>%s</P>\n",site);
   printf("<P>%s</P>\n",dns);
   printf("<P>%s</P>\n",cmd);
   printf("<P>%s</P>\n",cmd1);
   printf("<P>%s</P>\n",cmd2);*/
   popen(cmd1,"w");
   popen(cmd2,"w");
   fprintf(fichier,"\n127.0.0.1       %s\n",dns);
    int i=0;
    while(fgets(line,500,fic)!=NULL){
        fputs(line,file);
        if(i==8){
            fprintf(file,"\n\tServerName %s\n",dns);
            fprintf(file,"\tDocumentRoot %s\n",DocumentRoot(documentRoot));
            fprintf(file,"\tServerAdmin webmaster@localhost\n");
            fprintf(file,"\t<Directory %s>\n",DocumentRoot(documentRoot));
        } 
        i++;
    }
    
    if(rename("/etc/apache2/sites-available/monSite.conf",site)==0){
        popen(cmd,"w");
        popen("sudo systemctl reload apache2","w");
      printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/Creator/accueil.html\"");
        printf("</script>");  
    //printf("Nommage succes");
    }
    /**/
    printf("</BODY>\n");
    printf("</HTML>\n");
    fclose(fic);
  fclose(file); 
   pclose(fp);
   pclose(fe);
   fclose(fichier);
    return 0;
}