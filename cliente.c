
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char*argv[]) {
    char buffer[50];
    memset(buffer, 0, 50);
    int n = open("/tmp/Serv", O_WRONLY);
   
    
    write(1, "1- Agregar\n2-Incrementar\n", 25);
    read(0, buffer, 2);

    //AGREGAR  int agregar(char* prefixo[], unsigned nivel, char* path)
    if (buffer[0] == '1') {
        char* p[3];
        int i = 1;
        char* ficheiro;


        write(1, "Nível 0, 1 ou 2:\n", 17);
        read(0, buffer, 2);
        int nivel = atoi(&buffer[0]);
        char nivel2 = buffer[0];

        if(nivel>=0){
                write(1, "Digite o Distrito:\n", 19);
                read(0, buffer, 30);
                buffer[strlen(buffer)-1]='\0';
                p[0]=strdup(buffer); memset(buffer, 0, 50);

                if (nivel>=1){
                    write(1, "Digite o Concelho:\n", 19);
                    read(0, buffer, 30);
                    buffer[strlen(buffer)-1]='\0';
                    p[1]=strdup(buffer); memset(buffer, 0, 50);


                    if (nivel==2){
                        write(1, "Digite a Freguesia:\n", 20);
                        read(0, buffer, 30);
                        buffer[strlen(buffer)-1]='\0';
                        p[2]=strdup(buffer); memset(buffer, 0, 50);
            }}}

            else printf("ERRO NIVEL");


            write(1, "Digite o nome do ficheiro:\n", 27);
            read(0, buffer, 30);
            ficheiro = strdup(buffer);
            //mandar para o pipe -> n
            write(n,p[0],sizeof(char)*strlen(p[0]));
            write(n,":",1);
            write(n,"a:",2);
            write(n,&nivel2,1);
            write(n,":",1);


            
            while (i <= nivel) {
                write(n, p[i],sizeof(char)*strlen(p[i]));
                write(n, ":", 1);
                i++;
            }
            ficheiro[strlen(ficheiro)-1] = '\0';
            write(n,ficheiro,sizeof(char)*strlen(ficheiro));
            
            write(n, "#", 1);
        }
    




    //INCREMENTAR int incrementar(char* nome[], unsigned valor)
    else if (buffer[0] == '2') {
        char* p[3];
        char* ficheiro;

        
            write(1, "Digite o Distrito:\n", 19);
            read(0, buffer, 30);
            buffer[strlen(buffer)-1]='\0';
            p[0]=strdup(buffer); memset(buffer, 0, 50);

               
            write(1, "Digite o Concelho:\n", 19);
            read(0, buffer, 30);
            buffer[strlen(buffer)-1]='\0';
            p[1]=strdup(buffer); memset(buffer, 0, 50);


                   
            write(1, "Digite a Freguesia:\n", 20);
            read(0, buffer, 30);
            buffer[strlen(buffer)-1]='\0';
            p[2]=strdup(buffer); memset(buffer, 0, 50);


            write(1, "Digite o valor a incrementar:\n", 30);
            read(0, buffer, 30);
            buffer[strlen(buffer)-1]='\0';
            char* valor = strdup(buffer); memset(buffer, 0, 50);
        
           
            
            //mandar para o pipe -> n
            //d:i:c:f:valor:9
            write(n,p[0],sizeof(char)*strlen(p[0]));
            write(n,":",1);
            write(n,"i:",2);
            write(n,p[1],sizeof(char)*strlen(p[1]));
            write(n,":",1);
            write(n,p[2],sizeof(char)*strlen(p[2]));
            write(n,":",1);
            write(n,valor,sizeof(char)*strlen(valor));
           
            write(n, "#", 1);
    }
    

    close(n);
    return 1;
}







