

# Build instructions

mkdir build
cd build 
cmake ../
make -j8

# Usage
```sh
./inOneWeekend
```
For extra options, run:

```sh
./inOneWeekend -h
Usage: ./inOneWeekend [-h]
Options:
  -h, --help		Show this help message
  -w, --width		Set image width
  -s, --samples		Set samples per pixel
  -d, --depth		Set max depth
```

# Choices that deviate from the tutorial

- Choose extensions .cxx and .hpp (as ooposed to .cc and .h in book)
- Avoiding 'using std::xyz'
- Prefer the spelling colour
- Bump minimum C++ standard to C++14 (for better constexpr support)