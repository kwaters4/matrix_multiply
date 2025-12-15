import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Initialize lists to store data
naive = pd.read_csv('../../data/naive.txt')
python = pd.read_csv('../../data/python_32.txt')
summed = pd.read_csv('../../data/sum.txt')
strip = pd.read_csv('../../data/strip.txt')
blocked = pd.read_csv('../../data/blocked_512.txt')

# Create the plot
plt.figure(figsize=(8, 6))

# Plotting n vs time/trial
plt.plot(naive['n'], naive[' work/cycle'], marker='o', color='b', linestyle='-', linewidth=2, markersize=8, label="Naive C")
plt.plot(summed['n'], summed[' work/cycle'], marker='o', color='r', linestyle='-', linewidth=2, markersize=8, label="Sum C")
plt.plot(strip['n'], strip[' work/cycle'], marker='o', color='g', linestyle='-', linewidth=2, markersize=8, label="Loop Re-ording C")
plt.plot(blocked['n'], blocked[' work/cycle'], marker='o', linestyle='-', linewidth=2, markersize=8, label="Block (512) C")

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
plt.legend(loc="lower right")

# Show the plot
#plt.savefig("naive_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_strip_c.pdf", format='pdf', bbox_inches='tight')
plt.savefig("all_cycle_c.pdf", format='pdf', bbox_inches='tight')
