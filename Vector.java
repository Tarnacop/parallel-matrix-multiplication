import java.util.ArrayList;

public class Vector {

    public ArrayList<Float> value;

    public Vector(String vector_line) {

        value = new ArrayList<>();
        vector_line = vector_line.substring(1, vector_line.length() - 1);

        String[] vector_elements = vector_line.split(", ");
        for(String element: vector_elements) {

            element = element.substring(1, element.length() - 1);
            value.add(Float.parseFloat(element));
        }
    }
}
