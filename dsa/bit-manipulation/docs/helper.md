# Bit Manipulation Helper Guide

This is a concepts reference for solving Data Lab style bit manipulation
puzzles, where you are restricted to a small set of operators and a max
operation count, and normal control flow (if, while, for, switch) and
comparison operators are usually banned.

---

## 1. De Morgan's Laws

The two identities you will use constantly when `&` and `|` are not both
available:

```
~(a & b) = ~a | ~b
~(a | b) = ~a & ~b
```

Rearranged, these let you synthesize one operator from the other plus NOT:

```
a & b = ~(~a | ~b)
a | b = ~(~a & ~b)
```

This is exactly why `bitAnd` works with only `~` and `|`, and why `bitXor`
can be built from only `~` and `&`: XOR itself expands to
`(x & ~y) | (~x & y)`, and the `|` in that expression is rewritten using
De Morgan's law as `~(~a & ~b)`.

Think of De Morgan's law as a way to "translate" between AND-world and
OR-world whenever a problem locks you out of one of them.

---

## 2. Two's Complement Basics

- The most significant bit (bit 31 in a 32-bit int) is the sign bit.
- A negative number `-x` is represented as `~x + 1` (invert all bits, add 1).
  Equivalently, `~x = -x - 1`.
- Arithmetic right shift (`>>` on a signed int) copies the sign bit into the
  vacated high bits. This is called sign extension.
- Logical right shift fills vacated high bits with 0 regardless of sign.
  Plain C `>>` on a signed int is arithmetic, not logical, so if you need
  logical shift behavior you must mask off the sign-extended bits yourself.

Useful derived facts:

- `x + ~x = -1` (all bits set) for any x, since `~x = -x - 1`.
- `~x + 1 = -x`.
- For any nonzero x, at least one of `x` or `-x` has its sign bit set. This
  is the trick behind implementing `!x` (see bang below).

---

## 3. Building Comparisons Without `<` or `>`

Since relational operators are usually banned, comparisons are built from
sign bits and subtraction (`+` with negation).

- `x - y` is expressed as `x + (~y + 1)`.
- The sign of `x - y` tells you the relative order of x and y, but you must
  be careful about overflow: if x and y have different signs, `x - y` can
  overflow and give a misleading sign bit. The standard trick is to handle
  the "different signs" case separately from the "same sign" case.
- `sign(x)` type problems reduce to: check bit 31 for negative, use `!x` or
  `!!x` for the zero/nonzero distinction.

---

## 4. The "Double Bang" Trick: `!!x`

`!x` returns 1 if x is 0, else 0. So `!!x` returns 0 if x is 0, else 1.
This is the standard way to turn "is this operand zero or not" into a clean
0/1 value you can use to build masks.

Once you have a 0/1 value `b`, you can turn it into an all-0s or all-1s
mask with:

```
mask = ~b + 1
```

If `b = 1`, `mask = ~1 + 1 = -1` (all 1s, i.e. 0xFFFFFFFF).
If `b = 0`, `mask = ~0 + 1 = 0`.

This all-1s/all-0s mask is the core building block for `conditional`,
`isLessOrEqual`, and similar selection problems: you compute
`(mask & optionA) | (~mask & optionB)` to select between two values without
using an if statement.

---

## 5. Implementing `!` Without `!` (the `bang` trick)

You cannot use `!` inside `bang`, so you need another way to detect "is x
zero." The key fact: for any nonzero x, either x or -x (or both) has its
sign bit (bit 31) set. For x = 0, neither x nor -x has the sign bit set,
since -0 = 0.

So:

```
sign_bit_of(x | (-x))
```

is 1 for any nonzero x, and 0 for x = 0. Shift that combined value right by
31 (arithmetic shift) to spread the sign bit across the whole word (giving
-1 or 0), then adjust by adding 1 to flip -1/0 into 0/1.

---

## 6. Masks and Shifting

