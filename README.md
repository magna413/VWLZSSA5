# 📷 Custom LZSS Library for Volkswagen 2Q0 MFK3.0 ADAS Cameras

This is a Python implementation of a custom **LZSS variant** designed for **Volkswagen ADAS (2Q0 MFK3.0) cameras**.

### **🔹 Key Features**
- ✅ **6-bit length encoding**
- ✅ **10-bit displacement**
- ✅ **Compatible with Volkswagen's LZSS compression format**

---

## **📥 Installation**
To install directly from GitHub, run:
```sh
pip install git+https://github.com/magna413/VWLZSSA5.git
```

## Usage

```sh
from vwlzssa5 import VWLZSSA5

# Initialize new class instance
lzss = VWLZSSA5()

# 🔹 Decompression Example
random_lzss_compressed_data = b'RandomData'
decompressed_data = lzss.decompress(random_lzss_compressed_data)

# 🔹 Compression Example
compressed_data = lzss.compress(decompressed_data)
```
⚠️ WARNING: Use Compression with Caution!


# LZSS Compression and Decompression (C Implementation)

## Overview
This repository provides a C implementation of the LZSS compression and decompression algorithm, allowing efficient encoding and decoding of binary data using a sliding window mechanism.

## Features
- Compresses and decompresses binary files using the Custom VW LZSS algorithm
- Uses a 1023-byte sliding window for efficient encoding
- Outputs data in a format compatible with LZSS decompression

## Compilation
To compile the program, use the following command:
```sh
gcc -o lzss lzss.c
```

## Usage
### Compress a file
```sh
./lzss compress input.bin output.lzss
```
### Decompress a file
```sh
./lzss decompress output.lzss decompressed.bin
```

## Example
Compress a binary file:
```sh
./lzss compress sample.bin sample_compressed.lzss
```

## File Structure
- `lzss.c` - The main implementation of custom LZSS compression and decompression
- `README.md` - Documentation on how to use the tool




