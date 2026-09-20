# Complexity Analysis and Performance Report

This lab compares two correct approaches to the same problem. The goal is not simply to get the right answer, but to observe how algorithmic design changes runtime.

The benchmark output is written in CSV format and can be analyzed in Python, Excel, or a plotting tool.

## Tie-breaking rule for the frequency problem

When two values have the same frequency, the implementation returns the smaller numeric value.

This rule is used in both the naive and efficient implementations so the results are comparable.

## Problem 1 — Duplicate detection

### Algorithm A: Brute force

- Description: compare every pair of values in the array.
- Time complexity: O(n^2)
- Space complexity: O(1)
- Why: for each of n values, the code may compare against up to n - 1 other values.

### Algorithm B: Hash set

- Description: insert each value into a hash set; if a value is already present, a duplicate exists.
- Time complexity: O(n) average case
- Space complexity: O(n)
- Why: each value is inserted and looked up in expected constant time.

### Experimental comparison

1. Brute force took 1.998 ms at n = 1,000, 205.945 ms at n = 10,000, and 20,471.684 ms at n = 100,000. Each 10x increase in n multiplied the time by about 100x, which matches O(n^2).
2. The hash set took 0.19 ms, 1.868 ms, and 18.138 ms. Each 10x increase in n multiplied the time by about 10x, which matches O(n).
3. At n = 100,000 the hash set was about 1,100x faster.
4. The hash set is faster but needs O(n) extra memory for the table, while brute force needs O(1).
5. The 1,000,000 size was not run (see the README).

```mermaid
xychart-beta
    title Problem 1: Input Size vs Execution Time
    x-axis [1000, 10000, 100000]
    y-axis "Time (ms)" 0 --> 21000
    line [1.998, 205.945, 20471.684] "Brute Force"
    line [0.19, 1.868, 18.138] "Hash Set"
```

## Problem 2 — Most frequent value

### Algorithm A: Naive counting

- Description: for each value, scan the whole array and count occurrences.
- Time complexity: O(n^2)
- Space complexity: O(1)
- Why: each value may require a full pass through the array.

### Algorithm B: Hash table counts

- Description: count frequencies in one pass and then inspect the counts.
- Time complexity: O(n) average case
- Space complexity: O(n)
- Why: hash table operations are expected to be constant time per value.

### Experimental comparison

1. Naive counting took 3.553 ms at n = 1,000, 352.528 ms at n = 10,000, and 34,563.265 ms at n = 100,000. Each 10x increase in n multiplied the time by about 100x, which matches O(n^2).
2. The hash counts took 0.069 ms, 0.644 ms, and 6.04 ms, about 10x per step, which matches O(n).
3. At n = 100,000 the hash version was about 5,700x faster.
4. The hash version needs O(n) extra memory for the frequency table.
5. The 1,000,000 size was not run (see the README).

```mermaid
xychart-beta
    title Problem 2: Input Size vs Execution Time
    x-axis [1000, 10000, 100000]
    y-axis "Time (ms)" 0 --> 35000
    line [3.553, 352.528, 34563.265] "Naive Count"
    line [0.069, 0.644, 6.04] "Hash Counts"
```


## Problem 3 — Common elements between two arrays

### Algorithm A: Naive scan

- Description: take each value from the first array and scan the second array to see whether it appears there.
- Time complexity: O(n × m)
- Space complexity: O(k), where k is the number of distinct values found in common
- Why: each of the n values in the first array may require checking all m values in the second.

### Algorithm B: Hash-based lookup

- Description: construct a hash set from the second array, then examine each value in the first array.
- Time complexity: O(n + m) average case
- Space complexity: O(m)
- Why: set construction and lookup are each expected constant time per element.

### Experimental comparison

1. The hash-based solution is faster for large inputs.
1. The naive scan took 0.173 ms at n = 1,000, 1.697 ms at n = 10,000, and 16.957 ms at n = 100,000. That is about 10x per step, which looks linear (O(n)), not the O(n x m) the theory predicts for the worst case.
2. The hash lookup took 0.129 ms, 1.179 ms, and 11.626 ms, also about 10x per step, which matches O(n + m). At n = 100,000 it was only about 1.5x faster than the naive scan.
3. The reason is the benchmark input. Both arrays contain only the values 0 to 18, so every scan of the second array finds its match within about 19 elements and stops, and the list of distinct common values never grows past 19 entries. The naive cost is roughly n x 19, which is O(n).
4. The quadratic behavior only appears when many values are missing from the second array or sit deep inside it, for example two mostly non-overlapping ranges, where each lookup has to scan the entire array.
5. The hash version needs O(m) extra memory for the set built from the second array.

```mermaid
xychart-beta
    title Problem 3: Input Size vs Execution Time
    x-axis [1000, 10000, 100000]
    y-axis "Time (ms)" 0 --> 18
    line [0.173, 1.697, 16.957] "Naive Scan"
    line [0.129, 1.179, 11.626] "Hash Lookup"
```



## Observations

For Problems 1 and 2, the measured times match the theory: the naive versions grew about 100x for every 10x increase in n, while the hash-based versions grew about 10x. At n = 100,000 the hash versions were roughly 1,100x and 5,700x faster. For Problem 3 the provided inputs only contain values 0-18, so the naive scan exits early and behaves like O(n), which hides the expected quadratic gap. The hash-based versions use extra memory (O(n) or O(m)) in exchange for the speedup.
