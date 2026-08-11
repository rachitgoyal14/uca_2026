# Implement Base-64 Encoding

## Problem Statement

Write a program or function that accepts an ASCII string input and returns its Base64 encoded equivalent without using built-in Base64 encoding libraries.

## Background Context

Base64 is a binary-to-text encoding scheme that represents binary data in an ASCII string format. It works by taking groups of 3 bytes (24 bits) and splitting them into 4 groups of 6 bits. Each 6-bit group corresponds to an index (0 to 63) in the Base64 Index Table:

| Index Range | Characters |
| --- | --- |
| 0-25 | A-Z |
| 26-51 | a-z |
| 52-61 | 0-9 |
| 62 | `+` |
| 63 | `/` |

## Encoding Algorithm Rules

- **Convert to Binary:** Convert each character of the input string into its 8-bit ASCII binary representation.
- **Group into 6 Bits:** Concatenate all bits into one long sequence and divide them into chunks of 6 bits.
- **Handle Padding (Crucial):**
  - If the last group has fewer than 6 bits, pad it on the right with zeros to make it 6 bits.
  - The total number of input bytes determines the padding equal signs (`=`) at the end of the output string:
    - If the input length is a multiple of 3, there is no padding.
    - If the input length leaves a remainder of 2 bytes, add 1 padding character (`=`).
    - If the input length leaves a remainder of 1 byte, add 2 padding characters (`==`).
- **Map to Character Set:** Convert each 6-bit chunk to its decimal value, then replace it with the corresponding character from the Base64 Index Table.

## Worked Examples

### Example 1: Standard Input (No Padding Needed)

- **Input:** `"Man"`
- **Length:** 3 characters (3 bytes = 24 bits)

| Step | Output / Processing |
| --- | --- |
| ASCII Values | M (77), a (97), n (110) |
| 8-bit Binary | `01001101 01100001 01101110` |
| Combined 24 bits | `010011010110000101101110` |
| Split into 6-bit groups | `010011 | 010110 | 000101 | 101110` |
| Decimal Values | 19 \| 22 \| 5 \| 46 |
| Base64 Lookups | T \| W \| F \| u |
| Final Output | `TWFu` |

### Example 2: Input Requiring 1 Padding Character

- **Input:** `"Ma"`
- **Length:** 2 characters (16 bits -> needs 2 bits of zero-padding to make 18 bits, plus `=` to complete a 4-character output block)

| Step | Output / Processing |
| --- | --- |
| ASCII Values | M (77), a (97) |
| 8-bit Binary | `01001101 01100001` |
| Group into 6-bit blocks | `010011 | 010110 | 0001` |
| Pad 6-bit block with 0s | `010011 | 010110 | 000100` |
| Decimal Values | 19 \| 22 \| 4 |
| Base64 Lookups | T \| W \| E |
| Add Padding | Append `=` to make the total length 4 |
| Final Output | `TWE=` |

## Test Cases

| Input String | Expected Base64 Output | Notes |
| --- | --- | --- |
| `"Cat"` | `"Q2F0"` | Exact multiple of 3 bytes |
| `"Hello World"` | `"SGVsbG8gV29ybGQ="` | 11 bytes -> 1 `=` padding character |
| `"A"` | `"QQ=="` | 1 byte -> 2 `=` padding characters |
| `""` | `""` | Empty input yields an empty string |

## Optional Bonus Challenge

- **Decode Function:** Add a second function that reverses the process and decodes a Base64 string back to the original text.

Please provide a GitHub link containing your solution.

**Enter your answer:**