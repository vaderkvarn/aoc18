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
    val powerLevels = Array(size, {IntArray(size)})
    for (i in 0..size - 1) {
        for (j in 0..size - 1) {
            powerLevels[i][j] = getPowerLevel(sn, j + 1, i + 1)
        }
    }
    var maxX = -1
    var maxY = -1
    var maxPl: Int = 0
    var maxSquareSize = -1
    for (ss in 3..300) {
        for (i in 0..size - ss) {
            for (j in 0..size - ss) {
                val pl = getSquarePowerLevel(powerLevels, i, j, ss)
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
