import java.util.*
import java.io.*
import kotlin.collections.ArrayList
 
class lca {
    lateinit private var `in`: FastScanner
    lateinit private var out: PrintWriter
    private val fileName = "lca"
    private var currentLine = ""
    val maxN = 5 * 10_000 + 10
    var log = 1
    var N = 0
    var up = Array(maxN, { Array(2, { 0 }) })
    val timeIn = Array(maxN, { 0 })
    val timeOut = Array(maxN, { 0 })
    val parents = Array(maxN, { 0 })
    val d = Array(maxN, { 0 })
    val edges = Array(maxN, { ArrayList<Int>() })
    val counter = ArrayList<Int>()
 
    @Throws(IOException::class)
    fun solve() {
        N = nextInt()
        while ((1 shl log) <= N) log++
        counter.add(1)
        for (i in 1..log + 1) counter.add(1 shl i)
        up = Array(maxN, { Array(log + 1, { 0 }) })
        for (v in 1 until N) {
            val u = nextInt() - 1
            parents[v] = u
            edges[u].add(v)
        }
        dfs(0)
        val M = nextInt()
        for (i in 1..M) {
            out.println(lca(nextInt() - 1, nextInt() - 1))
        }
 
    }
 
    fun lca(vTemp: Int, uTemp: Int): Int {
        var v = vTemp
        var u = uTemp
        if (d[v] > d[u]) {
            val temp = v
            v = u
            u = temp
        }
        for (i in log downTo 0)
            if (d[u] - d[v] >= counter[i])
                u = up[u][i]
        if (v == u)
            return v + 1
        for (i in log downTo 0)
            if (up[v][i] != up[u][i]) {
                v = up[v][i]
                u = up[u][i]
            }
        return parents[v] + 1
    }
 
    var timer = 0
    var depth = 0
    fun dfs(v: Int, p: Int = 0) {
        timeIn[v] = ++timer
        d[v] = depth
        up[v][0] = p
        for (i in 1..log)
            up[v][i] = up[up[v][i - 1]][i - 1]
        for (to in edges[v])
            if (to != p) {
                depth++
                dfs(to, v)
                depth--
            }
        timeOut[v] = ++timer
    }
 
    fun upper(v: Int, u: Int) = timeIn[v] <= timeIn[u] && timeOut[v] >= timeOut[u]
 
    fun nextInt() = `in`.nextInt()
 
    fun next() = `in`.br.readLine()
 
    fun run() {
        try {
            `in` = FastScanner(File(fileName + ".in"))
            out = PrintWriter(File(fileName + ".out"))
 
            solve()
 
            out.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }
 
    }
 
    class FastScanner(f: File) {
        lateinit var br: BufferedReader
        var st: StringTokenizer? = null
 
        init {
            try {
                br = BufferedReader(FileReader(f))
            } catch (e: FileNotFoundException) {
                e.printStackTrace()
            }
 
        }
 
        operator fun next(): String {
            while (st == null || !st!!.hasMoreTokens()) {
                try {
                    st = StringTokenizer(br.readLine())
                } catch (e: IOException) {
                    e.printStackTrace()
                }
 
            }
            return st!!.nextToken()
        }
 
        fun nextInt(): Int {
            return Integer.parseInt(next())
        }
    }
 
    companion object {
        @JvmStatic
        fun main(arg: Array<String>) {
            lca().run()
        }
    }
}