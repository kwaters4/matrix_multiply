
#n = 64
#while n <= 4096:
#    print(n, n*n, 4*n*n/1024, 12*n*n/1024)
#    n = n * 2


import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Data
x = [64, 128, 256, 512, 1024, 2048, 4096]
y2 = [48.0, 192.0, 768.0, 3072.0, 12288.0, 49152.0, 196608.0]

# Create the plot
plt.figure(figsize=(10, 6))

plt.plot(x, y2, marker='s', color='b', linestyle='-', linewidth=3)
plt.xscale('log', base=2)
plt.yscale('log', base=2)

# Customize tick labels to show the full number instead of powers of 2
def custom_log_ticks(x, pos):
    return int(x)  # Convert x to integer for displaying full numbers

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(custom_log_ticks))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(custom_log_ticks))

plt.axhline(y=16*1024, color='black', linestyle='--', label="L3 Cache (16 MiB)", linewidth=3)
plt.axhline(y=256, color='r', linestyle=':', label="L2 Cache (256 KiB)", linewidth=3)
plt.axhline(y=32, color='g', linestyle='-.', label="L1 Cahce (32 KiB)", linewidth=3)

# Labeling the axes
plt.xlabel('Matrix Size (n)')
plt.ylabel('Memory (KiB)')
plt.title('Matrix Multiply Memory Footprint Growth')

# Add legend
plt.legend()

# Show grid
plt.grid(True)

# Show the plot
plt.savefig("memory_scale.pdf", format='pdf', bbox_inches='tight')
