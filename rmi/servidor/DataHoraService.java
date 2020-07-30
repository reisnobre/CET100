import java.rmi.*;

public interface DataHoraService extends Remote
{
	String pegarData() throws RemoteException;
	String pegarHora() throws RemoteException;
}
