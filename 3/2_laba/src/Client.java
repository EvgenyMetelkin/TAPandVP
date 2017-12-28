import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class Client implements Runnable {

    private final int port;
    private final Thread thread;
    private DatagramSocket socket;
    private boolean isActive = true;
    public static boolean connected = false;
    public static String message;

    public boolean isActivate() {
        return isActive;
    }

    public Client(int port) {
        this.port = port;
        thread = new Thread(this);
        thread.start();
    }

    @Override
    public void run() {

        byte[] buffer = new byte[1024];

        try {
            socket = new DatagramSocket(port);
            socket.setReuseAddress(true);
        } catch (SocketException ex) {
            isActive = false;
            try {
                throw new Exception("Невозможно создать UDP-сокет на порту " + port + ". " + ex.getMessage());
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        while (!connected) {
            //Receive request from client
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
            try {
                socket.receive(packet);
            } catch (IOException ex) {
                try {
                    throw new Exception("Невозможно отослать UDP-сообщение. " + ex.getMessage());
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            message = new String(buffer, packet.getOffset(), packet.getLength());
        }

    }

    /**
     * Останавливаем клиент
     */
    @SuppressWarnings("static-access")
    public void stop() throws IOException {
        thread.interrupted();
        socket.close();
        MainClient.socket.close();
    }
}  