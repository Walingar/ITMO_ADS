import java.io.*
import java.lang.Long.min
import java.util.*
import kotlin.collections.ArrayList


const val fileName = "bring"
const val MAX_N = 50 + 5
const val MAX_DAYS = 10000 + 5


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

var inp = FastScanner(File("$fileName.in").inputStream())
var out = File("$fileName.out").printWriter()

//var inp = FastScanner(System.`in`)
//var out = System.out


data class Edge(val from: Int, val to: Int, val capacity: Long, var flow: Long, val x: Int = -1, val y: Int = -1, val haveRev: Boolean = true) {
    lateinit var rev: Edge
}


val edges = Array(MAX_N * MAX_DAYS, { ArrayList<Edge>() })
var n = 0
var m = 0
var s = 0
var t = 0
var k = 0


fun getId(day: Int, v: Int) = day * n + v

fun addEdge(v: Int, u: Int, c: Long) {
    edges[v].add(Edge(v, u, c, 0))
    edges[u].add(Edge(u, v, 0, 0))
    edges[u].last().rev = edges[v].last()
    edges[v].last().rev = edges[u].last()
}

val from = IntArray(200 + 5, { -1 })
val to = IntArray(200 + 5, { -1 })


fun input() {
    n = inp.nextInt()
    m = inp.nextInt()
    k = inp.nextInt()
    s = inp.nextInt() - 1
    t = inp.nextInt() - 1
    for (v in 0 until m) {
        from[v] = inp.nextInt() - 1
        to[v] = inp.nextInt() - 1
    }
}

var maxFlow = 0L
val was = BooleanArray(MAX_DAYS * MAX_N, { false })

fun updateFlow(v: Int, Cmin: Long): Long {
    if (v == t) {
        return Cmin
    }
    was[v] = true

    for (to in edges[v]) {
        if (!was[to.to] && to.flow < to.capacity) {
            val delta = updateFlow(to.to, min(Cmin, to.capacity - to.flow))
            if (delta > 0) {
                to.flow += delta
                to.rev.flow -= delta
                return delta
            }
        }
    }
    return 0
}

fun findMaxFlow(to: Int, last: Long): Long {
    while (true) {
        was.fill(false, 0, to)
        val pushedFlow = updateFlow(s, last - maxFlow)
        maxFlow += pushedFlow
        if (pushedFlow == 0L || maxFlow == last) {
            break
        }
    }
    return maxFlow
}

var daysAns = 1

fun solve() {
    var count = 0L
    while (count != k.toLong()) {
        for (i in 0 until n) {
            addEdge(getId(daysAns - 1, i), getId(daysAns, i), Integer.MAX_VALUE.toLong())
        }
        for (i in 0 until m) {
            addEdge(getId(daysAns - 1, from[i]), getId(daysAns, to[i]), 1)
            addEdge(getId(daysAns - 1, to[i]), getId(daysAns, from[i]), 1)
        }
        val tempT = t
        t = getId(daysAns, t)
        maxFlow = 0
        count += findMaxFlow(getId(daysAns, n), k - count)
        daysAns++
        t = tempT
    }
}

fun output() {
    out.println(--daysAns)

    val ships = IntArray(k + 5, { s })
    var sb: StringBuilder
    var counter: Int
    for (day in 1..daysAns) {
        sb = StringBuilder()
        counter = 0
        for (ship in 1..k) {
            for (edge in edges[ships[ship]]) {
                if (edge.flow >= 1L) {
                    edge.flow -= 1
                    ships[ship] = edge.to
                    if (edge.capacity != Integer.MAX_VALUE.toLong()) {
                        counter++
                        sb.append(String.format(" %d %d", ship, edge.to % n + 1))
                    }
                    break
                }
            }
        }
        out.println(counter.toString() + sb.toString())
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