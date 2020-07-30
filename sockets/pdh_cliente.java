/*
 * pdh_cliente.java
 *
 * Created on October 19, 2003, 11:20 AM
 */

import java.net.Socket;
import java.net.SocketException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

/**
 *
 * @author  brumatto
 */
public class pdh_cliente {
    Socket cs; // A copia eh indicada separado do principal.
    BufferedReader r;
    BufferedWriter w;
    byte[] cliIP;
    String serverinfo = new String("Servidor em Java, Versao 1.00\n");
    String vers = new String("V1.00\n");
    String comando;
    String resposta;
    boolean fim=false;
    
    /** Creates a new instance of pdh_cliente */
    public pdh_cliente(String server) {
        try {
            /* Somente para avisar o usuario o que estamos fazendo */
            System.out.print("Buscando o servidor ... ");
            /* 
             * Este socket nao precisa de listen ou bind, ja que eh cliente
             * Por isto nao usamos o ServerSocket. O cliente somente precisa
             * se conectar. No java, criar um socket indicando o servidor e
             * porta faz isto automaticamente.
             */
            cs = new Socket(server,5555);
            /*
             * Como qualquer socket em Java, criamos os arquivos de entrada e saida
             */
            r = new BufferedReader( new InputStreamReader( cs.getInputStream() ));
            w = new BufferedWriter( new OutputStreamWriter( cs.getOutputStream() ));
            /* 
             * Como foi realizado com sucesso, basta indicar ao usuario.
             * Se houvesse erro seria desviado para o catch deste try.
             * Vamos avisar ao usuario com quem nos conectamos:
             */
            System.out.println("conectado!");
            System.out.println(r.readLine());
            /*
             * Tudo OK, vamos conversar com o servidor pedindo data, hora e info
             * Vamos supor que tudo esta OK, e desprezamos o +OK: das respostas.
             */
            resposta="Hoje: ";
            comando="DATA\n";
            w.write(comando, 0, comando.length());
            w.flush();
            resposta+=r.readLine().substring(5);
            comando="HORA\n";
            w.write(comando, 0, comando.length());
            w.flush();
            resposta+=" ";
            resposta+=r.readLine().substring(5);
            resposta+=" - ";
            comando="INFO\n";
            w.write(comando, 0, comando.length());
            w.flush();
            resposta+=r.readLine().substring(5);
            System.out.println(resposta);
            /* Terminada a conversa, vamos encerrar a conexao */
            comando="QUIT\n";
            w.write(comando, 0, comando.length());
            w.flush();
            resposta=r.readLine();
            /* Somente para brincar, vamos testar o +OK: desta vez */
            if(resposta.substring(0,4).equals("+OK:"))
                System.out.println("Conexao terminada com sucesso");
            else
                System.out.println("Problemas, vamos abortar a conexao");
            w.flush();
            r.close();
            w.close();
        } catch(IOException err) {
            System.out.println("Nao foi possivel conectar com o servidor "+server);
            err.printStackTrace();
        }
        
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("Cliente PDH para JAVA, versao 1.00");
        if(args.length == 1) new pdh_cliente(args[0]);
        else System.out.println("Usar: java pdh_cliente <servidor pdh>");
    }
    
}
