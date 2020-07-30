#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
#define MAX_BUFF 50

int main(int argc, char **argv)
{
    string comando; // cada comando do cliente deve possuir 4 caracteres;
    string resposta; // maximo tamanho de resposta
    char buffer[MAX_BUFF];
    int i;
    register int s2s; // meu socket para o servidor
    struct sockaddr_in socket2server; // definira os enderecos do servidor
    struct hostent *phost;
    
    cout << "Cliente PDH C++ para Unix, versao 1.10" << endl;
    if(argc != 2) {
    	cout << "Usar: pdh-cliente <servidor pdh>" << endl;
	exit(1);
    }
    /*
     * Primeiro devo definir um socket para a conexao
     * Aqui eu qualifico um socket TCP (SOCK_STREAM) sobre IP (PF_INET)
     * Se houver erro eu caio fora com aviso de erro.
     *
     * Primeiro informo ao usuario o que estou fazendo
     */
    cout << "Buscando o servidor ... "; 
    if ((s2s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Nao foi possivel conectar com o servidor" << endl;
	cerr << "cliente: socket" << endl;
        exit(1);
    }

    /*
     * Precisamos definir o endereco do servidor e sua porta
     * Definir o endereço ao qual o socket estará vinculado.
     */
    socket2server.sin_family = AF_INET; // Familia que representa IP
    socket2server.sin_port = htons(5555); // Porta que o servidor estará ouvindo
    /*
     * Para pegar o endereco do servidor, precisaremos utilizar um servico
     * de nomes que ira interpretar o servidor pelo nome conhecido.
     * phost irá apontar para uma estrutura constante do tipo s_addr
     */
    phost=nullptr;
    if((phost = gethostbyname(argv[1])) == nullptr)
    {
    	cout << "Nao foi possivel conectar com o servidor" << endl;
        cerr << "cliente: gethostbyname" << endl;
        exit(1);
    }
    
    /* 
     * vamos atribuir o endereco IP que acabamos de pegar como
     * endereço do servidor. Logo acima ja atribuimos a porta.
     */
    memcpy((char *) &socket2server.sin_addr.s_addr, (char *)phost->h_addr, phost->h_length);
    
    /* 
     * Agora vamos conectar o socket ao servidor
     */
    if (connect(s2s, (struct sockaddr *) &socket2server, sizeof(socket2server)) != 0) {
    	cout << "Nao foi possivel conectar com o servidor" << endl;
    	cerr << "cliente: connect" << endl;
	exit(1);
    }    
    cout << "conectado!" << endl; 
    
    // Primeiro recebemos a versão do servidor
    i=recv(s2s,buffer,MAX_BUFF,0); buffer[i]='\0';
    resposta = buffer;
    cout << resposta; // Usuario avisado!!!

          
    /*
     * Tudo OK, vamos conversar com o servidor pedindo data, hora e info
     * Vamos supor que tudo esta OK, e desprezamos o +OK: das respostas.
     */
    resposta = "Hoje: ";
    comando = "DATA\n";
    send(s2s, comando.c_str(), comando.size(), 0);
    i=recv(s2s,buffer,MAX_BUFF,0); buffer[i]='\0';
    resposta += string(buffer).substr(5,i-6) + " ";
    comando = "HORA\n";
    send(s2s, comando.c_str(), comando.size(), 0);
    i=recv(s2s,buffer,MAX_BUFF,0); buffer[i]='\0';
    resposta += string(buffer).substr(5,i-6) + " - ";
    comando = "INFO\n";
    send(s2s, comando.c_str(), comando.size(), 0);
    i=recv(s2s,buffer,MAX_BUFF,0); buffer[i]='\0';
    resposta += string(buffer).substr(5,i-6);
    
    cout << resposta << endl;

    comando = "QUIT\n";
    send(s2s, comando.c_str(), comando.size(), 0);
    i=recv(s2s,buffer,MAX_BUFF,0); buffer[i]='\0';
    resposta=string(buffer).substr(0,4);
    if(resposta == "+OK:") cout << "Conexao terminada com sucesso" << endl;
    else cout << "Problemas, vamos abortar a conexao" << endl;

    close(s2s);
    return 0;
}
