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

            String[] rows = matrix_line.split("\\[");

            // To check if it is the first in the row
            boolean isFirst;
            // Going through each row
            for(String row: rows) {

                // If empty, just go on
                if(row.isEmpty()) {
                    continue;
                }
                // Delete last "],"
                row = row.substring(0, row.length() - 3);

                isFirst = true;
                String[] row_elements = row.split("\\(");
                for(String row_element: row_elements) {

                    if(row_element.isEmpty()) {
                        continue;
                    }
                    row_element = row_element.substring(0, row_element.length() - 3);
                    // To keep the first and second element
                    String[] element = row_element.split(", ");

                    if(element.length == 2) {
                        value.add(Float.parseFloat(element[1]));
                        column.add(Integer.parseInt(element[0]));
                        if (isFirst) {

                            rowptr.add(value.size() - 1);
                            isFirst = false;
                        }
                    }
                }
            }
    }
}
