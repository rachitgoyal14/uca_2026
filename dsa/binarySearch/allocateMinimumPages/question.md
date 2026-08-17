# Allocate Minimum Pages

## Problem Statement

You are given an array `arr[]` of integers, where `arr[i]` represents the number of pages in the `i`-th book.

You are also given an integer `k`, representing the number of students.

Your task is to allocate all the books among the students such that the following conditions are satisfied:

* Each student receives at least one book.
* Each student is assigned a **contiguous sequence of books**.
* No book is assigned to more than one student.
* All books must be allocated.

The objective is to **minimize the maximum number of pages assigned to any single student**.

In other words, among all possible valid allocations, find the allocation where the student receiving the most pages has the **smallest possible page count**.

If it is impossible to allocate at least one book to every student, return `-1`.

## Input

For each test case, you are given:

* An array `arr[]` containing the number of pages in each book.
* An integer `k` representing the number of students.

## Output

Return the minimum possible value of the maximum number of pages assigned to any student.

If it is not possible to allocate books to all students, return:

```text
-1
```

## Examples

### Example 1

```text
Input:
arr = [12, 34, 67, 90]
k = 2

Output:
113
```

### Explanation

There are several possible ways to divide the books between two students.

#### Allocation 1

```text
[12] and [34, 67, 90]

Student 1 = 12 pages
Student 2 = 191 pages

Maximum = 191
```

#### Allocation 2

```text
[12, 34] and [67, 90]

Student 1 = 46 pages
Student 2 = 157 pages

Maximum = 157
```

#### Allocation 3

```text
[12, 34, 67] and [90]

Student 1 = 113 pages
Student 2 = 90 pages

Maximum = 113
```

The third allocation gives the smallest possible maximum.

Therefore:

```text
Output = 113
```

---

### Example 2

```text
Input:
arr = [15, 17, 20]
k = 5

Output:
-1
```

### Explanation

There are only `3` books but `5` students.

Since every student must receive at least one book, it is impossible to distribute the books.

Therefore:

```text
Output = -1
```

## Constraints

```text
1 <= arr.size() <= 10^6
1 <= arr[i], k <= 10^4
```

The test cases are generated such that the answer fits within a 32-bit integer.

## Approach

This problem can be solved using **Binary Search on Answer**.

The answer represents the minimum possible value of the maximum pages assigned to a student.

### Search Space

The minimum possible answer is the number of pages in the book with the largest number of pages.

Why?

Because every book must be assigned to some student, so a student must receive the largest book.

Therefore:

```text
start = maximum element in arr
```

The maximum possible answer is obtained when one student receives all the books:

```text
end = sum of all pages
```

So the search space is:

```text
[maximum book pages, total pages]
```

### Feasibility Check

For a candidate value `maxPages`, check whether it is possible to distribute all books among at most `k` students such that no student receives more than `maxPages` pages.

Process the books from left to right.

Keep adding books to the current student while:

```text
current pages + current book <= maxPages
```

If adding the next book would exceed `maxPages`, assign that book to a new student.

If the number of required students becomes greater than `k`, then `maxPages` is not feasible.

### Binary Search

For each `mid`:

```text
mid = start + (end - start) / 2
```

If `mid` is a valid distribution:

```text
answer = mid
end = mid - 1
```

We try to find an even smaller maximum.

Otherwise:

```text
start = mid + 1
```

We need to allow more pages per student.

## Complexity

Let `n` be the number of books.

Each feasibility check takes:

```text
O(n)
```

The binary search performs:

```text
O(log(sum(arr)))
```

iterations.

Therefore:

```text
Time Complexity: O(n log(sum(arr)))
Space Complexity: O(1)
```

## Key Pattern

This problem is an example of:

```text
Binary Search on Answer
        +
Greedy Feasibility Check
```

The general pattern is:

```text
Can I achieve answer X?
        |
        v
    Feasibility
        |
   +----+----+
   |         |
 YES        NO
   |         |
Try lower   Try higher
```
