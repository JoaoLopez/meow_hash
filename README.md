# Meow hash 0.5/calico
This is the official x64 implementation of the Meow hash, a fast hash taking 128 bytes of seed and producing 128 bits of output.  It is designed to be faster than currently available hashes in the "non-cryptographic" category.  See https://mollyrocket.com/meowhash for usage, implementation, and analysis details.

This version is v0.5 and is a **proposal for the final hash construction**.  Please provide as much testing, analysis, and commentary on the hash function as you can.  If we cannot substantially improve the hash function from here, this construction will be used for v1.0.

This version builds on Windows/MSVC, Windows/CLANG, and Linux/CLANG, with support for x64 AES-NI processors.

# Important Security Notice

Due to [recent discoveries](https://peter.website/meow-hash-cryptanalysis) by [Peter Schmidt-Nielsen](https://github.com/petersn), we have decided to reclassify Meow hash 0.5/calico from level 3 to level 1. This means that we recommend not to use this hash for message authentication codes, or for hash tables in scenarios where collision induced denial-of-service attacks are a concern.

We have seen no evidence that the hash is unfit for non-adversarial/non-cryptographic purposes, and continue to believe that it is amongst the best in this regard.

For level 3/MAC capabilities consider migrating to SipHash. Do not migrate to any hash not advertising MAC capabilities as these are almost certainly much weaker than Meow 0.5. If the performance of SipHash is not satisfying, continuing to use Meow 0.5 for hash tables is better than migrating to another fast hash. While Meow 0.5 also continue to provide some useful strength for message authentication codes, we have to stress that we strongly recommend migration in this case.

---

# 🔗 External Bindings and Wrappers

### SpeeduPy CTypes Wrapper

This repository is used by the **SpeeduPy** project for extreme performance caching in Python. A custom C++ wrapper is utilized with Python's `ctypes` to achieve stable, high-performance execution in environments where native performance is paramount.

* **Project Link:** [SpeeduPy Optimization Tool](https://github.com/dew-uff/speedupy)

* **How to Compile the Wrapper:**
    To use this hash in SpeeduPy, the custom wrapper (`meow_wrapper.cpp`) must be compiled into a shared object (`.so` or `.dll`). Run this command in the directory containing your wrapper and the Meow Hash source files:

    ```bash
    g++ -shared -o libmeow.so meow_wrapper.cpp -O3 -maes -msse4.1 -fPIC
    ```
    *Note: This command ensures correct compilation with SIMD instructions (AES-NI) and generates the shared library required by Python's `ctypes`.*

    **Implementation Detail:** The resulting shared library (`libmeow.so`) must be placed in the same directory as the `MeowHash.py` file within the SpeeduPy project structure (`/speedupy/execute_exp/services/hashes/`).

---

# Unofficial Ports
We do not maintain or vet these ports in any way.  Their correctness and performance may differ from the official Meow Hash.  **They may also have different, more restrictive licenses** than Meow Hash itself.  Use at your own risk.

* [.NET core port](https://github.com/tvandijck/meow_hash.NET) (by [Tom van Dijck](https://github.com/tvandijck))
* [Rust port](https://github.com/bodil/meowhash-rs) (by [Bodil Stokke](https://github.com/bodil))

If you have ported Meow Hash to another language, and would like to link to your repository here, please open