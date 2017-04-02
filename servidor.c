#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "struct.h"
char*dist[32];
int pipek[32][2];
int n;
Registo *loc;

void novoReg() {
    loc = (Registo*) malloc(sizeof (Registo));
    loc->root = NULL;


}
int fAct(char*s) {
    int i=0, f=-1;
    while (i<n && f==-1) {
        if ((strcmp(dist[i], s)) == 0) {
        f=i;}
        else i++;
    }
return f;
}
void printEstruturas() {

    Distrito *a = loc->root;
    while (a != NULL) {
        printf("Distrito:%s: \n", a->d);
        Concelho *b = a->c;
        while (b != NULL) {
            printf("concelho : %s:\n", b->concelho);
            Freguesia *c = b->f;

            while (c != NULL) {
                printf("freg : %s", c->freguesia);
                c = c->next;
            }
            b = b->next;
        }


        a = a->next;
    }


}

void inserir(char *nome[],int val){
    int f1 =0,f2=0,f3=0;
    
    Distrito *d = (Distrito*) malloc(sizeof (Distrito));
 Distrito *a = loc->root;
    while (a != NULL && !f1) {
     if (!(strcmp(a->d, nome[0]))){
         a->casos += val;
         f1  = 1;
      Concelho *b = a->c;
     while (b != NULL && !f2) {
         if (!(strcmp(b->concelho, nome[1]))){
             b->casos+=val;
             f2 =1;
             Freguesia *c = b->f;
             while(c!=NULL && !f3){
                  if (!(strcmp(c->freguesia , nome[2]))){
                      f3 =1;
                      c->casos+=val;
                  }else
                  c= c->next;
             } if (c == NULL &&!f3) {
                     
                        Freguesia *nf = (Freguesia*) malloc(sizeof (Freguesia));
                        nf->freguesia = strdup(nome[2]);

                        nf->casos = val;
                        nf->next = b->f;
                        b->f = nf;


                    }
         
         }else
       b = b->next;  
     }  if (b == NULL && !f2) {

                Concelho *nc = (Concelho*) malloc(sizeof (Concelho));
                nc->concelho = strdup(nome[1]);
                    Freguesia *nf = (Freguesia*) malloc(sizeof (Freguesia));
                    nf->freguesia = strdup(nome[2]);
                    nc->f = nf;
                    nf->next = NULL;
                    nf->casos = val;
               

                nc->casos = val;


                nc->next = a->c;
                a->c = nc;

            }
     
     
     
     }else  a = a->next;
    
    
    
   
    } if (a == NULL && !f1 ){ 
       
        d->d = strdup(nome[0]);
        d->casos = val;


        Concelho *nc = (Concelho*) malloc(sizeof (Concelho));
        nc->concelho = strdup(nome[1]);
        
            Freguesia *nf = (Freguesia*) malloc(sizeof (Freguesia));
            nf->freguesia = strdup(nome[2]);
            nc->f = nf;
            nf->next = NULL;
            nf->casos = val;
       
        nc->casos = val;

        nc->next = NULL;
        d->c = nc;
        d->next = loc->root;
        loc->root = d;
    } else free(d);
 ///printEstruturas();

}





