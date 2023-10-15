#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dateMG.h"

int main(){
	log* s = malloc(500*sizeof(log));
	
	FILE * file = popen("tail -100 /var/log/auth.log","r");
	//FILE* file=fopen("/var/log/auth.log","r");
	char ligne[500];
	int i=0;
	FILE*fic=fopen("log.txt","r");
    char redirection[5];
    fgets(redirection,4,fic);
	printf("Context-Type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
    printf("<html>\n");
		printf("<head>\n");
			printf("<title>Authentification</title>\n");
		printf("</head>\n");
    printf("<body BGCOLOR=\"#FFEECC\">\n");
	if(atoi(redirection)!=1){
        printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/myCGI/myCGI/log.html\"");
        printf("</script>");
       }
	   char* query=getenv("QUERY_STRING");
	printf("<H1 align=\"center\">Voici le r&eacute;sultat :</H1>");
	printf("<FORM ACTION=\"auth.cgi\" METHOD=\"GET\">");
	printf("<INPUT type=\"submit\" value=\"retour\" name=\"nameUser\"/>");
	printf("</FORM>");
	printf("<table border=2 align=\"center\">\n");
	printf("<tr>\n");
	printf("<td>ID</td>");
	printf("<td>Date</td>\n");
	printf("<td>Session</td>\n");
	char name[20];
	if(query==NULL) exit(1);
	sscanf(query,"nameUser=%[^&]",name);
	if(strcmp(name,"retour")==0){
		printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/myCGI/myCGI/recherche.cgi?button=1\"");
        printf("</script>"); 
	}
	if(strcmp(name,"deconnexion")==0){
		fic=fopen("log.txt","w");
		printf("<script>");
        printf("window.location.href=\"http://www.brice.mg/myCGI/myCGI/log.html\"");
        printf("</script>"); 
	}
	//printf("<p>%s</p>",name);		
	printf("<td>Utilisateur</td>\n");
	printf("</tr>\n");
	while(fgets(ligne,500,file)!=NULL){
			//sscanf(ligne,"%[^ ] %[^ ] %[^ ] %*s %*s %*s %*s %[^ ] %*s %*s %s\n",s[i].mois,s[i].jour,s[i].heure,s[i].decri,s[i].user);
			if((strstr(ligne,"session opened") && strstr(ligne,name) ) || (strstr(ligne,"session closed") && strstr(ligne,name))){
			sscanf(ligne,"%[^ ] %[^ ] %[^ ] %*s %*s %*s %*s %[^ ] %*s %*s %s\n",s[i].mois,s[i].jour,s[i].heure,s[i].decri,s[i].user);
			printf("<tr>\n");
			printf("<td>%d</td>",i+1);
			printf("<td> %s %s %s %s</td>\n",takeDay(atoi(s[i].jour)),s[i].mois,s[i].jour,s[i].heure);
			printf("<td>%s</td>\n",s[i].decri);		
			printf("<td>%s</td>\n",s[i].user);
			printf("</tr>\n");
			i++;
		}
	}
	/*for(int j=0;j<(i/10);j++){
    printf("<INPUT TYPE=\"submit\" VALUE=\"%d\" NAME=\"button\"/>\n",j+1);
    }
	for(int j=(10*i)-10;j<(10*i);j++){
        printf("<tr>\n");
			printf("<td>%s %s %s %s</td>\n",takeDay(atoi(s[j].jour)),s[j].mois,s[j].jour,s[j].heure);
			printf("<td>%s</td>\n",s[j].decri);		
			printf("<td>%s</td>\n",s[j].user);
			printf("</tr>\n");
    }*/
	printf("</table>\n");
	printf("<FORM ACTION=\"auth.cgi\" METHOD=\"GET\">");
	printf("<INPUT type=\"submit\" value=\"deconnexion\" name=\"nameUser\"/>");
	printf("</FORM>");
	printf("</body>\n");
    printf("</html>\n");
	//fic=fopen("log.txt","w");
	pclose(file);
	return 0;
}
