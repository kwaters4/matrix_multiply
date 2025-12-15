#import "@preview/typslides:1.3.0": *
#import "@preview/fontawesome:0.6.0"

#show footnote.entry: set text(size: 10pt)
#show figure.caption: emph
#set figure(numbering: none)

// Project configuration
#show: typslides.with(
  ratio: "16-9",
  theme: "bluey",
  font-size: 22pt,
  link-style: "color",
  show-progress: true,
)

// The front slide is the first slide of your presentation
#front-slide(
  title: "Matrix Multiplication and Performance",
  subtitle: [A Short Journey into High Performance Computing (HPC)],
  authors: "Kevin Waters",
)

// The front slide is the first slide of your presentation
#front-slide(
  title: "Matrix Multiplication and Performance",
  subtitle: [The Time I Accidentally Bested  NumPy],
  authors: "Kevin Waters",
)
// Background
#slide(title: "Code and Talk")[
  - The code and talk for this presentation can be found #link("https://github.com/kwaters4/matrix_multiply")[here].
  #figure(
  image("images/git_repo.png", width: 80%),
  )
]

// Custom outline
#table-of-contents()

#title-slide[
 What is High Performance Computing (HPC)?
]

// Background
#slide(title: "What is HPC?")[
  #cols(columns: (3fr, 2fr), gutter: 2em)[
    #[
      - AI (Training/Inference)?

      - Large-scale distributed memory computations?

      - Distributed and scalable web services?

      - Performance-aware programming: #footnote[Term taken from Casey Muratori https://www.computerenhance.com/p/welcome-to-the-performance-aware]
        - x86 aware?
        - Platform aware (CPU vs. GPU)?
        - Instruction set architecture (ISA) aware?
        - Cache-size aware?
    ]
  ][
      #figure(
      image("images/cluster.jpg", width: 90%),
      caption: [Raspberry Pi cluster #footnote[https://www.raspberrypi.com/tutorials/cluster-raspberry-pi-tutorial/]]
      )
  ]
]

// Title slides create new sections
#title-slide[
  Matrix Multiplication
]

// Background
#slide(title: "Why do we Care?")[
  - A few examples of applications (Where is linear algebra used today?):
    - *Finite element analysis* - Aerospace, automotive, material's properties...

    - *Electronic structure theory* - Density Functional Theory, Hartree-Fock++...

    - *Machine learning/data science* - Data analysis, pattern recognition, neural nets...

    - *Genetics* - genotype distribution

    - *Solving (partial) differential equations*... and much more
]

// Matrix Multiplication
// Slide with title
#slide(title: "Matrix Multiplication (Basics)")[

  #show math.equation: set text(24pt)
  $ bold(A)bold(B) = bold(C) $

  #show math.equation: set text(18pt)
  #set align(center)
  $ mat(
  a_00, a_01, a_02,  dots.h, a_(0 n);
  a_10, a_11, a_12,  dots.h, a_(1 n);
  a_20, a_21, a_22,  dots.h, a_(2 n);
  dots.v, dots.v, dots.v, dots.down;
  a_(n 0), a_(n 1), a_(n 3),  dots.h, a_(n n),;
  ) *
  mat(
  b_00, b_01, b_02,  dots.h, b_(0 n);
  b_10, b_11, b_12,  dots.h, b_(1 n);
  b_20, b_21, b_22,  dots.h, b_(2 n);
  dots.v, dots.v, dots.v, dots.down;
  b_(n 0), b_(n 1), b_(n 3),  dots.h, b_(n n),;
  ) =
  mat(
  c_00, c_01, c_02,  dots.h, c_(0 n);
  c_10, c_11, c_12,  dots.h, c_(1 n);
  c_20, c_21, c_22,  dots.h, c_(2 n);
  dots.v, dots.v, dots.v, dots.down;
  c_(n 0), c_(n 1), c_(n 3),  dots.h, c_(n n),;
  ) $

  Where:

  #show math.equation: set text(24pt)
  $c_(i j) = sum a_(i j) b_(k j) $
]

// Computational Complexity
#slide(title: "Computational Complexity")[
  #figure(
  image("images/complexity.pdf", width: 60%),
  caption: [ Progress of Computation Complexity of Matrix Multiply #footnote[Sourced from https://en.wikipedia.org/wiki/Computational_complexity_of_matrix_multiplication]],
)
]

