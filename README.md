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

