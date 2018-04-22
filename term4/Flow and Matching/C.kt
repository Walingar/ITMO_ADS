import java.io.*
import java.lang.Integer.min
import java.util.*
import kotlin.collections.ArrayList
import kotlin.collections.HashMap
import kotlin.collections.HashSet


const val fileName = "snails"
const val MAX_V = 100_000 + 5
const val MAX_E = 100_000 + 5
const val MAX_C = 10_000 + 5
var s = 1
var t = 1

class FastScanner(f: File) {
    private lateinit var br: BufferedReader
    private var st: StringTokenizer? = null

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
        return next().toInt()
    }

    fun nextDouble(): Double {
        return next().toDouble()
    }
}

var inp = FastScanner(File("$fileName.in"))
var out = File("$fileName.out").printWriter()

class Tube(val v: Int, val c: Int, var flow: Int)

val edges = Array<ArrayList<Tube>>(MAX_V, { ArrayList() })
var n = 0
var m = 0
val edgesBack = HashMap<Pair<Int, Int>, Tube>()
var maxFlow = 0
val tubes = ArrayList<Tube>()

fun input() {
    n = inp.nextInt()
    m = inp.nextInt()
    s = inp.nextInt()
    t = inp.nextInt()
    for (i in 1..m) {
        val v = inp.nextInt()
        val u = inp.nextInt()
        edges[v].add(Tube(u, 1, 0))
        edges[u].add(Tube(v, 0, 0))
        edgesBack[Pair(v, u)] = edges[u].last()
        edgesBack[Pair(u, v)] = edges[v].last()
    }
}

val was = Array(MAX_V, { false })

fun updateFlow(v: Int, Cmin: Int): Int {
    if (v == t) {
        return Cmin
    }
    was[v] = true

    for (to in edges[v]) {
        if (!was[to.v] && to.flow < to.c) {
            val delta = updateFlow(to.v, min(Cmin, to.c - to.flow))
            if (delta > 0) {
                to.flow += delta
                edgesBack[Pair(v, to.v)]!!.flow -= delta
                return delta
            }
        }
    }
    return 0
}

fun findMaxFlow() {
    while (true) {
        was.fill(false)
        val pushedFlow = updateFlow(s, 1000_000_000)
        maxFlow += pushedFlow
        if (pushedFlow == 0) {
            break
        }
    }
}

fun solve() {
    findMaxFlow()
}

fun output() {
    if (maxFlow >= 2) {
        out.println("YES")
        var to = s
        val was = HashSet<Tube>()
        while (to != t) {
            out.print(to.toString() + " ")
            for (tube in edges[to]) {
                if (tube !in was && tube.flow == 1) {
                    was.add(tube)
                    to = tube.v
                    break
                }
            }
        }
        to = s
        out.println(t)
        while (to != t) {
            out.print(to.toString() + " ")
            for (tube in edges[to]) {
                if (tube !in was && tube.flow == 1) {
                    was.add(tube)
                    to = tube.v
                    break
                }
            }
        }
        out.println(t)
    } else {
        out.print("NO")
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