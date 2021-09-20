# Lab2 - Implementando Cliente e Servido HTTP

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
Perceba que o <HOST> deve ser o host que se deseja acessar, exemplo: gaia.cs.umass.edu.
O <PORT> é referente a porta, exemplo: 80
O <FILENAME> é o arquivo que se deseja acessar, exemplo:wireshark-labs/HTTP-wireshark-file1.html

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

Será criado um executável "web-server" dentro da pasta /client/bin e os arquivos "html" serão copiados da pasta /file para a pasta /bin.

Para executá-lo, rode:

```bash
$ cd bin
$ ./web-server
```

## Testes