// Computational Complexity
#slide(title: "Naive Computational Complexity")[
  - Naive Matrix multiplication's computational complexity is $theta(n^3)$
    - Others scale better, but there are trade-offs

  - What does that mean?
    - $"2x2"$ results in 8 multiplication steps and 4 addition steps:
    #show math.equation: set text(30pt)
    $ mat(a_00, a_01; a_10, a_11;) mat(b_00, b_01; b_10, b_11;) =
      mat(a_00 b_00 + a_01 b_10, a_00 b_01 + a_01 b_11; a_10 b_00 + a_11 b_10, a_10 b_01 + a_11 b_11;)$

    - For the general case the number of operations is given by the following:
    #set align(center)
    $2n^3  + n^2 $
    #set align(left)
    #show math.equation: set text(18pt)
    - $2n^3$ multiply operations.
    - $n^2$ addition operations.
]


// Title slides create new sections
#title-slide[
  Matrix Multiplication in Python (Easy Part)
]
// Python
#slide(title: "What can Python do?")[
  #framed(title: "Python Benchmark")[
  #set text(size: 16pt)
  ```bash
  ❯ python python_plain.py
  1024x1024 matrix multiply...
  Int        Time: 80.576309 seconds
  Float      Time: 97.653700 seconds
  ```
  ]
  - There are many things working against python, just-in-time-compilation (JIT), arbitrary size integers...
]

// Python
#slide(title: "What can Python (NumPy) do?")[
  - NumPy is a highly-tuned library where typically expensive functions are implemented in compiled languages such as C/C++ or FORTRAN. (BLAS & LAPACK)
  #framed(title: "Python (NumPy) Benchmark")[
  #set text(size: 14pt)
  ```bash
  ❯ python python_numpy.py
  1024x1024 matrix multiply...
  Int32      Time: 1.895825 seconds
  Int64      Time: 1.884659 seconds
  Float      Time: 0.005361 seconds
  Double     Time: 0.010751 seconds
  ```
  ]
  - These results are interesting...
]

// Title slides create new sections
#title-slide[
  Matrix Multiplication in C (Hard Part)
]

#slide(title: "Some Quick Assumptions")[

  - All matrices are square.
  - All matrices sizes are a power of 2.
  - Matrices are populated with ints (32-bits) randomly distributed [-5,5].
  - For benchmarking, one warm-up was followed by five trials (times are per trials).
  - To count cycles, the following x86 instruction was used "``rdtsc()``" (Time Stamp Counter).
  - Time stamps were called using ``clock_gettime()``.
	- Compile flags for all timed runs:
		- _-Wall -O3 -march=native -funroll-loops_
	- Work per cycle was calculated using the following:

  #align(center)[
  $ "Work Required"/("Clock Cycle") = (3n^3 + n^2)/("# cycles_elapsed")$
  ]
]

#slide(title: "Naive Matrix Multiply")[
  #framed(title: "Simple Matrix Multiply")[
  #set text(size: 16pt)
    ```c
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i * n + j] += matrix1[i * n + k] * matrix2[k * n + j];
            }
        }
    }
    ```
  ]
  - Readable, simple, and slow.
]

#slide(title: "Naive Matrix Multiply")[
 #figure(
  image("images/naive_c.pdf", width: 55%),
  )
]

#slide(title: "Problem Size Growth (Memory Footprint)")[

  #let mytable(data) = table(
  columns: 4,
  stroke: 1pt + black,
  [*n*],[*Elements ($n^2$)*], [*Memory/Matrix (KiB)*], [*Total Memory (KiB)*],
  ..data.map(((n)) => ([#n], [#(n*n)], [#(4*n*n/1024)], [#(3*4*n*n/1024)])).flatten()
)
 - Assuming 32-bit integers or 32-bit floats
 #figure[
   #mytable((
     (64),
     (128),
     (256),
     (512),
     (1024),
     (2048),
     (4096),
   ))
 ]
 - Total memory is 3x the memory per matrix.
]
#slide(title: "Memory Footprint Revisted")[

 #figure(
  image("images/memory_scale.pdf", width: 80%),
  caption: [Memory requirement for three $n x n$ matrices.]
  )
]

#slide(title: "Skylake Topology")[

 #figure(
  image("images/cpu.pdf", width: 85%),
  caption: [8-core client Skylake topology (``\$ lstopo``)]
  )
]

