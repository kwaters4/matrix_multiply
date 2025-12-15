import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Initialize lists to store data
blocked = pd.read_csv('../../data/blocked_512.txt')
blocked_clang = pd.read_csv('../../data/blocked_512_clang.txt')

# Create the plot
plt.figure(figsize=(8, 6))

# Plotting n vs time/trial
plt.plot(blocked['n'], blocked[' work/cycle'], marker='o', linestyle='-', linewidth=2, markersize=8, label="GCC", color='b')
plt.plot(blocked_clang['n'], blocked_clang[' work/cycle'], marker='o', linestyle='-', linewidth=2, markersize=8, label="Clang", color='r')

plt.axhline(y=8, color='black', linestyle=':', label="AVX2 SIMD Vector Length", linewidth=3)

plt.xlim([128, 5000])
plt.xscale('log', base=2)

def custom_log_ticks(x, pos):
    return int(x)  # Convert x to integer for displaying full numbers

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(custom_log_ticks))

# Adding labels and title
plt.xlabel('n (Number of elements)', fontsize=12)
plt.ylabel('Work/Clock Cycle', fontsize=12)
plt.title('Work/Clock Cycle vs Matrix Size', fontsize=14)

# Adding grid for better visibility
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Add legend
plt.legend()

# Show the plot
#plt.savefig("naive_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_strip_c.pdf", format='pdf', bbox_inches='tight')
plt.savefig("all_compiler_c.pdf", format='pdf', bbox_inches='tight')
