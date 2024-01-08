#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count(char* text,char a);
int main(){
	char user[200];
	FILE* passwd=fopen("/etc/passwd","r");
	if(passwd==NULL)
		exit(1);
		
	printf("Content-type: text/html\n\n");
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>takeUser CGI</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	printf("<H1>Les utilisateurs vivants dans mon PC</H1>\n");
	printf("<TABLE BORDER=1 >\n");
	printf("<TR>\n");
	printf("<TD>Nom de l'utilisateur</TD>\n");
	printf("<TD>Son r&eacute;pertoire d'utilisation</TD>\n");
	printf("</TR>\n");
	while(fgets(user,199,passwd)!=NULL){
		char id[10];
		char name[15],directory[50];
	sscanf(user,"%[^:]:x:%[^:]",name,id);
	char* token=strtok(user,":");
	while(token!=NULL){
		strcpy(directory,token);
		token=strtok(NULL,":");
	}
	if(atoi(id)>=1000 && atoi(id)<60000){	
	printf("<TR>\n");
	printf("<TD>%s</TD>\n",name);
	printf("<TD>%s</TD>",directory);
	printf("</TR>\n");
}
}
	printf("</TABLE>");
	printf("</BODY>\n");
	printf("</HTML>\n");
	fclose(passwd);
	return 0;
}
