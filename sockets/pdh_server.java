/*
 * pdh_server.java
 *
 * Created on October 19, 2003, 9:22 AM
 */

import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Date;
import java.util.Calendar;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

/**
 *
 * @author  brumatto
 */
public class pdh_server {
    ServerSocket ss;
    Socket cs; // A copia eh indicada separado do principal.
    BufferedReader r;
    BufferedWriter w;
    byte[] cliIP;
    String serverinfo = new String("Servidor em Java, Versao 1.10\n");
    String vers = new String("V1.10\n");
    String comando;
    String resposta;
    boolean fim=false;

    /** Creates a new instance of pdh_server */
     public pdh_server() {
       /*
        * No java tudo é mais simples, ao criar o Serversocket
        * já é feita automaticamente a criação do socket (socket), 
        * sua atribuição de endereço (bind) e criação da fila (listen)
        * basta ficar aguardando a conexão (accept)
        */
       try {
           ss = new ServerSocket(5555);
           cs = ss.accept();
           /* No java utilizamos manipuladores de arquivos de texto para
            * entrada e saida no socket
            */
           r = new BufferedReader( new InputStreamReader( cs.getInputStream() ));
           w = new BufferedWriter( new OutputStreamWriter( cs.getOutputStream() ));
              
           /* Vamos exibir qu1em se conectou */
           System.out.println("cliente: "+cs.getInetAddress().getHostAddress()+":"+cs.getPort());
           
           // Primeiro o servidor manda a versão
           w.write(serverinfo, 0, serverinfo.length());
           w.flush(); // Nao vamos esperar para dar o retorno!!!
           // Troca de mensagens, até fim=true (QUIT)
           while(!fim) {
                comando = r.readLine();
                System.out.println("Comando: "+comando); //para registro
                if(comando.equals("DATA")) { // comando aceito
                     resposta="+OK: " + data()+"\n";
                     w.write(resposta, 0, resposta.length()); w.flush();
                } else if(comando.equals("HORA")) { 
                     resposta="+OK: " + hora()+"\n";
                     w.write(resposta, 0, resposta.length()); w.flush();

                } else if(comando.equals("INFO")) { // comando aceito, vou responder
                     resposta="+OK: " + vers;
                     w.write(resposta, 0, resposta.length()); w.flush();
                
                } else if(comando.equals("QUIT")) { // comando aceito, vou responder
                     resposta="+OK: ASTA LA VISTA\n"; // ok e a data
                     w.write(resposta, 0, resposta.length()); w.flush();
                     fim = true;
                } else {
                     resposta="-ERRO\n";
                     w.write(resposta, 0, resposta.length()); w.flush();
                }
           }
           /*
            * Basta fechar a conexao, mas antes vamos fechar os arquivos.
            * Para garantir que tudo foi terminado, vamos dar um flush
            */
           w.flush();
           r.close();
           w.close();
           cs.close();
           ss.close();
       } catch(IOException err) {
           err.printStackTrace();
       }
       
       
       
    }
    
    /**
     * O leitor podera implementar os métodos responsáveis
     * por pegar a hora e a data.
     */
    
    public String data() {
        DateFormat dformat = new SimpleDateFormat("dd/MM/yyyy");
        Date data = new Date();
        return dformat.format(data);
    }
    
    public String hora() {
        DateFormat hformat = new SimpleDateFormat("HH:mm:ss");
        Date hora = new Date();
        return hformat.format(hora);
    }
    
    /**
     * O método de classe main somente cria o objeto primordial
     */
    public static void main(String[] args) {
        new pdh_server();
    }
    
}
