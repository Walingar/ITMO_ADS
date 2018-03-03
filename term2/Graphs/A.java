import javafx.util.Pair;
 
import java.lang.reflect.Array;
import java.util.*;
import java.io.*;
 
public class Main {
    private FastScanner in;
    private PrintWriter out;
 
    private int n, m;
    private ArrayList<Pair<Pair<Integer, Integer>, Integer>> edges = new ArrayList<>();
    int cost = 0;
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
 
    public class CustomComparator implements Comparator<Pair<Pair<Integer, Integer>, Integer>> {
        @Override
        public int compare(Pair<Pair<Integer, Integer>, Integer> o1, Pair<Pair<Integer, Integer>, Integer> o2) {
            return o1.getValue().compareTo(o2.getValue());
        }
    }
 
    private void input() throws IOException {
        n = in.nextInt();
        m = in.nextInt();
        for (int i = 0; i < m; i++) {
            edges.add(new Pair<>(new Pair<>(in.nextInt(), in.nextInt()), in.nextInt()));
        }
        edges.sort(new CustomComparator());
        for (int i = 0; i < n; i++) {
            make_set(i);
        }
    }
 
 
    private void solve() throws IOException {
        input();
        for (int i = 0; i < m; i++) {
            int from = edges.get(i).getKey().getKey();
            int to = edges.get(i).getKey().getValue();
            int w = edges.get(i).getValue();
            if (find_set(from) != find_set(to)) {
                cost += w;
                union_sets(from, to);
            }
        }
        output();
    }
 
    private void output() throws IOException {
        out.print(cost);
    }
 
    private void run() {
        try {
            String fileName = "spantree2";
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
}