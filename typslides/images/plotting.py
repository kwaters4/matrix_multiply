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
plt.plot(naive['n'], naive[' time/trial (s)'], marker='o', color='b', linestyle='-', linewidth=2, markersize=8, label="Naive C")
#plt.plot(python['n'], python[' time (s)'], marker='o', color='r', linestyle='-', linewidth=2, markersize=8, label="Python NumPy")
plt.plot(summed['n'], summed[' time/trial (s)'], marker='o', color='r', linestyle='-', linewidth=2, markersize=8, label="Sum C")
plt.plot(strip['n'], strip[' time/trial (s)'], marker='o', color='g', linestyle='-', linewidth=2, markersize=8, label="Loop Re-ording C")
plt.plot(blocked['n'], blocked[' time/trial (s)'], marker='o', linestyle='-', linewidth=2, markersize=8, label="Block (512) C")
plt.xlim([128, 5000])
plt.xscale('log', base=2)

def custom_log_ticks(x, pos):
    return int(x)  # Convert x to integer for displaying full numbers

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(custom_log_ticks))

# Adding labels and title
plt.xlabel('n (Number of elements)', fontsize=12)
plt.ylabel('Time (s)', fontsize=12)
plt.title('Time vs Matrix Size', fontsize=14)

# Adding grid for better visibility
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Add legend
plt.legend(loc="upper left")

# Show the plot
#plt.savefig("naive_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_strip_c.pdf", format='pdf', bbox_inches='tight')
plt.savefig("all_c.pdf", format='pdf', bbox_inches='tight')
