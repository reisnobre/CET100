#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

class datahora {
public:
  string data() {
    time_t t = time(0);
    tm *now = localtime(&t);
    return to_string(now->tm_mday) + "/" + to_string(now->tm_mon+1) +
    "/" + to_string(now->tm_year+1900);
  }
  string hora() {
    time_t t = time(0);
    tm *now = localtime(&t);
    return to_string(now->tm_hour) + ":" + to_string(now->tm_min) +
    ":" + to_string(now->tm_sec);
  }
};

#define SOCKET_PORT 5555
#define MAX_BUFF 50

int main()
{
    datahora dh;
    string serverinfo = "Servidor em C++ para UNIX, Versao 1.10\n";
    string vers = "V1.10\n";
    char buffer[50]; // um buffer para string auxiliar.
    string comando; // comandos recebidos do cliente.
    string resposta; // resposta para o cliente.
    bool fim=false;
    int i;
    socklen_t fromlen;
    unsigned long int cliIP;
    register int ss, cs;
    struct sockaddr_in server, cliente; // enderecos dos sockets

    /*
     * Primeiro devo definir um socket para a conexao
     * Aqui eu qualifico um socket TCP (SOCK_STREAM) sobre IP (PF_INET)
     * Se houver erro eu caio fora com aviso de erro.
     */
    if ((ss = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "erro: server socket" << endl;
        exit(1);
    }

    /*
     * Definir o endereço ao qual o socket estará vinculado.
     */
    server.sin_family = AF_INET; // Familia que representa IP
    server.sin_port = htons(SOCKET_PORT); // Porta que o servidor estará ouvindo
    server.sin_addr.s_addr = htonl(INADDR_ANY); // IP 0.0.0.0
    // Na configuracao acima, qualquer maquina pode se conectar neste servico

    /*
     * Vamos tentar vincular o enderecoa ao Socket.
     * Aqui estamos associando ao socket criado "s" o endereco
     * para o servidor "server
     * O terceiro endereco indica o tamanho do endereco
     */
      if (bind(ss, (struct sockaddr *) &server, sizeof(server) ) < 0) {
        cerr << "erro: server bind" << endl;
        exit(1);
    }

    /*
     * Vamos criar a fila para ouvir o socket
     */
    if (listen(ss, 5) < 0) {
        cerr << "erro: server listen" << endl;
        exit(1);
    }

    /*
     * Estou aceitando conexoes. No caso apenas uma.
     * cliente ira conter o endereco do cliente conectado.
     * cs (ClienteSocket) eh uma copia do ss (ServerSocket),
     * a principio o ss esta liberado para aceitar novas conexoes,
     * mas aqui, como nao criamos threads distintas, nao temos
     * outro accept para uma nova conexao enquanto trabalhamos com
     * este cs.
     */
    if ((cs = accept(ss,nullptr,nullptr)) < 0) {
        cerr << "erro: server accept" << endl;
        exit(1);
    }

    /*
     * Somente para visualizarmos o que acontece, imprimimos os dados
     * do cliente conectado.
     */
    fromlen=sizeof(server);
    getpeername(cs, (struct sockaddr *)&cliente, &fromlen);

    cliIP=cliente.sin_addr.s_addr;
    cout << "cliente: " << cliIP%0x100 << "." << (cliIP%0x10000)/0x100 << "." << (cliIP%0x1000000)/0x10000 << "." << cliIP/0x1000000 << ":" << ntohs(cliente.sin_port) << endl; 
    
    /*
     * Ja que estou conectado, vou enviar informaçoes sobre este servidor.
     */
    send(cs, serverinfo.c_str(), serverinfo.size(), 0);

    /*
     * Agora vou me comunicar com o cliente seguindo o protocolo definido.
     * fim inicialmente é falso, e somente sera verdade quando receber QUIT.
     */
     while(!fim) {
     /*
      * Vamos ler o comando do cliente:
      */
        i = recv(cs,buffer,MAX_BUFF,0); buffer[i]='\0'; 
        comando = buffer;
	cout << "Comando: "<< comando; //somente para registro
	/*
	 * Vamos decidir o que fazer com o comando:
	 */
	 if(comando=="DATA\n") { // comando aceito, vou responder
	     resposta = "+OK: "+dh.data()+"\n";
	     send(cs, resposta.c_str(), resposta.size(), 0);
	     
	 } else if(comando=="HORA\n") { // outro comando
	     resposta = "+OK: "+dh.hora()+"\n";
	     send(cs, resposta.c_str(), resposta.size(), 0);
	     
	 } else if(comando=="INFO\n") { // a versao
	     resposta = "+OK: " + vers;
	     send(cs, resposta.c_str(), resposta.size(), 0);
	     
	 } else if(comando == "QUIT\n") { // saio deste loop
	     resposta = "+OK: ASTA LA VISTA\n";
	     send(cs, resposta.c_str(), resposta.size(), 0);
	     fim = true;
	 
	 } else { // qualquer outro comando implica em erro
	     resposta = "-ERRO\n";
	     send(cs, resposta.c_str(), resposta.size(), 0);
	 }     
    }

    /*
     * Basta fechar a conexao, mas por garantia, vou fechar tambem
     * outros elemento abertos
     */
    close(cs);
    close(ss);

    return 0;
}

/*
 * O importante neste exemplo eh o funcionamento da conexao em si, e nao
 * pegar a hora e data do sistema. A implementacao das funcoes abaixo fica
 * a cargo do leitor
 *
 */

