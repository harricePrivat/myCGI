#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
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
}
int main(){
	int button=1;
	//FILE * file = popen("tail -100 /var/log/auth.log","r");
	FILE* file=fopen("/var/log/auth.log","r");
    Session* s = malloc((count(file)+5)*sizeof(Session));
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
    printf("<BODY align=\"center\">\n");
        printf("<H1>Recherche un utilisateur par son Nom</H1>");	
        printf("<FORM ACTION=\"auth.cgi\" METHOD=\"GET\" >\n");
        printf("<INPUT TYPE=\"text\" NAME=\"nameUser\" PLACEHOLDER=\"Nom de l'utilisateur\"/>\n");
        printf("<INPUT TYPE=\"submit\" VALUE=\"recherche\" NAME=\"button\"/>\n");
    printf("</FORM>\n");
    printf("</BR>");
    printf("<table border=2 align=\"center\" >\n");
	printf("<tr>\n");
	printf("<td>Date</td>\n");
	printf("<td>Session</td>\n");
	char* query=getenv("QUERY_STRING");
	char nameButton[3];
	if(query==NULL) exit(1);
	sscanf(query,"button=%[^&]",nameButton);	
	button=atoi(nameButton);
    printf("<td>Utilisateur</td>\n");
	printf("</tr>\n");
	printf("<FORM ACTION=\"recherche.cgi\" METHOD=\"GET\" >\n");
    int x=(count(file)/10);
   // printf("<H1>%d</H1>",x);
    for(int i=0;i<x;i++){
    printf("<INPUT TYPE=\"submit\" VALUE=\"%d\" NAME=\"button\"/>\n",i+1);
    }
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
        printf("<tr>\n");
			printf("<td>%s %s %s</td>\n",s[i].mois,s[i].jour,s[i].heure);
			printf("<td>%s</td>\n",s[i].decri);		
			printf("<td><a href=\"http://www.brice.mg/myCGI/myCGI/auth.cgi?nameUser=%s&button=recherche\">%s<a></td>\n",s[i].user,s[i].user);
			printf("</tr>\n");
    }
    printf("</FORM>");
    printf("</table>");
    printf("</BODY>\n");
    pclose(file);
printf("</HTML>\n");
}
