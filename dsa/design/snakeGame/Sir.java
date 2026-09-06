package dsa.design.snakeGame;
import java.util.*;

class SnakeGame {

    class Coordinate {
        int x;
        int y;

        Coordinate(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Coordinate)) return false;
            Coordinate that = (Coordinate) o;
            return x == that.x && y == that.y;
        }

        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }
    }

    private Deque<Coordinate> snakeTracker;
    private Set<Coordinate> usedCoordinates;
    private int width;
    private int height;
    private int[][] food;
    private int foodIndex;

    public SnakeGame(int width, int height, int[][] food) {
        this.snakeTracker = new ArrayDeque<>();
        this.width = width;
        this.height = height;
        this.food = food;
        this.foodIndex = 0;
        this.usedCoordinates = new HashSet<>();

        Coordinate start = new Coordinate(0, 0);
        snakeTracker.addFirst(start);
        usedCoordinates.add(start);
    }

    public int move(String direction) {
        Coordinate head = snakeTracker.peekFirst();
        Coordinate newHead = moveSnake(direction, head);

        if (isCoordinatesInvalid(newHead)) {
            return -1;
        }

        boolean isFoodEaten = (foodIndex < food.length)
                && (newHead.x == food[foodIndex][0] && newHead.y == food[foodIndex][1]);

        if (!isFoodEaten) {
            Coordinate tail = snakeTracker.removeLast();
            usedCoordinates.remove(tail);
        }

        if (usedCoordinates.contains(newHead)) {
            return -1;
        }

        snakeTracker.addFirst(newHead);
        usedCoordinates.add(newHead);

        if (isFoodEaten) {
            foodIndex++;
        }

        return snakeTracker.size() - 1;
    }

    private Coordinate moveSnake(String direction, Coordinate current) {
        if (direction.equals("U")) {
            return new Coordinate(current.x - 1, current.y);
        } else if (direction.equals("D")) {
            return new Coordinate(current.x + 1, current.y);
        } else if (direction.equals("L")) {
            return new Coordinate(current.x, current.y - 1);
        } else if (direction.equals("R")) {
            return new Coordinate(current.x, current.y + 1);
        }
        throw new IllegalArgumentException("Direction not supported");
    }

    private boolean isCoordinatesInvalid(Coordinate coordinate) {
        return coordinate.x < 0 || coordinate.y < 0
                || coordinate.x >= height || coordinate.y >= width;
    }
}

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */