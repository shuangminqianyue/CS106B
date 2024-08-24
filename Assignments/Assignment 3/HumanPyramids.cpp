#include "HumanPyramids.h"
#include "error.h"
#include "grid.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */

double weightOnBackOfHelper(int row, int col, int pyramidHeight,
                            Grid<double>& g) {
    // set a person as 160 bounds
    // error check
    if (row < 0 || col < 0 || row >= pyramidHeight || col >= pyramidHeight) {
        error("The input coordinates are out of bounds!");
    }
    int height = row + 1;
    double weight;

    // base case
    if (height == 1) {
        return 0;
    } else if (g[row][col] != 0.0) {
        return g[row][col]; // 递归中存过结果直接调用
    } else {
        // 递归，存新结果
        if (col == 0) {
            weight = 80 + weightOnBackOfHelper(row - 1, col, height - 1, g) / 2.0;
        } else if (col == pyramidHeight - 1) {
            weight = 80 + weightOnBackOfHelper(row - 1, col - 1, height - 1, g) / 2.0;
        } else {
            weight = 160 + weightOnBackOfHelper(row - 1, col, height - 1, g) / 2.0 +
                   weightOnBackOfHelper(row - 1, col - 1, height - 1, g) / 2.0;
        }
        g[row][col] = weight;
        return weight;
    }
}


double weightOnBackOf(int row, int col, int pyramidHeight) {
    Grid<double> g(row + 1, col + 1, 0.0);
    return weightOnBackOfHelper(row, col, pyramidHeight, g);
}





/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
STUDENT_TEST("Check Person A from the handout.") {
    // row 0, col 0
    EXPECT_EQUAL(weightOnBackOf(0, 0, 5), 0);
}


STUDENT_TEST("Check Person D from the handout.") {
    // row 2, col 0
    EXPECT_EQUAL(weightOnBackOf(2, 0, 5), 120);
}










/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    // SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
