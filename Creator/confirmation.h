#ifndef __CONFIRMATION__
#define __CONFIRMATION__

char* addSite(char site[]){
    char*addsite=malloc(50);
    sprintf(addsite,"/etc/apache2/sites-available/%s.conf",site);
    return addsite;
}

char* DocumentRoot(char* documentRoot){
    char* finally=malloc(strlen(documentRoot));
    int k=0;
    for(int i=0;i<strlen(documentRoot);i++){
        if(documentRoot[i]=='%'){
        finally[k]='/';
        i=i+2;
        finally[k+1]=documentRoot[i];
        }else{
            finally[k]=documentRoot[i];
        }
            
         
    k++;
    }
    return finally;
}
typedef struct Options{
    bool execCGI;
    bool followSymLinks;
}Options;

#endif