import java.rmi.*;

public class Servidor {

	public static void main(String[] args) {
		try {
			DataHoraService dhs = new DataHoraServer();
			Naming.rebind(
				"rmi://localhost:5555/rmt_dhs",dhs);
			System.out.println("Registrado objeto remoto na rede");
		} catch (Exception e) {
			System.out.println("Não foi possível registrar pelo RMI");
			e.printStackTrace();
		}
	}
}
