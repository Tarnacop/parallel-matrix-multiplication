import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

public class MatrixMultiplication {

    public static void main(String[] args) {

        if(args.length != 2) {

            System.err.println("Usage: pass matrix input file, vector input file");
        }

        BufferedReader matrix_reader, vector_reader;
        try {
            matrix_reader = new BufferedReader(new FileReader(args[0]));
            vector_reader = new BufferedReader(new FileReader(args[1]));

            String vector_line = vector_reader.readLine();
            ArrayList<Vector> vectors = new ArrayList<>() ;

            while(vector_line != null) {

                vectors.add(new Vector(vector_line));
                vector_line = vector_reader.readLine();
            }
            vector_reader.close();

            String matrix_line = matrix_reader.readLine();
            while(matrix_line != null) {

                Matrix matrix = new Matrix(matrix_line);

                for(int i = 0; i < vectors.size(); i++) {

                    float result = matrix.Multiply(vectors.get(i));
                    System.out.println(result);
                }
                // Continue
                matrix_line = matrix_reader.readLine();
            }
            matrix_reader.close();

        } catch(IOException e) {
            e.printStackTrace();
        }
    }

}
