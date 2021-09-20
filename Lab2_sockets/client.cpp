/* This page contains a client program that can request a file from the server program
* on the next page. The server responds by sending the whole file.
*/


#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//#define SERVER_PORT 8080 /* arbitrary, but client & server must agree */
#define BUFSIZE 4096  /* block transfer size */
#define ADDRSIZE 128 /* addres size*/

using namespace std;

void separarURL(string url,char *host, long int &port, char *file,char *nomeArq)
{
  // exemplo
  // url =  http://gaia.cs.umass.edu:80/wireshark-labs/HTTP-wireshark-file1.html
  // host = gaia.cs.umass.edu
  // port = 80
  // file = wireshark-labs/HTTP-wireshark-file1.html
  //cout<< "inicio o separarURL"<<"\n";
  //pegando host
  int inicio = url.find("//")+2;//somar pq tem um '/' a mais
  int fim = url.find(':',inicio);
  string hostStr = url.substr(inicio,fim-inicio);
  strcpy(host,hostStr.c_str());
  //cout<< host << "\n";
  
  //pegando port
  inicio = fim+1;
  fim = url.find('/',inicio);
  string portStr = url.substr(inicio,fim-inicio);
  port = strtol(portStr.c_str(),NULL,10);
  //cout<< port << "\n";

  // pegando file
  inicio = fim+1;
  fim = url.find_last_of('/')+1;
  string fileStr = url.substr(inicio);
  strcpy(file,fileStr.c_str());
  //cout<< file << "\n";

  string nomeArqStr = url.substr(fim);
  strcpy(nomeArq,nomeArqStr.c_str());


  return;

}

void cabecalho(char *getReq, char file[],char host[])
{
  char buf[BUFSIZE];
  strcpy(getReq,"");
  sprintf(buf,"GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n",file,host);
  strcat(getReq,buf);
  return;
}

long int separarResp(string buf,char *respHeader,char *resp, int &sizeHeader, int &sizeResp)
{
  char busca[5] ="\r\n\r\n";
  int fim = buf.find(busca);  
  string aux = buf.substr(0,fim);
  sizeHeader = aux.size();
  strcpy(respHeader,aux.c_str());
  fim =fim+4;
  aux = buf.substr(fim);
  sizeResp = aux.size();
  strcpy(resp,aux.c_str());

  int inicio = buf.find(" ");  
  aux = buf.substr(inicio,4);

  return strtol(aux.c_str(),NULL,10);
}

int main(int argc, char **argv)
{
  int c, s, bytes;
  char buf[BUFSIZE];  /* buffer for incoming file */
  struct hostent *h;  /* info about server */
  struct sockaddr_in channel; /* holds IP address */
  FILE *arquivo;
  //cout << argc<< "\n";  
  //cout<<"chegou ate antes do argc\n";

  if (argc != 2){printf("Usage: client http://<HOST>:<PORT>/<FILE>\n"); exit(-1);}

  //string url = argv[1];
  char host[ADDRSIZE];
  long int port;
  char  file[ADDRSIZE];
  char nomeArq[ADDRSIZE];

  //cout<<"chegou ate antes do separarURL\n";

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
  //write(s, file, strlen(file)+1);
  
  /* Go get the file and write it to standard output.*/
  
    
  // Formulando cabeçalho para requisição
  char getReq[BUFSIZE]  ;  
  cabecalho(getReq,file, host);

//strcpy(getReq,"GET /wireshark-labs/HTTP-wireshark-file1.html HTTP/1.1\r\nHost: gaia.cs.umass.edu\r\n\r\n");
  /*strcpy(getReq,"GET ");
  sprintf(buf,"%s HTTP/1.1\r\n",file);
  strcat(getReq,buf);
  sprintf(buf,"Host: %s\r\n\r\n",host);
  strcat(getReq,buf);
  printf("Cabeçalho enviado: %s\n",getReq );
*/
  /*
  strcpy(getReq,"");
  sprintf(buf,"GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n",file,host);
  strcat(getReq,buf);
*/

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