#slide(title: "Skylake Topology (Highlights)")[

  - One NUMA domain
  - One 16 MiB shared L3 cache
  - Individual 256 KiB L2 cache
  - Individual 32 KiB instruction and data caches
  - Two logical cores per physical core (8 physical, 16 logical)

]

// Table
#slide(title: "Latency Comparison Numbers (Everything is a Cache) (~2012)")[

  #show table.cell: set text(size: 18pt)
  #align(center)[
    #figure[
      #table(
      columns: 5,
      [L1 cache reference                ],[           0.5 ns],[],[],[],
      [Branch mispredict                 ],[           5   ns],[],[],[],
      [L2 cache reference                ],[           7   ns],[],[],[14x L1 cache],
      [Mutex lock/unlock                 ],[          25   ns],[],[],[],
      [Main memory reference             ],[         100   ns],[],[],[20x L2 cache, 200x L1 cache],
      [Send 1K bytes over 1 Gbps network ],[      10,000   ns],[    10 us],[],[],
      [Read 4K randomly from SSD         ],[     150,000   ns],[   150 us],[],[~1GB/sec SSD],
      [Read 1 MB sequentially from memory],[     250,000   ns],[   250 us],[],[],
      [Read 1 MB sequentially from SSD   ],[   1,000,000   ns],[ 1,000 us],[ 1 ms],[ ~1GB/sec SSD, 4X memory],
      [Disk seek                         ],[  10,000,000   ns],[10,000 us],[ 10 ms],[  10x datacenter roundtrip],
      [Read 1 MB sequentially from disk  ],[  20,000,000   ns],[20,000 us],[ 20 ms],[  80x memory, 20X SSD],
    )
    ]
  Latencies to generate intuition for the cost of an operation.#footnote[Originally by Peter Norvig: http://norvig.com/21-days.html#answers]
  ]
]

#slide(title: "Memory Footprint Revisted")[

 #figure(
  image("images/memory_scale.pdf", width: 80%),
  caption: [Memory requirement for three $n x n$ matrices.]
  )
]

#slide(title: "Whole Program Performance Metrics")[
  #framed(title: "Intermediate Sum")[
  #set text(size: 14pt)
   ```bash
  ❯ perf stat -e cycles,instructions,cache-references,cache-misses ./build/driver 2048 2048 5
  n, trials, req. memory (KiB), time/trial (s), work/cycle, Read Bandwidth (GiB/s)
  s2048, 5, 49152, 21.019992, 0.215482, 0.000297

   Performance counter stats for './build/driver 2048 2048 5':

     603,229,008,482      cycles:u
     156,197,169,903      instructions:u                   #    0.26  insn per cycle
     100,483,589,712      cache-references:u
       7,718,024,466      cache-misses:u                   #    7.68% of all cache refs
  ```
  ]
  - More targeted data can be found with PAPI (Performance Application Programming Interface).
]


#slide(title: "Intermediate Sum Matrix Multiply")[
  #framed(title: "Intermediate Sum")[
  #set text(size: 16pt)
    ```c
		for (int i = 0; i < n; i++) {
		  for (int j = 0; j < n; j++) {
		    int sum = 0;
		    for (int k = 0; k < n; k++) {
		      sum = matrix1[i * n + k] * matrix2[k * n + j] + sum;
		    }
		  result[i * n + j] = sum;
		  }
		}
    ```
  ]
  - Allows for sum to stay in registers requiring less fetching from memory, a little bit faster.
]

#slide(title: "Intermediate Sum Matrix Multiply")[
 #figure(
  image("images/naive_sum_c.pdf", width: 55%),
  )
]

#slide(title: "Loop Re-ording Matrix Multiply")[
  #framed(title: "Loop Re-ording Sum")[
  #set text(size: 16pt)
    ```c
  	for (int i = 0; i < n; i++) {
  	  for (int k = 0; k < n; k++) {
  	    for (int j = 0; j < n; j++) {
  	      result[i * n + j] += matrix1[i * n + k] * matrix2[k * n + j];
  	    }
  	  }
  	}
    ```
  ]
  - Re-ording the last two loops (j with k) enabling better caching behavior.
]

#slide(title: "Loop Re-ordering Matrix Multiply")[
 #figure(
  image("images/naive_sum_strip_c.pdf", width: 55%),
  )
]

