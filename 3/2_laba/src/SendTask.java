import java.io.*;
import java.net.Socket;

import static java.lang.Thread.interrupted;
import static java.lang.Thread.sleep;

public class SendTask implements Runnable {
    public static Socket socket;

    SendTask(Socket socket){
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            InputStream input = socket.getInputStream();
            OutputStream output = socket.getOutputStream();

            DataOutputStream out = new DataOutputStream(output);
            DataInputStream in = new DataInputStream(input);

            if (in.readUTF().equals("cameNumberColsAndRows")) {
                out.writeInt(Server.rows);
                out.writeInt(Server.cols);
            }

            if (in.readUTF().equals("matrix1ndMatrix2")) {

                for (int row = 0; row < Server.rows; ++row) {
                    for (int col = 0; col < Server.cols; ++col) {
                        out.writeInt(Server.matrix1[row][col]);
                    }
                }
                for (int row = 0; row < Server.rows; ++row) {
                    for (int col = 0; col < Server.cols; ++col) {
                        out.writeInt(Server.matrix2[row][col]);
                    }
                }
            }


            while (Server.noClose) {
                for (int row = 0; row < Server.rows; ++row) {
                    for (int col = 0; col < Server.cols; ++col) {
                        if (!Server.matrix4[row][col]) {
                            out.writeInt(row);
                            out.writeInt(col);
                            Server.matrix1[row][col] = in.readInt();
                            Server.matrix4[row][col] = true;
                            sleep(200);
                            if(!Server.noClose){
                                socket.setReuseAddress(true);
                                socket.close();
                                Thread.currentThread().interrupt();
                            }
                        }
                    }
                }
            }



        } catch (IOException e) {
            System.out.println("Error of waiting of clients!");
            ConnectUser.numberOfClients--;
            System.out.println("Number of clients: " + ConnectUser.numberOfClients);
        } catch (InterruptedException e) {
            System.out.println("Error sleep");
        }
    }
}
