import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

import static java.lang.Thread.sleep;

public class MainClient {
    private static boolean connected = false;
    public static Socket socket;
    private static int rows;
    private static int cols;
    private static int[][] matrix1;
    private static int[][] matrix2;
    private static String ipAddress;
    private static boolean error = false;

    public static void main(String[] args) {
        new Client(1014);
        while(Client.message == null) {
            System.out.println("Попытка подключиться...");
            try {
                sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        ipAddress = Client.message.substring(1, Client.message.length());
        System.out.println("Подключились! IP адрес " + ipAddress);

        try {
            socket = new Socket(ipAddress, 4444);
        } catch (IOException e) {
            System.out.println("Ошибка! Не удалось создать сокет.");
        }

        InputStream input  = null;
        try {
            input = socket.getInputStream();
        } catch (IOException e) {
            System.out.println("Ошибка создания InputStream");
        }
        OutputStream output = null;
        try {
            output = socket.getOutputStream();
        } catch (IOException e) {
            System.out.println("Ошибка создания OutputStream");
        }

        DataOutputStream out = new DataOutputStream(output);
        DataInputStream in = new DataInputStream(input);

        if(rows == 0 || cols == 0){
            try {
                out.writeUTF("cameNumberColsAndRows");
            } catch (IOException e) {
                System.out.println("Ошибка отправки сообщения");
            }
            try {
                rows = in.readInt();
            } catch (IOException e) {
                System.out.println("Ошибка! Не удалось принять строки... Возможно, сервер был отключен!");
            }
            try {
                cols = in.readInt();
            } catch (IOException e) {
                System.out.println("Ошибка! Не удалось принять столбцы... Возможно, сервер был отключен!");
            }

            //System.out.println("Строк = " + rows + ". Столбцов = " + cols + ".");

            matrix1 = new int[rows][cols];
            matrix2 = new int[rows][cols];
        }
        if(matrix1[0][0] == 0 || matrix1[0][0] == 0){
            try {
                out.writeUTF("matrix1ndMatrix2");
            } catch (IOException e) {
                System.out.println("Ошибка! Не удалось отправить сообщение \"matrixAndMatrixB\"");
            }
            for (int row = 0; row < rows; ++row) {           // Цикл по строкам матрицы.
                for (int col = 0; col < cols; ++col) {  // Цикл по столбцам матрицы.
                    try {
                        matrix1[row][col] = in.readInt();
                    } catch (IOException e) {
                        System.out.println("Ошибка! Не удалось прочитать очередное значение первой матрицы");
                    }
                }
            }
            for (int row = 0; row < rows; ++row) {           // Цикл по строкам матрицы.
                for (int col = 0; col < cols; ++col) {  // Цикл по столбцам матрицы.
                    try {
                        matrix2[row][col] = in.readInt();
                    } catch (IOException e) {
                        System.out.println("Ошибка! Не удалось прочитать очередное значение второй матрицы");
                    }
                }
            }
            System.out.println("Матрицы получены!");
        }

        while(!error){
            int taskRow = 0;
            try {
                taskRow = in.readInt();
            } catch (IOException e) {
                error = true;
                System.out.println("Ошибка! Не удалось прочитать Task Row! Возможно, сервер был отключен!");
                System.out.println("Работа будет остановлена!");
                continue;
            }
            int taskCol = 0;
            try {
                taskCol = in.readInt();
            } catch (IOException e) {
                error = true;
                System.out.println("Ошибка! Не удалось прочитать Task Col! Возможно, сервер был отключен!");
                System.out.println("Работа будет остановлена!");
                continue;
            }

            int result = 0;

            for(int i = 0; i < matrix2.length; i++){
                result += matrix1[taskRow][i] * matrix2[i][taskCol];
            }

            try {
                out.writeInt(result);
            } catch (IOException e) {
                error = true;
                System.out.println("Ошибка! Не удалось отправить результат на сервер. Возможно, сервер был отключен!");
                System.out.println("Работа будет остановлена!");
                continue;
            }
            System.out.print(taskRow + "\t");
            System.out.print(taskCol + "\t");
            System.out.println(result);
        }

    }
}
