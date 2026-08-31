package dsa.hashing.maxNumberOfPointsOnStraightLine;

import java.util.*;

class Coordinate {
    int x;
    int y;

    Coordinate(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public class Main {

    private static int gcd(int a, int b) {
        while (a != b){
            if (a > b)
                a = a - b;
            else b = b - a;
        }
        return a;
    }

    public static int maxPoints(int[][] points) {
        int maxPoints = 0;

        // < slope, number of points >

        for (int i = 0; i < points.length; i++) {
            HashMap<Double, Integer> map = new HashMap<>();
            int currentMax = 0;

            for (int j = 0; j < points.length && j != i; j++) {
                int deltaX = points[j][0] - points[i][0];
                int deltaY = points[j][1] - points[i][1];

                int gcd = gcd(deltaX, deltaY);
                
                deltaX /= gcd;
                deltaY /= gcd;

                double slope;

                if (deltaX == 0) {
                    slope = Double.MAX_VALUE; // denotes a vertical line
                } else {
                    slope = (double) deltaY / deltaX;
                }

                map.put(slope, map.getOrDefault(slope, 0) + 1);
            }

            for (int count : map.values()) {
                currentMax = Math.max(currentMax, count + 1);
            }

            maxPoints = Math.max(maxPoints, currentMax);
        }

        return maxPoints;
    }

    public static void main(String[] args) {
        int[][] points1 = {
            {1, 1},
            {2, 2},
            {3, 3}
        };

        int[][] points2 = {
            {1, 1},
            {3, 2},
            {5, 3},
            {4, 1},
            {2, 3},
            {1, 4}
        };

        // Answer is 4
        int[][] points3 = {
            {3, 1},
            {3, 2},
            {3, 5},
            {3, 10}
        };

        // Answer is 4
        int[][] points4 = {
            {1, 1},
            {2, 2},
            {3, 3},
            {4, 4}
        };

        // Answer is 4
        int[][] points5 = {
            {1, 5},
            {2, 4},
            {3, 3},
            {4, 2}
        };

        // Answer is 5
        int[][] points6 = {
            {-3, -3},
            {-2, -2},
            {-1, -1},
            {0, 0},
            {1, 1}
        };

        int[][] points7 = {
            {-3, 3},
            {-2, 2},
            {-1, 1},
            {0, 0},
            {1, -1}
        };

        int[][] points8 = {
            {1, 1},
            {1, 1},
            {2, 2},
            {3, 3}
        };

        // Expected: 4
        int[][] points9 = {
            {1, 1},
            {2, 2},
            {3, 3},
            {4, 4},
            {1, 5},
            {2, 5},
            {3, 5}
        };

        int maxPointsOnSingleLine = maxPoints(points1);

        System.out.println(maxPointsOnSingleLine);
    }
}