#slide(title: "Block Matrix Multiply")[
  #framed(title: "Blocking")[
  #set text(size: 12pt)
    ```c
		for (int ii = 0; ii < n; ii+= BLOCK_SIZE) {
      for (int kk = 0; kk < n; kk+= BLOCK_SIZE) {
        for (int jj = 0; jj < n; jj+= BLOCK_SIZE) {
          int limit_i = ((ii + BLOCK_SIZE) < n) ? (ii + BLOCK_SIZE) : n;
          int limit_j = ((jj + BLOCK_SIZE) < n) ? (jj + BLOCK_SIZE) : n;
          int limit_k = ((kk + BLOCK_SIZE) < n) ? (kk + BLOCK_SIZE) : n;
          for (int i = ii; i < limit_i; ++i) {
            for (int k = kk; k < limit_k; ++k) {
              int ki = i * n + k;
              for (int j = jj; j < limit_j; j++) {
                result[i * n + j] += matrix1[ki] * matrix2[k * n + j];
              }
            }
          }
        }
      }
    }

    ```
  ]
]
#slide(title: "Block Matrix Multiply")[
	#figure(
	image("images/gemm_tiled.png", width: 80%),
	caption: [GEMM tiling or BLOCK_SIZE.#footnote[Mathhes et. al. Tuning and Optimization for a Variety of Many-Core Architectures Without Changing a Single Line of Implementation Code Using the Alpaka Library (2017)]]
	)
]

#slide(title: "Block Matrix Multiply")[
  - This is where optimizations start becoming unpleasant as it is not hardware agnostic, however we are not using intrinsics yet!

  - The ``BLOCK_SIZE`` variable is a compile time constant, requiring the library to be recompiled.

  - We will recompile until we find an optimal BLOCK_SIZE value.

]


#slide(title: "Loop Re-ordering Matrix Multiply BLOCK_SIZE")[
 #figure(
  image("images/block_c.pdf", width: 55%),
  )
]
#slide(title: "Whole Program Performance Metrics")[
  #framed(title: "BLOCK_SIZE 512")[
  #set text(size: 14pt)
   ```bash
  ❯ perf stat -e cycles,instructions,cache-references,cache-misses ./build/driver 2048 2048 5
  2048, 5, 49152, 0.792592, 5.714694, 0.007886

  Performance counter stats for './build/driver 2048 2048 5':

    22,990,040,828      cycles:u
    26,574,845,684      instructions:u                   #    1.16  insn per cycle
     7,550,989,191      cache-references:u
       121,521,554      cache-misses:u                   #    1.61% of all cache refs
  ```
  ]
  - Naive L3 cache misses was 7.68%, PAPI would give better resolution. There is still better cache performance possible.
]

#slide(title: "All Methods")[
 #figure(
  image("images/all_c.pdf", width: 55%),
  )
]

// Instruction Set
#slide(title: "What CPU do I have?")[
  #framed(title: "Checking the Hardware")[
  #set text(size: 16pt)
    ```bash
    ❯ for i in Architecture "CPU(s):" "Model name" Thread Socket "NUMA node(s)"; do lscpu | grep "$i" | grep -v "node0"; done

    Architecture:                         x86_64
    CPU(s):                               16
    Model name:                           Intel(R) Core(TM) i7-10700KF CPU @ 3.80GHz
    Thread(s) per core:                   2
    Socket(s):                            1
    NUMA node(s):                         1
    ```
  ]
]


// Instruction Set (Overview)
#slide(title: "Instructions Set Architecture (ISA)")[
  - ``x86``#footnote[ARM has different names for everything] SIMD #footnote[Single Instruction, Multiple Data] extensions:
    - *SSE (Streaming SIMD Extensions)* - 128-bit floating point registers
    - *SSE2* - 128-bit doubles and integer registers
    - *AVX (Advanced Vector Extensions)* - 256-bit floating/double point registers
    - *AVX2* - 256-bit integer SSE instructions
    - *AVX512* - 512 bit registers!
  - *FMA(Fused Multiply-Add)* - Exists in AVX, AVX512, but only for floats and doubles.
]


#slide(title: "Instructions Set Architecture (ISA)")[
  #framed(title: "Checking the Architecture and ISA")[
  #set text(size: 14pt)
  ```bash
  ❯ cat /sys/devices/cpu/caps/pmu_name
  skylake

  ❯ for isa in sse sse2 avx avx2 avx512 fma; do grep -q "$isa" /proc/cpuinfo && echo "$isa  1" || echo "$isa  0"; done
  sse  1
  sse2  1
  avx  1
  avx2  1
  avx512  0
  fma  1
  ```
  ]
]

