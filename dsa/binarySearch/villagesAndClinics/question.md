# Villages and Clinics

## Problem Statement

You are given `n` villages and must open exactly `k` clinics across them.

The population of each village is given, and initially, no village has a clinic.

You must distribute the `k` clinics among the villages subject to the following conditions:

* Every village must have at least one clinic.
* Residents can only visit clinics within their own village.
* Clinics within the same village share that village's population equally.
* You must minimize the **maximum number of patients assigned to any single clinic**.

Given the number of villages, the population of each village, and the number of clinics available, determine the minimum possible maximum patient load.

### Input

The input consists of multiple test cases.

For each test case:

* The first line contains an integer `n`, the number of villages.
* The second line contains an integer `k`, the total number of clinics.
* The third line contains `n` integers representing the population of each village.

### Constraints

* `1 <= n <= k`
* Each village has a positive population.
* `k` is at least `n`.
* All populations are non-negative integers.

### Output

For each test case, print the minimum possible maximum patient load.

The answer may be fractional, so print the result with **2 decimal places**.

### Example

#### Input

```text
1
3
5
200 20 50
```

#### Output

```text
66.67
```

### Explanation

There are 3 villages and 5 clinics.

An optimal allocation is:

```text
Village 1: 3 clinics
Village 2: 1 clinic
Village 3: 1 clinic
```

The resulting loads are:

```text
200 / 3 = 66.67
20 / 1  = 20.00
50 / 1  = 50.00
```

Therefore, the maximum load is:

```text
66.67
```

and this is the minimum possible maximum load.

## Approach

This problem can be solved using **Binary Search on Answer**.

For a candidate maximum load `X`, determine whether it is possible to serve all villages using at most `k` clinics while ensuring that no clinic has more than `X` patients.

For a village with population `P`, the number of clinics required is:

```text
ceil(P / X)
```

Therefore:

```text
total clinics required =
    sum(ceil(population[i] / X))
```

If:

```text
total clinics required <= k
```

then `X` is a valid maximum load.

Otherwise, `X` is too small.

### Binary Search

The search space is:

```text
start = 0
end = maximum population of any village
```

Since the answer can be fractional, perform a fixed number of binary-search iterations rather than using `start <= end`.

For each iteration:

```text
mid = (start + end) / 2
```

* If `mid` is feasible, store it as the current answer and search for a smaller value.
* Otherwise, search for a larger value.

### Complexity

Let:

* `n` = number of villages
* `I` = number of binary-search iterations

Each feasibility check takes `O(n)`.

Therefore:

```text
Time Complexity: O(n * I)
Space Complexity: O(n)
```

With a fixed number of iterations such as `100`, this is effectively:

```text
O(n)
```

for practical purposes.
