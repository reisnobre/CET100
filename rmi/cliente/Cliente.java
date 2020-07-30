import java.rmi.*;

public class Cliente {
   public static void main(String[] args) {
      try {
         DataHoraService dh = (DataHoraService) Naming.lookup(
            "rmi://localhost:5555/rmt_dhs");
         System.out.println("Dia de hoje " + dh.pegarData());
         System.out.println("Hora atual "+dh.pegarHora());
      } catch(Exception e) {
         System.out.println("Problemas na comunicação com o servidor RMI");
         e.printStackTrace();
      }
   }
}
