# dd-cpp

A simple command-line utility implemented in modern C++ for block-wise file copying — inspired by the Unix/Linux `dd` tool.

## Current Features

* **Block-wise Copying:** Reads binary data from an input file and writes it block by block to an output file.

* **Configurable Block Size (`bs=`):** Sets the buffer/block size in bytes (default: `512` bytes).

* **Configurable Block Count (`count=`):** Sets the maximum number of blocks to copy (default: `1` block).

* **Partial Block Handling:** Reliably detects end-of-file (`EOF`) as well as partial blocks and terminates the copy loop cleanly.

* **Status Output (`dd`-style):** Prints the number of full and partial blocks read/written (`records in` / `records out`), total bytes copied, and the block size used upon completion.

* **Error Handling:** Validates stream states when opening and writing files, reporting errors via exceptions.

## Project Structure

* `main.cpp` – Entry point, file stream handling, copy loop, and status output

* `argv_parser.h` / `argv_parser.cpp` – Encapsulation and parsing of command-line arguments (`if=`, `of=`, `bs=`, `count=`)

## Requirements

* A C++17-compatible compiler (for `std::optional`), e.g., `g++` or `clang++`

## Building

Compile directly using `g++` or `clang++`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp argv_parser.cpp -o dd-cpp
```

## Usage

```bash
./dd-cpp if=<input_file> of=<output_file> [bs=<bytes>] [count=<number>]
```

### Parameters

| Parameter | Description | Default |
| :--- | :--- | :--- |
| `if=<path>` | Path to the input file | *required* |
| `of=<path>` | Path to the output file | *required* |
| `bs=<number>` | Block size in bytes (positive integer $> 0$) | `512` |
| `count=<number>` | Number of blocks to copy (positive integer $> 0$) | `1` |

### Example

Copy 10 blocks of 4096 bytes each from `input.bin` to `output.bin`:

```bash
./dd-cpp if=input.bin of=output.bin bs=4096 count=10
```

Example output:

```text
10+0 records in
10+0 records out
40960 bytes copied
Block size: 4096
```

## Planned Enhancements / Roadmap

* Copy until end-of-file (`EOF`) when `count=` is omitted

* Support `stdin` / `stdout` as default I/O streams when `if=` or `of=` are omitted

* Support size suffixes for `bs=` (e.g., `K`, `M`, `G`)

* Additional `dd` options such as `skip=` and `seek=`
