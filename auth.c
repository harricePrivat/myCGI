#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char mois[20];
	char jour[20];
	char heure[30];
	char decri[20];
	char user[50];
} Session;

int main(){
	Session* s = malloc(500*sizeof(Session));
	
	FILE * file = popen("tail -100 /var/log/auth.log","r");
	//FILE* file=fopen("/var/log/auth.log","r");
	char ligne[500];
	int i=0;
	
	printf("Context-Type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
    printf("<html>\n");
		printf("<head>\n");
			printf("<title>Authentification</title>\n");
		printf("</head>\n");
    printf("<body>\n");
	printf("<H1 align=\"center\">Voici le r&eacute;sultat :</H1>");
	printf("<table border=2 align=\"center\">\n");
	printf("<tr>\n");
	printf("<td>Date</td>\n");
	printf("<td>Session</td>\n");
	char* query=getenv("QUERY_STRING");
	char name[20];
	if(query==NULL) exit(1);
	sscanf(query,"nameUser=%[^&]",name);
	//printf("<p>%s</p>",name);		
	printf("<td>Utilisateur</td>\n");
	printf("</tr>\n");
	while(fgets(ligne,500,file)!=NULL){
			sscanf(ligne,"%[^ ] %[^ ] %[^ ] %*s %*s %*s %*s %[^ ] %*s %*s %s\n",s[i].mois,s[i].jour,s[i].heure,s[i].decri,s[i].user);
			if((strstr(ligne,"session opened") && strstr(ligne,name) ) || (strstr(ligne,"session closed") && strstr(ligne,name))){
			printf("<tr>\n");
			printf("<td>%s %s %s</td>\n",s[i].mois,s[i].jour,s[i].heure);
			printf("<td>%s</td>\n",s[i].decri);		
			printf("<td>%s</td>\n",s[i].user);
			printf("</tr>\n");
			i++;
		}
	}
	printf("</table>\n");

	printf("</body>\n");
    printf("</html>\n");
	pclose(file);
	return 0;
}
