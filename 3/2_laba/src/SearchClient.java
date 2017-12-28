import java.io.IOException;
import java.net.*;

public class SearchClient implements Runnable {
    private InetAddress ipAddress;
    private String message;

    SearchClient(InetAddress ipAddress){
        this.ipAddress = ipAddress;
    }

    @Override
    public void run() {
        while(Server.noClose){
            message = ipAddress.toString();

            sendUDPIP(message, 1014);

            try {
                Thread.sleep(4000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        Thread.currentThread().interrupt();
    }

    public static void sendUDPIP(String message, int port){
        try {
            final DatagramSocket socket = new DatagramSocket();
            socket.setReuseAddress(true);
            final byte[] message_byte = message.getBytes();
            DatagramPacket packet = new DatagramPacket(message_byte,
                    message_byte.length,
                    InetAddress.getByName("255.255.255.255"),
                    port);
            socket.send(packet);
        } catch (SocketException e) {
            System.out.println("Error! The socket is not open");
        } catch (UnknownHostException e) {
            System.out.println("Unknown host exception!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}
