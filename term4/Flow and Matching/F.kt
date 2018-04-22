import java.io.*
import java.lang.Math.sqrt
import java.util.*
import kotlin.collections.ArrayList


const val fileName = "snails"
const val MAX_N = 50 + 5
const val MAX_M = 50 + 5
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


data class Item(val x: Double, val y: Double, val speed: Double)


var edges = Array<ArrayList<Int>>(MAX_N, { ArrayList() })
var matching = IntArray(MAX_N, { -1 })
val was = Array(MAX_N, { false })
val positions = ArrayList<Pair<Double, Double>>()
val items = ArrayList<Item>()
var n = 0
var m = 0


fun input() {
    n = inp.nextInt()
    for (i in 0 until n) {
        items.add(Item(inp.nextDouble(), inp.nextDouble(), inp.nextDouble()))
    }
    for (i in 0 until n) {
        positions.add(Pair(inp.nextDouble(), inp.nextDouble()))
    }
}

const val Eps = 0.00001

fun distance(item: Item, pos: Pair<Double, Double>) = sqrt(
        (item.x - pos.first) * (item.x - pos.first) + (item.y - pos.second) * (item.y - pos.second)
)

fun neededTime(item: Item, pos: Pair<Double, Double>) = distance(item, pos) / item.speed

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

fun res(time: Double): Boolean {
    edges = Array(MAX_N, { ArrayList<Int>() })
    for (i in 0 until n) {
        for (j in 0 until n) {
            if (neededTime(items[i], positions[j]) <= time) {
                edges[i].add(j)
            }
        }
    }
    matching = IntArray(MAX_N, { -1 })

    var counter = 0
    for (v in 0 until n) {
        was.fill(false)
        if (kuhn(v)) {
            counter++
        }
    }

    return counter == n

}

fun solve() {
    var l = 0.0
    var r = Integer.MAX_VALUE.toDouble()

    while (r - l > Eps) {
        val m = (l + r) / 2
        if (res(m)) {
            r = m
        } else {
            l = m
        }
    }

    out.println(String.format("%.5f",l))
}

fun output() {

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