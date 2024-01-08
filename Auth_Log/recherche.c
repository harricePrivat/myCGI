#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dateMG.h"

/*typedef struct{
	char mois[20];
	char jour[20];
	char heure[30];
	char decri[20];
	char user[50];
} Session;

int count(FILE* file){
   file=fopen("/var/log/auth.log","r");
    int i=0;
    char ligne[500];
    while(fgets(ligne,499,file)!=NULL){
    if(strstr(ligne,"session opened") || strstr(ligne,"session closed") )
     i++;
    }
    return i;
}*/
int main(){
	int button=1;
	//FILE * file = popen("tail -100 /var/log/auth.log","r");
    FILE*fic=fopen("log.txt","r");
    char redirection[5];
    fgets(redirection,4,fic);
    FILE* file=fopen("/var/log/auth.log","r");
    //if(file ==NULL || fic==NULL) exit(1);
    //fputs("Bonjour",fic);
    log* s = malloc((count(file)+5)*sizeof(log));
	char ligne[500];
	int i=0;
    printf("Context-Type: text/html\n\n");
    printf("<!DOCTYPE HTML>\n");
printf("<HTML>\n");
    printf("<HEAD>\n");
        printf("<TITLE>Authentification</TITLE>\n");
        printf("<style>");
        printf("input{align=\"center\"}");
        printf("</style>");
    printf("</HEAD>\n");
    printf("<BODY BGCOLOR=\"#FFEECC\" align=\"center\">\n");
       if(atoi(redirection)!=1){
        printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/myCGI/myCGI/log.html\"");
        printf("</script>");
       }
        printf("<H1>Recherche un utilisateur par son Nom</H1>");	
        printf("<FORM ACTION=\"auth.cgi\" METHOD=\"GET\" >\n");
        printf("<INPUT TYPE=\"text\" REQUIRED NAME=\"nameUser\" PLACEHOLDER=\"Nom de l'utilisateur\"/>\n");
        printf("<INPUT TYPE=\"submit\" VALUE=\"recherche\" NAME=\"button\"/>\n");
    printf("</FORM>\n");
    printf("</BR>");
    printf("<table border=2 align=\"center\" >\n");
	printf("<tr>\n");
    printf("<td>ID</td>");
	printf("<td>Date</td>\n");
	printf("<td>Session</td>\n");
	char* query=getenv("QUERY_STRING");
	char nameButton[3];
	if(query==NULL) exit(1);
	sscanf(query,"button=%[^&]",nameButton);	
	button=atoi(nameButton);
    printf("<td>Utilisateur</td>\n");
	printf("</tr>\n");
    int x=(count(file)/10);
    //if(strcmp(nameButton,"NEXT")==0 && next<count(file)) next+=10;
    //if(strcmp(nameButton,"PREVIOUS" )==0 && next<10) next+=10;

    printf("<FORM ACTION=\"recherche.cgi\" METHOD=\"GET\" >\n");
    for(int i=0;i<x;i++){
    printf("<INPUT TYPE=\"submit\" VALUE=\"%d\" NAME=\"button\"/>\n",i+1);
    }
    printf("</FORM>");
    while(fgets(ligne,500,file)!=NULL){
		if(strstr(ligne,"session opened") || strstr(ligne,"session closed") ){
			sscanf(ligne,"%[^ ] %[^ ] %[^ ] %*s %*s %*s %*s %[^ ] %*s %*s %s\n",s[i].mois,s[i].jour,s[i].heure,s[i].decri,s[i].user);
			//printf("%s %s %s %s %s\n",s[i].mois,s[i].jour,s[i].heure,s[i].decri,s[i].user);
			/*printf("<tr>\n");
			printf("<td>%s %s %s</td>\n",s[i].mois,s[i].jour,s[i].heure);
			printf("<td>%s</td>\n",s[i].decri);		
			printf("<td><a href=\"http://www.brice.mg/myCGI/myCGI/auth.cgi?nameUser=%s&button=recherche\">%s<a></td>\n",s[i].user,s[i].user);
			printf("</tr>\n");*/
			i++;
         //   if(i==10*button) break;
		}
    }
    for(int i=(10*button)-10;i<(10*button);i++){
        if(s[i].mois!=NULL){
        printf("<tr>\n");
            printf("<td>%d</td>",i+1);
			printf("<td>%s %s %s %s</td>\n",takeDay(atoi(s[i].jour)),s[i].mois,s[i].jour,s[i].heure);
			printf("<td>%s</td>\n",s[i].decri);		
			printf("<td><a href=\"http://www.brice.mg/myCGI/myCGI/auth.cgi?nameUser=%s&button=recherche\">%s<a></td>\n",s[i].user,s[i].user);
			printf("</tr>\n");
    }
    }
    printf("</FORM>");
    printf("<FORM ACTION=\"auth.cgi\" METHOD=\"GET\">");
	printf("<INPUT type=\"submit\" value=\"deconnexion\" name=\"nameUser\"/>");
	printf("</FORM>");
    printf("</table>");
    printf("</BODY>\n");
    fclose(file);
    //fclose(fic);
printf("</HTML>\n");

    return 0;
}
