import java.io.*;
import java.net.*;

public class ConnectUser implements Runnable {
    private static int rows;
    private static int cols;
    private int[][] matrixA = new int[rows][cols];
    private int[][] matrixB = new int[rows][cols];
    public static int numberOfClients = 0;

    private ServerSocket serverSocket;

    ConnectUser(int rows, int cols,
                int[][] matrixA, int[][] matrixB){
        this.rows = rows;
        this.cols = cols;
        this.matrixA = matrixA;
        this.matrixB = matrixB;

        try {
            serverSocket = new ServerSocket(4444);
            serverSocket.setReuseAddress(true);
        } catch (IOException e) {
            System.out.println("Ошибка! Сокет сервера не открыт!");
        }
    }

    @Override
    public void run() {
        Socket socket;
        System.out.println("Сервер запущен");
        while (Server.noClose){
            try {
                socket = serverSocket.accept(); // блокировка до появления соединения
                numberOfClients++;
                System.out.println("Подключился новый клиент! Количество клиентов: " + numberOfClients);
                socket.setReuseAddress(true);

                new Thread(new SendTask(socket)).start();

            } catch (IOException e) {
                System.out.println("Ошибка подключения клиента!");
            }
        }
        try {
            serverSocket.close();
            Thread.currentThread().interrupt();
        } catch (IOException e) {
            System.out.println("Не получилось закрыть сокет сервера");
        } catch (NullPointerException e) {
            System.out.println("Ошибка! Порт занят");
        }
    }

}