#slide(title: "Instructions Set Architecture (ISA)")[
  #framed(title: "Checking for SIMD (AVX2)")[
  #set text(size: 10pt)
  ```assembly
    10b0:	c4 c2 7d 40 4c 8a a0 	vpmulld -0x60(%r10,%rcx,4),%ymm0,%ymm1
    10b7:	c4 c2 7d 40 54 8a c0 	vpmulld -0x40(%r10,%rcx,4),%ymm0,%ymm2
    10be:	c4 c2 7d 40 5c 8a e0 	vpmulld -0x20(%r10,%rcx,4),%ymm0,%ymm3
    10c5:	c4 c2 7d 40 24 8a    	vpmulld (%r10,%rcx,4),%ymm0,%ymm4
    10cb:	c4 c1 75 fe 4c 88 a0 	vpaddd -0x60(%r8,%rcx,4),%ymm1,%ymm1
    10d2:	c4 c1 6d fe 54 88 c0 	vpaddd -0x40(%r8,%rcx,4),%ymm2,%ymm2
    10d9:	c4 c1 65 fe 5c 88 e0 	vpaddd -0x20(%r8,%rcx,4),%ymm3,%ymm3
    10e0:	c4 c1 5d fe 24 88    	vpaddd (%r8,%rcx,4),%ymm4,%ymm4
    10e6:	c4 c1 7e 7f 4c 88 a0 	vmovdqu %ymm1,-0x60(%r8,%rcx,4)
    10ed:	c4 c1 7e 7f 54 88 c0 	vmovdqu %ymm2,-0x40(%r8,%rcx,4)
    10f4:	c4 c1 7e 7f 5c 88 e0 	vmovdqu %ymm3,-0x20(%r8,%rcx,4)
    10fb:	c4 c1 7e 7f 24 88    	vmovdqu %ymm4,(%r8,%rcx,4)
  ```
  ]
  - Excerpt from multiplication library (appears some pipelining is going on!) #footnote[More details can be found in the Intel Intrinsics Guide].
]

#slide(title: "Work per Clock Cycles (Normalized Data)")[
 #figure(
  image("images/all_cycle_c.pdf", width: 55%),
  )
]


// Compilers
#slide(title: "GCC vs. Clang")[
 #figure(
  image("images/all_compiler_c.pdf", width: 55%),
  )
]

// Conclusion Slide
#slide(title: "Long Journey (Int32)")[
  #align(center)[
    #figure[
      #table(
      columns: 4,
      []   , table.cell(colspan:3, [*Runtime (s)*]),
      [*Matrix size (n)*], [*Pure Python*], [*Python (NumPy)*], [*Blocked C*],
      [256],  [0.24], [0.02], [0.001],
      [512],  [1.79], [0.18], [0.01],
      [1024], [15.32],[1.46], [0.10],
      [2048], []    , [26.40], [0.81],
      [4096], []    , []      ,[6.55],
      )
    ]
  ]
  - Final results with the different run times. More optimization is possible for C and NumPy.
]







// Title slides create new sections
#title-slide[
  More Discussion
]

// Types Matter
#slide(title: "Integers, Floats, Bits, each Matter")[
	- Libraries exists with hyper optimized floating-point matrix operations standardized by BLAS #footnote[Basic Linear Algebra Subprograms].
		- *ATLAS* - Automatically Tuned Linear Algebra Software
		- *OpenBLAS* - open-source CPU based BLAS
		- *rocBLAS* - AMD's GPUs version via ROCM
		- and many more #footnote[https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms#Implementations]
	- Sparsity may drive to different algorithms.
	- If working with integers you may have to write your own kernels.
	- If working with Boolean matrices they allow for new algorthms using look-up tables #footnote[Method of Four Russians]
]

// Parallelization Matter
#slide(title: "Parallelization (Things we did not go over)")[
  - *OpenMP/PThreads*
    - Using all cores on a socket/node
  - *Simultaneous Multithreading (SMT/HyperThreading)*
    - Should it be used?
  - *Non-Uniform Memory Access (NUMA)*
    - Even more levels to the memory subsystem
    - AMD's Core Complex (CCX) have made this harder
  - *MPI/SHMEM*
    - Inter-node communication using remote direct memory access (RDMA)
]

// Focus slide
#focus-slide[
  Questions?
]

