class Accumulator {
        float total;

        public Accumulator() {

            total = 0;
        }

        public synchronized void add(float number) {
            this.total += number; }
}

class Multiplyrow implements Runnable {
        Vector v;
        Matrix m;
        int rowStart;
        int rowEnd;
        float total;
        Accumulator a;

        public Multiplyrow(Vector v, Matrix m, int rowStart, Accumulator a) {
            this.v = v;
            this.m = m;
            this.rowStart = rowStart;
            this.rowEnd = m.rowptr.size() - 1;
            this.total = 0;
            this.a = a;
        }

        public Multiplyrow(Vector v, Matrix m, int rowStart, int rowEnd, Accumulator a) {
            this.v = v;
            this.m = m;
            this.rowStart = rowStart;
            this.rowEnd = rowEnd;
            this.total = 0;
            this.a = a;
        }

        public void run() {

            for (int i = m.rowptr.get(rowStart); i < m.rowptr.get(rowEnd); i++) {

                total += m.value.get(i) * v.value.get(m.column.get(i));
            }
            a.add(total);
        }
    }
