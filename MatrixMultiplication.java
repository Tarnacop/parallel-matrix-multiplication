import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class MatrixMultiplication {

    public static void main(String[] args) {

        if(args.length != 3) {

            System.err.println("Usage: pass matrix input file, vector input file");
        }

        BufferedReader matrix_reader, vector_reader;
        try {
            matrix_reader = new BufferedReader(new FileReader(args[1]));
            vector_reader = new BufferedReader(new FileReader(args[2]));

            String matrix_line = matrix_reader.readLine();
            String vector_line = vector_reader.readLine();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

}
