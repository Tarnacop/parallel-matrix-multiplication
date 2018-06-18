class Methods{
    int multiplysum(Vector v, Matrix m){
        int i;
        Accumulator a = new Accumulator();
        for(i = 0; i < m.rowptr.size(); i++){
            Thread t = new Thread(new Multiplyrow(v,m,i,a));
            t.run();
        }
        while(a.count < i){
            //not done
        }
        return a.total;
    }
}

class Accumulator{
    int total = 0;
    int count = 0;
    public synchronized void add(int i){
        this.total+=i;
        this.count++;
    }
}

class Multiplyrow implements Runnable {
    Vector v;
    Matrix m;
    int row;
    int total;
    Accumulator a;

    public Multiplyrow(Vector v, Matrix m, int row, Accumulator a){
        this.v = v;
        this.m = m;
        this.row = row;
        this.a = a;
    }

    public void run(){
        int row_start = m.rowptr.get(row);
    }
}

