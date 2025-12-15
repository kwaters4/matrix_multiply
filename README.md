## Configure
```
CC=clang cmake ../ --fresh -DENABLE_TESTING=1
```

## Build
```
make
```

## Test
```
ctest .
```

## Run
```
driver min_size_matrix max_size_matrix #_of_trials
```

For example:
```
driver 256 4096 5
```
