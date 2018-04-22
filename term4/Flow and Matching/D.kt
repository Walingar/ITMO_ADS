import java.io.*
import java.util.*
import kotlin.collections.ArrayList


const val fileName = "snails"
const val MAX_V = 250 + 5
const val MAX_E = 250 + 5
const val MAX_C = 10_000 + 5

class FastScanner(f: InputStream) {
    private lateinit var br: BufferedReader
    private var st: StringTokenizer? = null

    init {
        try {
            br = BufferedReader(InputStreamReader(f))
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
        return next().toInt()
    }

    fun nextDouble(): Double {
        return next().toDouble()
    }
}

//var inp = FastScanner(File("$fileName.in").inputStream())
//var out = File("$fileName.out").printWriter()

var inp = FastScanner(System.`in`)
var out = System.out

val edges = Array<ArrayList<Int>>(MAX_V, { ArrayList() })
var n = 0
var m = 0


fun input() {
    n = inp.nextInt()
    m = inp.nextInt()
    for (v in 1..n) {
        var u = inp.nextInt()
        while (u != 0) {
            edges[v].add(u)
            u = inp.nextInt()
        }
    }
}

val was = Array(MAX_V, { false })
val matching = IntArray(MAX_V, { -1 })

fun kuhn(v: Int): Boolean {
    if (was[v]) {
        return false
    }
    was[v] = true

    for (u in edges[v]) {
        if (matching[u] == -1 || kuhn(matching[u])) {
            matching[u] = v
            return true
        }
    }
    return false
}

var counter = 0

fun solve() {
    for (i in 1..n) {
        was.fill(false)
        if (kuhn(i)) {
            counter++
        }
    }
}

fun output() {
    out.println(counter)
    for (i in 1..m) {
        if (matching[i] != -1) {
            out.println(matching[i].toString() + " " + i)
        }
    }
}

fun main(args: Array<String>) {
    try {
        input()
        solve()
        output()
        out.close()
    } catch (e: IOException) {
        e.printStackTrace()
    }
}