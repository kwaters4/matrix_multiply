# Matrix Multiplication Exploration

## Typst

How to build the presentation.

```
cd typslides
typst compile main.typ
```

This should create `main.pdf`.

# Testing the Code in the Repository

## Configure
```
CC=clang cmake ../ --fresh -DENABLE_TESTING=1
```

## Build

`src/main.c` this needs to change matrix multiplication methods via commenting code in and out. **WORK IN PROGRESS**

```
make
```

## Test
```
ctest .
```

## Run
```
./driver min_size_matrix max_size_matrix #_of_trials
```

For example:
```
./driver 256 4096 5
```
