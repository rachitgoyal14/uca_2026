# Min Stack

Design a stack that supports **push**, **pop**, **top**, and **retrieving the minimum element** - all in **O(1)** time.

Implement the `MinStack` class:

```java
class MinStack {
    public MinStack() { }

    public void push(int val) { }

    public void pop() { }

    public int top() { }

    public int getMin() { }
}
```

### Methods

- `MinStack()` initializes the stack object.
- `void push(int val)` pushes the element `val` onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

## Example

### Input

```text
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
```

### Output

```text
[null,null,null,null,-3,null,0,-2]
```

### Explanation

```java
MinStack minStack = new MinStack();

minStack.push(-2);
minStack.push(0);
minStack.push(-3);

minStack.getMin(); // return -3

minStack.pop();

minStack.top();    // return 0

minStack.getMin(); // return -2
```

## Constraints

- All operations must be **O(1)** time complexity.
- `-2^31 <= val <= 2^31 - 1`