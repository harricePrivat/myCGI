#ifndef __CGI__
#define __CGI__
typedef struct{
	char mois[20];
	char jour[20];
	char heure[30];
	char decri[20];
	char user[50];
} log;

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

char* takeDay(int day){
    int x=day%7;
    if(x==0) return "Sabotsy";
    if(x==1) return "Alahady";
    if(x==2) return "Alatsinainy";
    if(x==3) return "Talata";
    if(x==4) return "Alarobia";
    if(x==5) return "Alakamisy";
    if(x==6) return "Zoma";
}
int next=0;
#endif