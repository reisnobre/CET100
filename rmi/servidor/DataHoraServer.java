import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;
import java.util.Calendar;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class DataHoraServer extends UnicastRemoteObject implements DataHoraService {
    private Date data;
    private Date hora;
    private DateFormat dformat = new SimpleDateFormat("dd/MM/yyyy");
    private DateFormat hformat = new SimpleDateFormat("HH:mm:ss");

    public DataHoraServer() throws RemoteException { }
    
    public String pegarData() throws RemoteException {
        data = new Date();
        return dformat.format(data);
    }
    
    public String pegarHora() throws RemoteException {
        hora = new Date();
        return hformat.format(hora);
    }
}
