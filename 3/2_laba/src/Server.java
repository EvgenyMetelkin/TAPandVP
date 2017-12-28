import java.net.*;
import java.util.Enumeration;
import java.util.Random;

import static java.lang.Thread.sleep;

public class Server implements Runnable{
    public static int rows;
    public static int cols;
    public static volatile int[][] matrix1 , matrix2;
    public static volatile boolean[][] matrix4;

    public static volatile boolean noClose = true;


    Server(int rows, int cols, int[][] m1, int[][] m2){
        this.rows = rows;
        this.cols = cols;
        this.matrix1 = m1;
        this.matrix2 = m2;
        matrix1 = new int[rows][cols];
        matrix2 = new int[rows][cols];

        final Random random = new Random();
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                matrix1[row][col] = random.nextInt(44);
                matrix2[row][col] = random.nextInt(44);
            }
        }
        matrix4 = new boolean[rows][cols];
    }

    @Override
    public void run() {
        try {
            new Thread(new SearchClient(getServerIp())).start();
        } catch (SocketException e) {
            System.out.println("Error! HiNewClient.class not open!");
        }

        new Thread(new ConnectUser(rows, cols, matrix1, matrix2)).start(); // ожидаем подключение по tcp



        new Thread(new ShowResultMatrix()).start(); // постоянная проверка матрицы на нулевые значения
    }

    private static InetAddress getServerIp() throws SocketException {
        Enumeration en = null;
        try {
            en = NetworkInterface.getNetworkInterfaces();
        } catch (SocketException e) {
            e.printStackTrace();
        }
        while (en.hasMoreElements()) {
            NetworkInterface i = (NetworkInterface) en.nextElement();
            for (Enumeration en2 = i.getInetAddresses(); en2.hasMoreElements();) {
                InetAddress addr = (InetAddress) en2.nextElement();
                if (!addr.isLoopbackAddress()) {
                    if (addr instanceof Inet4Address) {
                        return addr;                    }

                }
            }
        }
        return null;
    }


}
