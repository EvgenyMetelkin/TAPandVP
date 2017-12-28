public class ShowResultMatrix implements Runnable{
    @Override
    public void run() {
        boolean show = false;
        while (!show) {
            if(!Server.noClose){
                Thread.currentThread().interrupt();
            }
            for (int row = 0; row < Server.rows; ++row) {
                for (int col = 0; col < Server.cols; ++col) {
                    if (!Server.matrix4[row][col]) {
                        row = 0;
                        col = 0;
                    }
                }
            }
            show = true;
        }
        if (show){
            System.out.println("Матрицы посчитаны!");
            System.out.println("Результат:");
            for (int row = 0; row < Server.rows; ++row) {           // Цикл по строкам матрицы.
                for (int col = 0; col < Server.cols; ++col) {  // Цикл по столбцам матрицы.
                    System.out.print(Server.matrix1[row][col] + "\t");
                }

                System.out.println();
            }

            Thread.currentThread().interrupt();
        }
    }
}
