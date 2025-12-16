# Matrix Multiplication Exploration

Small library and executable that explores matrix multiplication.
Image and pdfs were added to repository for completness as full plot automation does not yet exist.

- `python/` - some auxillary python programs
- `data/` - raw benchmarking data used by python plotting in `typslides/images`

## Typst (Presentation)

How to build the presentation.

- requries an install of the [typst crate](https://typst.app/open-source/)
    - requires the Rust compiler

```
cd typslides
typst compile main.typ
```

This will create `main.pdf`.

# Testing the Code in the Repository

## Configure
```
CC=clang cmake ../ --fresh \
  -DCMAKE_INSTALL_PREFIX=/home/cosmicbox/Documents/Talk/code/Matrix/INSTALL \
  -DENABLE_TESTING=1 \
  -DBLOCK_SIZE="64"
```

- 'ENABLE_TESTING'(0) - Enables building of the ctests.
- 'BLOCK_SIZE'(32) - Toggles how big the block size is for tiled matrix multiplication.

## Build

`src/main.c` this needs to change matrix multiplication methods via commenting code in and out. **WORK IN PROGRESS**

```
make
```

## Test
```
ctest .
```

## INSTALL

```
make install
```

## Run
```
./driver min_size_matrix max_size_matrix #_of_trials
```

For example:
```
./driver 256 4096 5
```
