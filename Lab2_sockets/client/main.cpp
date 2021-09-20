#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <parsing.h>

#define BUFSIZE 4096  /* block transfer size */
#define ADDRSIZE 128 /* addres size*/

using namespace std;

int main(int argc, char **argv)
{
  int c, s, bytes;
  char buf[BUFSIZE];  /* buffer for incoming file */
  struct hostent *h;  /* info about server */
  struct sockaddr_in channel; /* holds IP address */
  FILE *arquivo;

  if (argc != 2){printf("Usage: client http://<HOST>:<PORT>/<FILE>\n"); exit(-1);}


  char host[ADDRSIZE];
  long int port;
  char  file[ADDRSIZE];
  char nomeArq[ADDRSIZE];

  separarURL(argv[1],host,port,file,nomeArq);  
  
  h = gethostbyname(host); /* look up host’s IP address */ 
  if (!h) {printf("gethostbyname failed to locate %s\n", host); exit(-1);}
  
  //socket()
  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (s <0) {printf("socket call failed\n"); exit(-1);} 
  memset(&channel, 0, sizeof(channel));
  //definindo address family
  channel.sin_family= AF_INET;
  memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
  //padronizando Bigendian
  channel.sin_port= htons(port);

  //connect()
  c = connect(s, (struct sockaddr *) &channel, sizeof(channel));
  if (c < 0) {printf("connect failed"); exit(-1);}
  else printf("Conectado\n");
  
  /* Connection is now established. Send file name including 0 byte at end. */
  
  /* Go get the file and write it to standard output.*/
    
  // Formulando cabeçalho para requisição
  char getReq[BUFSIZE]  ;  
  cabecalho(getReq,file, host);

  printf("Solicitando arquivo %s\n",file );
  write(s,getReq,strlen(getReq)+1);
  
  printf("Aguardando leitura...\n");
  while (1) {    
    bytes = read(s, buf, BUFSIZE); /* read from socket */
    if(bytes <= 0) break; /* check for end of file */    

    printf("Dados Recebidos, escrevendo cabeçalho na tela:\n\n");
    char respHeader[BUFSIZE],resp[BUFSIZE];
    int sizeHeader,sizeResp;
    long int status;
    status = separarResp(buf,respHeader,resp,sizeHeader,sizeResp);

    write(1, respHeader, sizeHeader);  /* write to standard output */
    
    if(status == 200)
    {
      printf("\n\nStatus 200 OK\nGravando arquivo em %s.\n",nomeArq);
      cout<< "\nEscrevendo conteudo do arquivo na tela:\n";
      write(1, resp, sizeResp);  /* write to standard output */      
      arquivo = fopen(nomeArq,"w");
      fputs(resp,arquivo);
      fclose(arquivo);
    }
    else
    {
      printf("\n\nStatus %ld, arquivos não serao gravados.\n",status );
      cout<< "\nEscrevendo conteudo do arquivo na tela:\n";
      write(1, resp, sizeResp);
    } 
    //cout<< "\nDados Recebidos, escrevendo resposta:\n\n";    
    
    
  }
  printf("\nEncerrando.\n");
 
}
