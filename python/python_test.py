import numpy as np
import time

# Matrix size (adjust for your machine)
N = 2048

# Initialize matrices
A = np.random.randint(
    low=-5,
    high=5,
    size=(N, N),
    dtype=np.int32)

B = np.random.randint(
    low=-5,
    high=5,
    size=(N, N),
    dtype=np.int32)

#A = np.random.rand(N, N)
#B = np.random.rand(N, N)

# Warm-up
C = A @ B

# Timed run
start = time.perf_counter()
C = A @ B
end = time.perf_counter()

print(f"Time: {end - start:.6f} seconds")