void save(char *nome[],char*path,int lvl){
 int f1 =0,f2=0,f3=0;
 Distrito *a = loc->root;char l[50];
 char casos;
 memset(&l,0,50);
 strcat(l,path) ;
 strcat(l,".txt"); 
int e = open(l,O_WRONLY |  O_CREAT|O_TRUNC,0666);
     while (a != NULL && !f1) {
     if (!(strcmp(a->d, nome[0]))){
        
         f1  = 1;
         
    if(lvl>=1){  
        
        Concelho *b = a->c;
     while (b != NULL && !f2) {
         if (!(strcmp(b->concelho, nome[1]))){
                
                   
             f2 =1;
             
             if(lvl==2){
             Freguesia *c = b->f;
             while(c!=NULL && !f3){
                  if (!(strcmp(c->freguesia , nome[2]))){
                      f3 =1;
                      char novo[50];
                 memset(&novo,0,50);
              
                  casos = c->casos ;
                 snprintf ( novo, 50, "%s:%s:%s:%d",nome[0], nome[1],nome[2],casos );
            
            
          
               write(e,novo,strlen(novo)*sizeof(char));  
                  write(e,"\n",1);   
                  }else
                  c= c->next;
             } 
             }else{
                 char novo[50];
                 memset(&novo,0,50);
              Freguesia *c = b->f;
             while(c!=NULL && !f3){
                 
                 
                 memset(&novo,0,50);
              
                  casos = c->casos ;
                 snprintf ( novo, 50, "%s:%s:%s:%d",a->d,b->concelho,c->freguesia,casos );
             write(e,novo,strlen(novo)*sizeof(char)); 
              write(e,"\n",1);  
             c=c->next;
                 }  
             }
         }else
             
       b = b->next;  
     } 
     
     
    }else {
        char novo[50];
    
Concelho *b = a->c;
     while (b != NULL ) {
        
                
                   
            
             
           
             Freguesia *c = b->f;
             while(c!=NULL && !f3){
                 
                 
                 memset(&novo,0,50);
              
                  casos = c->casos ;
                 snprintf ( novo, 50, "%s:%s:%s:%d",a->d,b->concelho,c->freguesia,casos );
             write(e,novo,strlen(novo)*sizeof(char)); 
              write(e,"\n",1);  
             c=c->next;
                 }
          
              
                    
               b = b->next;  
             } 
             
     
        
        
    
    
    
    }
     }else  a = a->next;



     } 

close(e);
}

int incrementar(char* nome[], unsigned  valor){
  
    printf("VOU INCREMENTAR a %s-%d-\n",nome[0],valor);
   
    inserir(nome,valor);
    save(nome,nome[0],-1);
    return 1;
}


int agregar(char* prefixo[], unsigned nivel, char* path){
    //fazer
  printf("VOU AGREGAR  a%s-%d-%s\n",prefixo[0],nivel,path);
  
  save(prefixo,path,nivel);
    return 1;
}

//li = :nivel(:c:f):ficheiro:9
void parseA(int g, char* distrito){
    int j=0;
    char nivel;
    unsigned nn;
    char buffer[50]; memset(buffer, 0, 50);
    char conc[15]; memset(conc, 0, 15);
    char freg[15]; memset(freg, 0, 15);
    char fic[15]; memset(fic, 0, 15);
    int n=0;

  if((     read(pipek[g][0], buffer, 1))!=0){   
            //NIVEL
             
                
                
                
                nivel = buffer[0];
                
                n=1; j=0;
                read(pipek[g][0], buffer, 1);
            
     nn = nivel -'0'; 
     
   
            if(nn>=1){
               
                //CONCELHO
                if(n==1){ 
                
                
                    if(buffer[0]==':') {
                  read(pipek[g][0], buffer, 1);   }
                    conc[j] = buffer[0];
                    j++;

                    while (buffer[0]!=':'){
                        read(pipek[g][0], buffer, 1); 
                         
                        
                        conc[j] = buffer[0];
                        j++;
                    }

                   conc[j-1] = '\0';
                   
                    n=2; j=0;
                   
                }

              
                 //FREGUESIA
                if(n==2 && nn == 2){
                    
                    if(buffer[0]==':')
                   read(pipek[g][0], buffer, 1);
                    freg[j] = buffer[0]; j++;

                    while (buffer[0]!=':'){
                        read(pipek[g][0], buffer, 1);
                        freg[j] = buffer[0];
                        j++;
                    }

                    freg[j-1] = '\0';
                    
                    n=3; j=0;
                }else{n = 3;}
            
            }else{n = 3;}
            //FICHEIRO
            if(n==3){ 
                if(buffer[0]==':') read(pipek[g][0], buffer, 1);
                fic[j] = buffer[0]; j++;

                while (buffer[0]!='#'){
                    read(pipek[g][0], buffer, 1);
                    fic[j] = buffer[0];
                    j++;
                }

                fic[j-1] = '\0';
               
                n=4; j=0;
            }

        
     
    char* nome[3];
    nome[0]=strdup(distrito);
    nome[1]=strdup(conc);
    nome[2]=strdup(freg);
     read(pipek[g][1], buffer, 1);
    
    agregar(nome,nn,fic);
   }else printf("Adeus\n");
   
   
   }


