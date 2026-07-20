# Understanding `strtok()` 

## The Code

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "C,C++,Java,Python,Rust";
    char *token;

    token = strtok(str, ",");

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
```

**Output:**
```
C
C++
Java
Python
Rust
```

---

## What is `strtok()`?

`strtok()` is a C standard library function that splits a string into smaller pieces called **tokens**, based on delimiter characters you provide. It lives in `<string.h>`.

Function signature:

```c
char *strtok(char *str, const char *delim);
```

- `str` - the string to tokenize. You only pass the real string on the **first** call.
- `delim` - a string of delimiter characters. Every individual character in `delim` is treated as a valid cut point (not the whole string as a single multi-character delimiter).
- **Return value** - a pointer to the next token, or `NULL` once there are no tokens left.

`strtok()` keeps track of where it left off internally (using a static pointer behind the scenes), so repeated calls know how to continue from the previous position.

---

## Line-by-Line Breakdown

### 1. Header files

```c
#include <stdio.h>
```
Gives access to `printf()`, used to print each token.

```c
#include <string.h>
```
Gives access to `strtok()` and other string functions. Without this include, the compiler doesn't know `strtok()` exists.

---

### 2. Declaring the string

```c
char str[] = "C,C++,Java,Python,Rust";
```

This creates a **mutable character array** - your own private, writable copy of the string, stored on the stack.

**Why this matters:** `strtok()` doesn't just *read* the string - it *modifies* it. Every time it finds a delimiter, it overwrites that character with a `'\0'` (null terminator) to "cut" the string into a standalone piece. This means the array you hand it must be writable.

#### `char str[] = "..."` vs `char *str = "..."`

| Declaration | Where it lives | Writable? | Safe with `strtok()`? |
|---|---|---|---|
| `char str[] = "..."` | Stack - your own copy | Yes | ✅ Yes |
| `char *str = "..."` | Read-only data segment | No | ❌ No - undefined behavior |

- **`char str[] = "..."`** tells the compiler: "allocate a new array on the stack and copy this string literal into it." You now own that memory outright, so modifying it (which `strtok()` needs to do) is perfectly safe.

- **`char *str = "..."`** just creates a pointer that points *directly at the string literal itself*. String literals are stored by the compiler in a read-only section of memory (shared/protected). You never got a personal copy - you're pointing at the original, protected data.

If `strtok()` tries to write a `'\0'` into read-only memory, the result is **undefined behavior**. In practice this usually crashes the program (segmentation fault), but technically anything could happen - that unpredictability is exactly what "undefined behavior" means in C. It might even appear to work on some systems, which makes the bug more dangerous, not less - it can pass testing and fail later.

**Rule of thumb:** if a string needs to be modified in any way (by `strtok()`, or by anything else), always declare it as an array (`char str[] = "..."`), never as a pointer to a literal.

```c
char *token;
```

Declares a pointer that will hold the address of each token as `strtok()` finds them. Note this doesn't allocate new memory for the token text - `token` just points *into* the original `str` array, at wherever the current token begins.

---

### 3. The first call to `strtok()`

```c
token = strtok(str, ",");
```

This is special - it's the **only** call where you pass the actual string. Here's what happens internally:

1. `strtok()` scans `str` starting from the beginning, looking for the first occurrence of any character in the delimiter set (here, just `,`).
2. When it finds that `,`, it overwrites it with `'\0'`, effectively cutting the string into two pieces right there.
3. It returns a pointer to the start of the first token - `"C"`.
4. Internally, it remembers (via a static pointer) where it stopped, so the *next* call knows where to resume.

After this call:
- `token` points to `"C"`
- The underlying memory now conceptually looks like: `"C\0C++,Java,Python,Rust"`

---

### 4. The loop

```c
while (token != NULL) {
```

`strtok()` returns `NULL` once there's nothing left to tokenize. So this loop runs exactly once per token found, and stops naturally when tokens run out.

```c
    printf("%s\n", token);
```

Prints the current token followed by a newline. Since `token` is just a `char *` pointing to a null-terminated segment of the original string, `%s` prints exactly up to the `'\0'` that `strtok()` inserted.

```c
    token = strtok(NULL, ",");
```

This is the key trick of how `strtok()` works across multiple calls. Passing `NULL` (instead of the string) tells `strtok()`:

> "Don't start over from the beginning - continue from your internally saved position."

Each subsequent call:
1. Starts right after the previous `'\0'` it inserted.
2. Finds the next delimiter (or reaches the end of the string).
3. Replaces it with `'\0'` if found.
4. Returns a pointer to the token that starts right after the previous cut.
5. Returns `NULL` if there's nothing left - which ends the loop.

```c
}
```

Closes the `while` loop.

---

### 5. Program exit

```c
return 0;
```

Signals that the program completed successfully (standard convention in C - `0` means "no error").

---

## Important Caveats About `strtok()`

1. **It modifies the original string.** If you need the original, unmodified string later in your program, make a copy before calling `strtok()` on it.

2. **It's not thread-safe / not reentrant.** Because `strtok()` relies on a single internal static pointer to remember its position, you can't tokenize two different strings at the same time (e.g., in nested loops, or across threads) - the second call would corrupt the first one's progress.

   The fix is `strtok_r()` (the "reentrant" version), which takes an extra `char **saveptr` argument so *you* manage the position tracking instead of relying on a hidden static variable:

   ```c
   char str[] = "C,C++,Java,Python,Rust";
   char *token;
   char *saveptr;

   token = strtok_r(str, ",", &saveptr);
   while (token != NULL) {
       printf("%s\n", token);
       token = strtok_r(NULL, ",", &saveptr);
   }
   ```

3. **Consecutive delimiters are skipped.** For example, tokenizing `"C,,Java"` with delimiter `,` gives you `"C"` and `"Java"` - not an empty token in between. If you need empty fields preserved (common when parsing CSV data with blank cells), `strtok()` is the wrong tool.

4. **Never pass a string literal directly.** As covered above - always use a `char[]` array, not a `char *` pointing to a literal.