- `1 << k` produces a single 1 bit at position k.
- `(1 << k) - 1` produces k ones in the low bits (a common width mask), but
  remember `-1` here is really `~0`, so you can also write it as
  `~(~0 << k)` if subtraction feels indirect.
- To extract byte n (0 = LSB) from a word: shift right by `n * 8` bits (i.e.
  `n << 3`), then mask with `0xFF`.
- To build a logical (zero-filling) right shift from an arithmetic one: do
  the arithmetic shift first, then AND with a mask that has 0s in the top n
  bit positions and 1s elsewhere. That mask can be built by taking
  `1 << 31`, arithmetic-shifting it right by n to replicate the sign bit
  n+1 times, shifting left by 1 to drop one copy, and complementing.

---

## 7. Overflow Detection

Overflow in `x + y` (both signed) can only happen when x and y have the
same sign, and the result has a different sign from both. This gives the
general recipe for `addOK` and `satAdd` type problems: compare the sign
bits of x, y, and `x + y` using XOR to detect "same sign" or "different
sign" without using comparison operators.

- `(x ^ y)` has its sign bit set if x and y have different signs.
- `(x ^ sum)` has its sign bit set if x and the sum have different signs.
- Overflow occurred if x and y had the same sign AND the sum's sign
  differs from theirs.

---

## 8. Working with Floating Point Bit Patterns (IEEE 754 single precision)

Some Data Lab style problems (floatAbsVal, floatIsEqual) operate on the raw
bit pattern of a float, passed as an `unsigned int`, rather than as a float
value directly. Layout of a 32-bit float:

```
bit 31       : sign
bits 30-23   : exponent (8 bits)
bits 22-0    : mantissa / fraction (23 bits)
```

- To get the absolute value at the bit level, just clear the sign bit:
  `uf & 0x7FFFFFFF`.
- A value is NaN if the exponent bits are all 1 (0xFF after shifting into
  place) AND the mantissa is nonzero. You must check for NaN before
  returning a "fixed" result, since the problem usually asks you to return
  NaN unchanged.
- Comparing floats for equality at the bit level is not the same as
  comparing the raw bit patterns for equality, because +0 and -0 have
  different bit patterns but are numerically equal, and any NaN is never
  equal to anything including itself. Handle both as special cases before
  falling back to a direct bit or numeric comparison.

---

## 9. General Strategy Checklist

When you are stuck on one of these problems, work through this checklist:

1. What does the sign bit tell me here? Can I isolate it with `>> 31`?
2. Do I need a 0/1 flag, or an all-0s/all-1s mask? Convert between them with
   `!!x` and `~b + 1`.
3. Can I express the operation as "select between two precomputed values"
   using a mask, instead of branching?
4. Am I banned from `|` or `&`? Reach for De Morgan's law.
5. Am I banned from comparisons? Reduce the comparison to a sign-bit check
   on a subtraction, being careful about overflow when operands have
   different signs.
6. Does the problem involve extracting or replacing part of a word? Think
   in terms of shift-then-mask (extract) or mask-then-OR (insert).
7. Count your operators as you go. Casts and constant literals are usually
   free, but do not assume; recheck the specific problem's rules.

---

## 10. Common Building Blocks Reference

```
x & y              = ~(~x | ~y)                      (De Morgan)
x | y              = ~(~x & ~y)                      (De Morgan)
x ^ y              = (x & ~y) | (~x & y)
-x                 = ~x + 1
x - y              = x + (~y + 1)
is x zero (0/1)    = !x
is x nonzero (0/1) = !!x
0/1 to all-1s/0s   = ~b + 1        where b is 0 or 1
select(cond,a,b)   = (mask & a) | (~mask & b)         where mask is all-1s or all-0s
extract byte n     = (x >> (n * 8)) & 0xFF
sign bit of x      = (x >> 31) & 1
```

Keep this list nearby. The vast majority of Data Lab problems are some
combination of these seven or eight ideas layered together.