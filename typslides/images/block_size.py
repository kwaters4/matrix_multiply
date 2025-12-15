import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Initialize lists to store data
block_32 = pd.read_csv('../../data/blocked_32.txt')
block_64 = pd.read_csv('../../data/blocked_64.txt')
block_128 = pd.read_csv('../../data/blocked_128.txt')
block_256 = pd.read_csv('../../data/blocked_256.txt')
block_512 = pd.read_csv('../../data/blocked_512.txt')
block_1024 = pd.read_csv('../../data/blocked_1024.txt')

# Create the plot
plt.figure(figsize=(8, 6))

# Plotting n vs time/trial
plt.plot(block_32['n'], block_32[' time/trial (s)'], marker='o', color='b', linestyle='-', linewidth=2, markersize=8, label="32")
plt.plot(block_64['n'], block_64[' time/trial (s)'], marker='o', color='r', linestyle='-', linewidth=2, markersize=8, label="64")
plt.plot(block_128['n'], block_128[' time/trial (s)'], marker='o', color='g', linestyle='-', linewidth=2, markersize=8, label="128")
plt.plot(block_256['n'], block_256[' time/trial (s)'], marker='o', color='purple', linestyle='-', linewidth=2, markersize=8, label="256")
plt.plot(block_512['n'], block_512[' time/trial (s)'], marker='o', color='cyan', linestyle='-', linewidth=2, markersize=8, label="512")
plt.plot(block_1024['n'], block_1024[' time/trial (s)'], marker='o', linestyle='-', linewidth=2, markersize=8, label="1024")
#plt.plot(summed['n'], summed[' time/trial (s)'], marker='o', color='r', linestyle='-', linewidth=2, markersize=8, label="Sum C")
#plt.plot(strip['n'], strip[' time/trial (s)'], marker='o', color='g', linestyle='-', linewidth=2, markersize=8, label="Loop Re-ording C")
plt.xlim([128, 5000])
plt.xscale('log', base=2)

def custom_log_ticks(x, pos):
    return int(x)  # Convert x to integer for displaying full numbers

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(custom_log_ticks))

# Adding labels and title
plt.xlabel('Matrxi Size (Number of elements)', fontsize=12)
plt.ylabel('Time (s)', fontsize=12)
plt.title('Time vs Matrix Block Size', fontsize=14)

# Adding grid for better visibility
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Add legend
plt.legend(title="Block Size", loc="upper left")

# Show the plot
plt.savefig("block_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_c.pdf", format='pdf', bbox_inches='tight')
#plt.savefig("naive_sum_strip_c.pdf", format='pdf', bbox_inches='tight')
