class methods{
    int multiplysum(Vector v, Matrix m){
        int i;
        accumulator a = new accumulator();
        for(i = 0; i < m.rows(); i++){
            Thread t = new Thread(new multiplyrow(v,m,i,a));
            t.run();
        }
        while(a.count < i){
            //not done
        }
        return a.total;
    }
}

class accumulator{
    int total = 0;
    int count = 0;
    public synchronized void add(int i){
        this.total+=i;
        this.count++;
    }
}

class multiplyrow extends Thread{
    Vector v;
    Matrix m;
    int row;
    int total;
    accumulator a;

    public void run(){
        int row_start = m.rowptr.get(row);
        
    }

    public void multiplyrow(Vector v, Matrix m, int row, accumulator a){
        this.v = v;
        this.m = m;
        this.row = row;
        this.a = a;
    }

}

