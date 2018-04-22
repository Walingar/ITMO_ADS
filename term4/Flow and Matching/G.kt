import java.io.*
import java.lang.Long.min
import java.util.*
import kotlin.collections.ArrayList


const val fileName = "snails"
const val MAX_N = 100 + 5
const val MAX_M = 100 + 5

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


val edges = Array(MAX_N * MAX_M, { ArrayList<Edge>() })
val shortestPaths = IntArray(MAX_N * MAX_M, { -1 })
val deletedV = IntArray(MAX_N * MAX_M, { 0 })
var n = 0
var m = 0
var s = 0
var t = 0
var maxFlow = 0L
val kingdomMap = Array(MAX_N, { CharArray(MAX_M) })

fun getIndex(i: Int, j: Int) = i * m + j

fun getDoubledIndex(i: Int, j: Int) = i * m + j + n * m

fun addEdge(v: Int, u: Int, c: Long) {
    edges[v].add(Edge(v, u, c, 0))
    edges[u].add(Edge(u, v, 0, 0))
    edges[u].last().rev = edges[v].last()
    edges[v].last().rev = edges[u].last()
}

fun addOrEdge(v: Int, u: Int, c: Long, x: Int, y: Int, rev: Boolean) {
    edges[v].add(Edge(v, u, c, 0, x, y, rev))
}

fun input() {
    n = inp.nextInt()
    m = inp.nextInt()

    for (i in 0 until n) {
        val line = inp.next()
        for (j in 0 until m) {
            kingdomMap[i][j] = line[j]
            when (kingdomMap[i][j]) {
                '-' -> addOrEdge(getIndex(i, j), getDoubledIndex(i, j), Integer.MAX_VALUE.toLong(), i, j, false)
                '.' -> addOrEdge(getIndex(i, j), getDoubledIndex(i, j), 1, i, j, false)
                '#' -> addOrEdge(getIndex(i, j), getDoubledIndex(i, j), 0, i, j, false)
                'A' -> s = getDoubledIndex(i, j)
                'B' -> t = getIndex(i, j)
            }
        }
    }

    for (i in 0 until n - 1) {
        for (j in 0 until m - 1) {
            addEdge(getDoubledIndex(i, j), getIndex(i + 1, j), Integer.MAX_VALUE.toLong())
            addEdge(getDoubledIndex(i + 1, j), getIndex(i, j), Integer.MAX_VALUE.toLong())
            addEdge(getDoubledIndex(i, j), getIndex(i, j + 1), Integer.MAX_VALUE.toLong())
            addEdge(getDoubledIndex(i, j + 1), getIndex(i, j), Integer.MAX_VALUE.toLong())
        }
    }
    for (i in 0 until n - 1) {
        addEdge(getDoubledIndex(i, m - 1), getIndex(i + 1, m - 1), Integer.MAX_VALUE.toLong())
        addEdge(getDoubledIndex(i + 1, m - 1), getIndex(i, m - 1), Integer.MAX_VALUE.toLong())
    }
    for (j in 0 until m - 1) {
        addEdge(getDoubledIndex(n - 1, j), getIndex(n - 1, j + 1), Integer.MAX_VALUE.toLong())
        addEdge(getDoubledIndex(n - 1, j + 1), getIndex(n - 1, j), Integer.MAX_VALUE.toLong())
    }


}

val was = Array(MAX_N * MAX_M, { false })

fun findShortestPaths(): Boolean {
    shortestPaths.fill(-1)
    val bfsQueue = ArrayDeque<Int>()
    bfsQueue.add(s)
    shortestPaths[s] = 0

    while (bfsQueue.isNotEmpty()) {
        val v = bfsQueue.poll()
        for (to in edges[v]) {
            if (shortestPaths[to.to] == -1 && to.flow < to.capacity) {
                shortestPaths[to.to] = shortestPaths[v] + 1
                bfsQueue.add(to.to)
            }
        }
    }

    return shortestPaths[t] != -1
}

fun updateFlow(v: Int, Cmin: Long): Long {
    if (v == t) {
        return Cmin
    }

    for (i in deletedV[v] until edges[v].size) {
        val to = edges[v][i]
        if (to.flow < to.capacity && shortestPaths[to.to] == shortestPaths[v] + 1) {
            val delta = updateFlow(to.to, min(Cmin, to.capacity - to.flow))
            if (delta > 0) {
                to.flow += delta
                if (to.haveRev) {
                    to.rev.flow -= delta
                }
                return delta
            }
        }
        deletedV[v] = i + 1
    }
    return 0
}

fun findMaxFlow(): Long {
    while (true) {
        if (!findShortestPaths()) {
            break
        }
        deletedV.fill(0)
        while (true) {
            val pushedFlow = updateFlow(s, Integer.MAX_VALUE.toLong())
            maxFlow += pushedFlow
            if (pushedFlow == 0L) {
                break
            }
        }
    }
    return maxFlow
}

val markedList = ArrayList<Int>()

fun marking(v: Int, marked: Array<Boolean>) {
    marked[v] = true
    markedList.add(v)
    for (tube in edges[v]) {
        if (!marked[tube.to]) {
            if (tube.flow < tube.capacity) {
                marking(tube.to, marked)
            }
        }
    }
}

fun findMinCut() {
    val marked = Array(MAX_N * MAX_M, { false })
    marking(s, marked)

    for (v in markedList) {
        for (tube in edges[v]) {
            if (!marked[tube.to] && tube.flow == 1L) {
                kingdomMap[tube.x][tube.y] = '+'
                break
            }
        }
    }
}

fun solve() {
    findMaxFlow()
    findMinCut()
}

fun output() {
    if (maxFlow >= Integer.MAX_VALUE) {
        out.print(-1)
        return
    }

    out.println(maxFlow)
    for (i in 0 until n) {
        for (j in 0 until m) {
            out.print(kingdomMap[i][j])
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