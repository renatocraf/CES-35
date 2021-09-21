# Lab2 - Implementando Cliente e Servidor HTTP

- Carlos Renato de Andrade Figueiredo
- Samara Ribeiro Silva

## Cliente

Os arquivos relacionados com a parte do cliente estão dispostos na pasta client.
Para compilar os arquivos, entre na pasta e execute o comando make:

```bash
$ cd client
$ make
```

Será criado um executável "web-client" dentro da pasta /client/bin

Para executá-lo, rode:

```bash
$ cd bin
$ ./web-client http://<HOST>:<PORT>/<FILENAME>
```
Perceba que o HOST deve ser o host que se deseja acessar, exemplo: gaia.cs.umass.edu.
O PORT é referente a porta, exemplo: 80
O FILENAME é o arquivo que se deseja acessar, exemplo:wireshark-labs/HTTP-wireshark-file1.html

Caso deseje apagar os arquivos compilados mais os arquivos baixados com execução do programa, basta voltar para a pasta /client utilizar o seguinte comando, que irá deletar a pasta /bin:

```bash
$ cd ..
$ make clean
```

## Servidor

Os arquivos relacionados com a parte do cliente estão dispostos na pasta server.
Para compilar os arquivos, entre na pasta e execute o comando make:

```bash
$ cd server
$ make
```

Será criado um executável "web-server" dentro da pasta /server/bin e os arquivos "html" serão copiados da pasta /file para a pasta /bin.
O Server foi configurado para rodar na porta 8080.

Para executá-lo, rode:

```bash
$ cd bin
$ ./web-server
```

## Testes

Primeiro foi feito o teste no arquivo web-client, fazendo uma solicitação para o http://gaia.cs.umass.edu:80/wireshark-labs/HTTP-wireshark-file1.html.

O resultado pode ser observado na figura abaixo. Como a resposta foi 200 OK, o arquivo foi gravado na pasta /client/bin com o nome "HTTP-wireshark-file1.html":

![alt text](https://github.com/renatocraf/CES-35/blob/ae37b94942a6bdbd8d3549c236463f3fbe874f50/Lab2_sockets/img_readme/client_gaia_cs_umass.png)

O segundo teste consistiu em fazer uma solicitação de um arquivo inexistente/errado para o mesmo servidor http://gaia.cs.umass.edu:80/wireshark-labs/arquivo_errado.

Como o arquivo não existe, recebemos a resposta 404, que é mostrada na figura abaixo, mas não é gravada em um arquivo.

![alt text](https://github.com/renatocraf/CES-35/blob/ae37b94942a6bdbd8d3549c236463f3fbe874f50/Lab2_sockets/img_readme/cliente_arquivo_errado_gaia.png)

Agora vamos testar o nosso web-server. Inicialmente, utilizando o web-cliente criado, foi solicitado o arquivo http://localhost:8080/ola.html. O server encontra esse arquivo e responde com um 200 OK. O arquivo é gravado na pasta /client/bin.

![alt text](https://github.com/renatocraf/CES-35/blob/ae37b94942a6bdbd8d3549c236463f3fbe874f50/Lab2_sockets/img_readme/server_solic_cliente.png)

Outro teste realizado foi a solicitação de um arquivo inexistente para o web-server, resultando numa resposta 404 Not Found, conforme pode ser observado na próxima figura. O arquivo não é gravado.

![alt text](https://github.com/renatocraf/CES-35/blob/ae37b94942a6bdbd8d3549c236463f3fbe874f50/Lab2_sockets/img_readme/servidor_solic_client_fail.png)

Por fim, para testar a multithread foram feitas 10 solicitações utilizando o comando "curl". Observe que as ids das threads não variam até a 6ª solicitação. Significa que a solicitação está sendo resolvida e finalizada antes mesmo de receber uma nova solicitação. Note que na sétima solicitação, a resposta não foi criada a tempo, e uma nova thread foi criada.

O comando utilizado para teste foi:

```bash
$ for i in {1..10}; do time curl -s http://localhost:8080/ola.html &> /dev/null & sleep 0.001; done
```

![alt text](https://github.com/renatocraf/CES-35/blob/ae37b94942a6bdbd8d3549c236463f3fbe874f50/Lab2_sockets/img_readme/server_solic_curl.png)



