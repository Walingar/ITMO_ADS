import java.io.*
import java.lang.Math.abs
import java.util.*
import kotlin.collections.ArrayList


const val fileName = "snails"
const val MAX_N = 100 + 5
const val MAX_M = 100 + 5
const val MAX_E = 100 + 5
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

class Edge(val to: Int, val x: Int, val y: Int, var flow: Int = 0) {
    lateinit var reversed: Edge
}

var edges = Array<ArrayList<Edge>>(4 * (MAX_M + MAX_N), { ArrayList() })
val table = Array(MAX_N, { IntArray(MAX_M) })
var n = 0
var m = 0


fun input() {
    n = inp.nextInt()
    m = inp.nextInt()

    for (i in 0 until n) {
        val line = inp.next()
        for (j in 0 until m) {
            if (line[j] == 'W') {
                table[i][j] = (i + j) % 2
            } else {
                table[i][j] = abs((i + j) % 2 - 1)
            }
        }
    }
}

val was = Array(4 * (MAX_M + MAX_N), { false })

fun kuhn(v: Int): Boolean {
    if (v == 4 * (n + m)) {
        return true
    }
    was[v] = true
    for (edge in edges[v]) {
        if (edge.flow == 1 && !was[edge.to] && kuhn(edge.to)) {
            edge.flow = 0
            edge.reversed.flow = 1
            return true
        }
    }
    return false
}

fun addEdges(from: Int, to: Int, i: Int, j: Int) {
    val edge = Edge(to, i, j, 1)
    val reversedEdge = Edge(from, i, j, 0)

    edge.reversed = reversedEdge
    reversedEdge.reversed = edge

    edges[from].add(edge)
    edges[to].add(reversedEdge)
}

data class Answer(val type: Int, val x: Int, val y: Int)

fun getAnswer(): Array<Answer> {
    edges = Array(4 * (MAX_M + MAX_N), { ArrayList<Edge>() })
    for (i in 0 until n) {
        for (j in 0 until m) {
            if (table[i][j] == 1) {
                addEdges(i - j + n + m, i + j + 2 * (n + m), i + 1, j + 1)
            }
        }
    }

    // add s
    for (i in 1 until 2 * (n + m)) {
        addEdges(0, i, i + 1, i + 1)
    }

    // add t
    for (i in 2 * (n + m) until 4 * (n + m)) {
        addEdges(i, 4 * (n + m), i + 1, i + 1)
    }

    var counter = 0

    while (true) {
        was.fill(false)
        if (!kuhn(0)) {
            break
        }
        counter++
    }

    val answer = Array(counter, { Answer(0, 0, 0) })
    var t = 0

    for (i in 0 until 2 * (n + m)) {
        if (!was[i]) {
            for (edge in edges[i]) {
                if (edge.to != 0) {
                    answer[t] = Answer(2, edge.x, edge.y)
                    t++
                    break
                }
            }
        }
    }

    for (i in 2 * (n + m) until 4 * (n + m)) {
        if (was[i]) {
            for (edge in edges[i]) {
                if (edge.to != 4 * (n + m)) {
                    answer[t] = Answer(1, edge.x, edge.y)
                    t++
                    break
                }
            }
        }
    }
    return answer
}

var res = Array(0, { Answer(0, -1, -1) })
var type = 0

fun swapColors() {
    for (i in 0 until n) {
        for (j in 0 until m) {
            table[i][j] = 1 - table[i][j]
        }
    }
}

fun solve() {
    val resWB = getAnswer()
    swapColors()
    val resBW = getAnswer()

    if (resBW.size <= resWB.size) {
        res = resBW
        type = 1
    } else {
        res = resWB
        type = 0
    }
}

fun output() {
    out.println(res.size)
    for (i in 0 until res.size) {
        out.println(String.format(
                "%d %d %d %s",
                res[i].type,
                res[i].x,
                res[i].y,
                if ((res[i].x + res[i].y) % 2 == type) "W" else "B"
        ))
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