#include <parsing.h>

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
    
  //pegando port
  inicio = fim+1;
  fim = url.find('/',inicio);
  string portStr = url.substr(inicio,fim-inicio);
  port = strtol(portStr.c_str(),NULL,10);
 
  // pegando file
  inicio = fim+1;
  fim = url.find_last_of('/')+1;
  string fileStr = url.substr(inicio);
  strcpy(file,fileStr.c_str());

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