//li == :c:f:valor:#
void parseI(int g,  char* distrito){
    int j=0;
    char nivel;
    
    char buffer[50]; memset(buffer, 0, 50);
    char conc[15]; memset(conc, 0, 15);
    char freg[15]; memset(freg, 0, 15);
    char fic[15]; memset(fic, 0, 15);
    int n=0;

  if((     read(pipek[g][0], buffer, 1))!=0){   
            //NIVEL
       
                
                
                    if(buffer[0]==':') {
                  read(pipek[g][0], buffer, 1);   }
                    conc[j] = buffer[0];
                    j++;

                    while (buffer[0]!=':'){
                        read(pipek[g][0], buffer, 1); 
                        
                        
                        conc[j] = buffer[0];
                        j++;
                    }

                    conc[j-1] = '\0';
                   
                    n=2; j=0;
                   
                }

              
                 //FREGUESIA
               
                    
                    if(buffer[0]==':')
                   read(pipek[g][0], buffer, 1);
                    freg[j] = buffer[0]; j++;

                    while (buffer[0]!=':'){
                        read(pipek[g][0], buffer, 1);
                        freg[j] = buffer[0];
                        j++;
                    }

                    freg[j-1] = '\0';
                    
                    n=3; j=0;
                
            
           
             
                if(buffer[0]==':') read(pipek[g][0], buffer, 1);
                fic[j] = buffer[0]; j++;

                while (buffer[0]!='#'){
                    read(pipek[g][0], buffer, 1);
                    fic[j] = buffer[0];
                    j++;
                }

                fic[j-1] = '\0';
               
                n=atoi(fic);
            

        
    
    char* nome[3];
    nome[0]=strdup(distrito);
    nome[1]=strdup(conc);
    nome[2]=strdup(freg);
     read(pipek[g][1], buffer, 1);
   
   

   
   
   
    incrementar(nome, n);
}


//ler do li e escrever para o g (pipek[g][1])
void existe(int g, int li, char* distrito){
    int fl = 0;
    char buffer[50];
        
        while ((read(li, buffer, 1)) != 0 && !fl) {
            if (buffer[0]=='#') {
                write(pipek[g][1], (&buffer[0]), 1); 
                fl = 1;
            }
            else write(pipek[g][1],(&buffer[0]), 1);
        }
}



void naoExiste( int li, char* distrito){
    char buffer[15];
    dist[n] = strdup(distrito);
    printf("distrito NOVO:%s\n",dist[n]);
    pipe(pipek[n]);
    n++;
    

    if(!fork()) {
        char *Dist = strdup(distrito);
        close(pipek[n-1][1]);
        
            while(1){
                if((read(pipek[n-1][0],buffer,2))!=0){
                   
                    if (buffer[0]=='a') {
                        
                        
                       parseA(n-1, distrito);
                  
                    }
                    else if (buffer[0]=='i') {parseI(n-1, distrito);
                         
                    }
                      
                }
            }
    }

    else {
        close(pipek[n-1][0]);
        int fl = 0;
        while ((read(li, buffer, 1)) != 0&& !fl) {
            if (buffer[0]=='#') {
                write(pipek[n - 1][1], (&buffer[0]), 1);
                fl = 1;
            }

            else write(pipek[n - 1][1], (&buffer[0]), 1); 
        }
    }
}




int main() {
    char buffer[50], pref[15];
    int j=0, i = 0, f = 0, r, nivel; n = 0;
    novoReg();
    mkfifo("/tmp/Serv", 0666);
    int li = open("/tmp/Serv", O_RDONLY);

    while (1) {
        if ((r = read(li, buffer, 1)) != 0) {
            j=0; memset(pref, 0, 15);
            pref[j] = buffer[0]; j++;
         
                while (buffer[0] != ':'){
                    read(li, buffer, 1);
                    pref[j] = buffer[0];
                    j++;
                }

                pref[j-1] = '\0';
               
                int g = fAct(pref);
                if (g != -1) existe(g, li, pref);
                else naoExiste( li, pref);
        }
    }

    return (EXIT_SUCCESS);
}

