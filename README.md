*This project has been created as part of the 42 curriculum by dd-alo.*

# get_next_line

## Description

**get_next_line** is a C function that reads and returns one line at a time from a file descriptor. It is designed to work with regular files and standard input, without requiring the caller to know the length of the next line.

The project focuses on the `read()` system call, dynamic memory management, and **static variables**. Repeated calls continue reading from the point where the previous call stopped.

**Prototype:** `char *get_next_line(int fd);`

- Returns a heap-allocated string containing the next line, including `\n` when present.
- Returns the final line even if the file does not end with `\n`.
- Returns `NULL` at the end of the file or when an error occurs.
- The caller is responsible for calling `free()` on each returned line.

## Instructions

### Files

The implementation consists of three files, placed at the root of the repository:

| File | Purpose |
| --- | --- |
| `get_next_line.c` | Main function, buffered reading, and allocation management. |
| `get_next_line_utils.c` | String helpers, line extraction, and preservation of leftover data. |
| `get_next_line.h` | Function prototypes, storage structure, and `BUFFER_SIZE` definition. |

### Compilation

There is no executable or `main()` function in the submitted implementation. Compile the three project files **together with your own test program** (for example, `main.c`):

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line.c get_next_line_utils.c main.c -o gnl_test
./gnl_test
```

Replace `main.c` with the filename of your test program. The source also compiles without `-D BUFFER_SIZE=...`; in that case, the default value is **42**.

Try different buffer sizes, especially `1`, `42`, and `9999`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
  get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

To use the function in another program, include `get_next_line.h`, pass it an open file descriptor, call it repeatedly until it returns `NULL`, and free every returned line.

## Algorithm and Technical Choices

The main design choice is to **keep unread characters between calls** using one static pointer, `saved`. A local `t_storage` structure tracks the current string length and allocated capacity during each call.

1. **Reuse existing data.** At the beginning of a call, check whether `saved` already contains a newline. If so, no additional `read()` is necessary.
2. **Read incrementally.** Otherwise, allocate a temporary buffer of `BUFFER_SIZE` bytes and read chunks until a newline is found, end-of-file is reached, or an error occurs.
3. **Grow the saved string.** Append only the bytes actually returned by `read()`. When more space is needed, `ft_reserve()` allocates a larger block (normally twice the required size), copies the existing characters, and frees the old block. This avoids repeatedly rebuilding the entire accumulated string for every chunk.
4. **Extract one line.** `ft_take_line()` copies characters up to and including the first `\n`, or up to the string terminator when no newline exists.
5. **Preserve leftovers.** `ft_update_saved()` keeps characters located after the returned line for the next call. If none remain, it frees the saved string.
6. **Clean up.** At EOF with no characters remaining, return `NULL`. On a read or allocation error, release the allocated state and return `NULL`.

**Why this algorithm?** A line may span many `read()` calls, and one read can contain parts of multiple lines. The static pointer preserves data that was read but not returned yet; incremental reading stops once the next newline has been found. The capacity-management strategy reduces unnecessary allocations while accumulating long lines.

**Scope:** A single static saved string is used, so the mandatory implementation is intended for sequential reading, not alternating between several file descriptors.

## Testing

Useful cases to check include an empty file, a file containing only `\n`, multiple lines, the last line without `\n`, very long lines, invalid file descriptors, and different `BUFFER_SIZE` values. Check for memory leaks and verify that each call returns exactly one line.

## Resources

- **42 get_next_line subject (v14.3)** — official requirements for the mandatory part, bonus, and README.
- [Linux `read(2)` manual](https://man7.org/linux/man-pages/man2/read.2.html) — file descriptors, byte counts, EOF, and errors.
- [Linux `malloc(3)` manual](https://man7.org/linux/man-pages/man3/malloc.3.html) — dynamic allocation and memory release.
- [C storage duration reference](https://en.cppreference.com/w/c/language/storage_duration.html) — lifetime of static local variables.

**AI usage:** ChatGPT was used as a learning and review tool for `get_next_line.c` (reading loop, static storage, and buffer allocation), `get_next_line_utils.c` (line extraction and leftover data), debugging and interpreting test results, and drafting this README. The implementation was examined and revised throughout the project.
