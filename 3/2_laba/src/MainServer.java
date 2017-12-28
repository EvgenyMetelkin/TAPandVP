import java.util.Random;

public class MainServer {
    private static int cols = 20;
    private static int rows = 20;
    private static int[][] matrix1;
    private static int[][] matrix2;
    private static Thread thread;

    public static void main(String[] args) {
        matrix1 = new int[rows][cols];
        matrix2 = new int[rows][cols];



        thread = new Thread(new Server(rows, cols, matrix1, matrix2));
        thread.start();

    }
}