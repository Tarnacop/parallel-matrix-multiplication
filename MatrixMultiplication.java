import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class MatrixMultiplication {

    public static void main(String[] args) {

        if(args.length != 2) {

            System.err.println("Usage: pass matrix input file, vector input file");
        }

        BufferedReader matrix_reader, vector_reader;
        try {
            matrix_reader = new BufferedReader(new FileReader(args[0]));
            vector_reader = new BufferedReader(new FileReader(args[1]));

            String matrix_line = matrix_reader.readLine();
            String vector_line = vector_reader.readLine();

            while(matrix_line != null && vector_line != null) {

                Matrix matrix = new Matrix(matrix_line);
                Vector vector = new Vector(vector_line);

                // Continue
                matrix_line = matrix_reader.readLine();
                vector_line = vector_reader.readLine();
            }
            matrix_reader.close();
            vector_reader.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

}
