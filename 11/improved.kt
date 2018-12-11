/*
    Using https://en.wikipedia.org/wiki/Summed-area_table
 */
val sn: Int = 6392

fun getPowerLevel(sn: Int, x: Int, y: Int): Int {
    val rid = x + 10
    var pl = rid*y
    pl += sn
    pl *= rid
    pl = (pl/100)%10
    pl -= 5
    return pl
}

fun getSquarePowerLevel(arr: Array<IntArray>, i: Int, j: Int, ss: Int): Int {
    var sum: Int = 0
    for (k in 0..ss-1) {
        for (l in 0..ss-1) {
            sum += arr[i+k][j+l]
        }
    }
    return sum
}

fun solve() {
    val size: Int = 300
    val I = Array(size, {IntArray(size)})
    for (i in 1..size - 1) {
        for (j in 1..size - 1) {
            I[i][j] = getPowerLevel(sn, j, i) + I[i][j-1] + I[i-1][j] - I[i-1][j-1]

        }
    }
    var maxX = -1
    var maxY = -1
    var maxPl: Int = 0
    var maxSquareSize = -1
    for (ss in 3..size - 1) {
        for (i in 0..size - ss - 1) {
            for (j in 0..size - ss - 1) {
                val pl = I[i+ss][j+ss] + I[i][j] - I[i+ss][j] - I[i][j+ss]
                if (pl > maxPl) {
                    maxPl = pl
                    maxX = j + 1
                    maxY = i + 1
                    maxSquareSize = ss
                }
            }
        }
        if (ss == 3) {
            println(maxX.toString() + "," + maxY.toString())
        }
    }
    println(maxX.toString() + "," + maxY.toString() + "," + maxSquareSize.toString())
}
fun main(args: Array<String>) {
    solve()
}
