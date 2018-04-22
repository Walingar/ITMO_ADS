import java.io.*
import java.lang.Long.max
import java.lang.Integer.max
import java.lang.Long.min
import java.util.*
import kotlin.collections.ArrayList
import kotlin.collections.HashSet


const val fileName = "bring"
const val MAX_N = 100 + 5


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


data class Edge(val from: Int, val to: Int, val capacity: Long, var flow: Long, val x: Int = -1, val y: Int = -1, val haveRev: Boolean = true) {
    lateinit var rev: Edge
}


val edges = Array(MAX_N, { ArrayList<Edge>() })
val scores = IntArray(MAX_N, { 0 })
val table = Array(MAX_N, { CharArray(MAX_N, { '0' }) })
val shouldPlay = Array(MAX_N, { HashSet<Int>() })
val shouldGet = IntArray(MAX_N, { 0 })

var n = 0
var s = 0
var t = 0

fun addEdge(v: Int, u: Int, c: Long) {
    edges[v].add(Edge(v, u, c, 0))
    edges[u].add(Edge(u, v, 0, 0))
    edges[u].last().rev = edges[v].last()
    edges[v].last().rev = edges[u].last()
}


fun input() {
    n = inp.nextInt()
    s = 0
    t = n + 1
    for (i in 1..n) {
        val line = inp.next()
        for (j in 1..n) {
            val res = line[j - 1]
            table[i][j] = res
            when (res) {
                'W' -> {
                    scores[i] += 3
                }
                'w' -> {
                    scores[i] += 2
                }
                'L' -> {
                    scores[i] += 0
                }
                'l' -> {
                    scores[i] += 1
                }
                '.' -> shouldPlay[i].add(j)
            }
        }
    }

    for (i in 1..n) {
        val score = inp.nextInt()
        shouldGet[i] = max(0, score - scores[i])
    }
}

var maxFlow = 0L
val was = BooleanArray(MAX_N, { false })

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

fun findMaxFlow(): Long {
    while (true) {
        was.fill(false)
        val pushedFlow = updateFlow(s, Integer.MAX_VALUE.toLong())
        maxFlow += pushedFlow
        if (pushedFlow == 0L) {
            break
        }
    }
    return maxFlow
}

fun canGet(team: Int): Long {
    var count = 0L
    for (i in shouldPlay[team]) {
        if (i > team) {
            count += 3L
        }
    }
    return count
}

fun solve() {
    // add Edges From S
    for (i in 1..n) {
        addEdge(s, i, canGet(i))
    }
    // add Edges to t
    for (i in 1..n) {
        addEdge(i, t, shouldGet[i].toLong())
    }
    // add other Edges
    for (i in 1..n) {
        for (j in shouldPlay[i]) {
            if (j > i) {
                addEdge(i, j, 3)
            }
        }
    }
    findMaxFlow()
}

fun output() {
    for (i in 1..n) {
        for (edge in edges[i]) {
            if (edge.to != t && edge.to != s && i < edge.to) {
                when (edge.flow) {
                    0L -> {
                        table[i][edge.to] = 'W'
                        table[edge.to][i] = 'L'
                    }
                    1L -> {
                        table[i][edge.to] = 'w'
                        table[edge.to][i] = 'l'
                    }
                    2L -> {
                        table[i][edge.to] = 'l'
                        table[edge.to][i] = 'w'
                    }
                    3L -> {
                        table[i][edge.to] = 'L'
                        table[edge.to][i] = 'W'
                    }
                }
            }
        }
    }

    for (i in 1..n) {
        for (j in 1..n) {
            out.print(table[i][j])
        }
        out.println()
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