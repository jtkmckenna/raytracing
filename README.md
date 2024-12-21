

# Build instructions

mkdir build
cd build 
cmake ../
make -j8

# Choices that deviate from the tutorial

- Choose extensions .cxx and .hpp (as ooposed to .cc and .h in book)
- Avoiding 'using std::xyz'
- Prefer the spelling colour