import java.util.ArrayList;

public class Matrix {

    public ArrayList<Float> value;
    public ArrayList<Integer> column;
    public ArrayList<Integer> rowptr;
    public Matrix(String matrix_line) {

            value = new ArrayList<>();
            column = new ArrayList<>();
            rowptr = new ArrayList<>();

            // To get the first "[ " and last " ]" out of the way
            matrix_line = matrix_line.substring(2, matrix_line.length() - 2);

            for(String row: matrix_line.split("\\[")) {

                row = row.substring(0, row.length() -1);
            }
    }



}
