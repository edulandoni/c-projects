
# hideincleartext

Simple C program that generates a **transformer** (key) by XOR-ing two files of the same size.

- **Create transformer:** `transformer = clear XOR secret`
- **Recover secret:** `secret = clear XOR transformer`

> The XOR output is **binary** (not text). If you open it in nano/vim it will look like “garbage”. That’s expected.

---

## Requirements

- GCC (or clang)
- make

---

## Build

From the project root:

    make

---

## Usage

The program expects **2 input files** (same number of bytes) and writes the result to **stdout**, so you can redirect it to a file.

### 1) Create sample files

    cleartext "Just a normal note about groceries, weather, and a boring Monday. Nothing to see here.\n" > testdata/clear.txt
    secrettext "Meet at the old bridge at 21:30. Bring the SD card and do not text anyone about this.\n" > testdata/secret.txt

### 2) Create the transformer (key)

    ./build/app samples/cleartext.txt samples/secrettext.txt > samples/transformer.bin

### 3) Recover the secret

    ./build/app samples/cleartext.txt samples/transformer.bin > samples/secret_recovered.txt

### 4) Verify it matches

    diff -q samples/secrettext.txt samples/secret_recovered.txt

If `diff` prints nothing, the files are identical.

---

## View the transformer in hex

Since it is binary, view it as hex:

    hexdump -C samples/transformer.bin | head

---

## Notes

- Both input files must have **exactly the same size in bytes**.
- This works because:
  - `x ^ x = 0`
  - `x ^ 0 = x`
  - therefore `(clear ^ secret) ^ clear = secret`
