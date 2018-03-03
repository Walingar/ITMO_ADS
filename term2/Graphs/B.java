import javafx.util.Pair;
 
import java.io.*;
import java.util.*;
 
public class Main {
    private FastScanner in;
    private PrintWriter out;
 
    private int n, m, fromPos, toPos;
    boolean check = false;
    @SuppressWarnings("unchecked")
    private ArrayList<ArrayList<edge>> edges = new ArrayList<>();
    private ArrayDeque<Integer> q = new ArrayDeque<>();
    private ArrayList<Integer> d = new ArrayList<>();
    private ArrayList<Boolean> was = new ArrayList<>();
    public class CustomComparator implements Comparator<edge> {
        @Override
        public int compare(edge o1, edge o2) {
            return o1.getValue().compareTo(o2.getValue());
        }
    }
 
    private void bfs() throws IOException {
 
    }
 
    private void input() throws IOException {
        n = in.nextInt();
        m = in.nextInt();
        for (int i = 0; i < n; i++) {
            ArrayList<edge> temp = new ArrayList<>();
            edges.add(temp);
            d.add(0);
            was.add(false);
        }
        for (int i = 0; i < m; i++) {
            int x = in.nextInt() - 1;
            int y = in.nextInt() - 1;
            edges.get(x).add(new edge(x, y, 0));
            edges.get(y).add(new edge(y, x, 0));
        }
        q.addLast(0);
        was.set(0, true);
    }
 
 
    private void solve() throws IOException {
        input();
        while(!q.isEmpty()) {
            int v = q.pop();
            //out.print(v);
            for(int i = 0; i < edges.get(v).size(); i++) {
                int to = edges.get(v).get(i).to;
                if (!was.get(to)) {
                    was.set(to, true);
                    d.set(to, d.get(v) + 1);
                    q.addLast(to);
                }
            }
        }
        output();
    }
 
    private void output() throws IOException {
        for(int i = 0; i < n; i++) {
            out.print(d.get(i) + " ");
        }
    }
 
    private void run() {
        try {
            String fileName = "pathbge1";
            in = new FastScanner(new File(fileName + ".in"));
            out = new PrintWriter(new File(fileName + ".out")); // PrintWriter(System.out) || new File("output" + ".out")
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f)); //InputStreamReader(System.in) || new FileReader(f)
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    public static void main(String[] arg) {
        new Main().run();
    }
 
    private class unionSet {
        int[] parent = new int[20000];
        int[] rank = new int[20000];
 
        private void make_set(int v) {
            parent[v] = v;
            rank[v] = 0;
        }
 
        private int find_set(int v) {
            if (v == parent[v]) {
                return v;
            }
            return parent[v] = find_set(parent[v]);
        }
 
        private void union_sets(int a, int b) {
            a = find_set(a);
            b = find_set(b);
            if (a != b) {
                if (rank[a] < rank[b]) {
                    int c = b;
                    b = a;
                    a = c;
                }
                parent[b] = a;
                if (rank[a] == rank[b]) {
                    rank[a]++;
                }
            }
        }
    }
 
    private class edge {
        Integer from;
        Integer to;
        Integer w;
 
        edge(int x, int y, int z) {
            from = x;
            to = y;
            w = z;
        }
 
        public Integer getValue() {
            return w;
        }
    }
}