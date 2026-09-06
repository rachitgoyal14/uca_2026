package dsa.design.snakeGame;
import java.util.*;


// // // // HINT // // // //
// try solving it for 2 X 2 matrix
// if you can solve it for a 2 X 2 matrix, then you can solve it for any kind of matrix

public class snakeGame {
    private int width;
    private int height;
    private int[][] food;
    private int[][] gameArea;
    private int score;
    private int[] head = {0, 0};
    private int[] tail = {0, 0};
    private int foodIndex;
    
    public snakeGame(int width, int height, int[][] food) {
        this.width = width;
        this.height = height;
        this.food = food;
        this.gameArea = new int[height][width];
        
        // initialize the game area
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                gameArea[i][j] = 0;
            }
        }

        // spawn the initial apple
        food[0][0] = 1;
        food[0][1] = 1;

        // set the initial position of snake (head & tail)
        gameArea[0][0] = 1;
        
    }

    private void spawnFood(int foodIndex) {
        food[foodIndex][0] = 1;
        food[foodIndex][1] = 1;
    }

    public int move(String direction) {
        if (direction.equals("R")) {
            head = 
        } else if (direction.equals("L")) {

        } else if (direction.equals("U")) {

        } else if (direction.equals("D")) {

        }

        if (head[0] == currFoodPos)        

        return 0;
    }
}