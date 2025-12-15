import matplotlib.pyplot as plt

# Initialize lists to store data
n = []          # List for 'n' (number of elements)
time_trial = [] # List for 'time/trial (s)'

# Read the data from the file
with open('../data/naive.txt', 'r') as file:
    # Skip the header line
    next(file)

    # Read each line, split by commas, and extract relevant columns
    for line in file:
        # Strip leading/trailing whitespaces and split by commas
        values = line.strip().split(', ')

        # Extract n (first column) and time/trial (4th column)
        n.append(int(values[0]))                # n is the first column
        time_trial.append(float(values[3]))     # time/trial is the 4th column

# Create the plot
plt.figure(figsize=(8, 6))

# Plotting n vs time/trial
plt.plot(n, time_trial, marker='o', color='b', linestyle='-', linewidth=2, markersize=8, label="Naive C")

# Adding labels and title
plt.xlabel('n (Number of elements)', fontsize=12)
plt.ylabel('Time per trial (s)', fontsize=12)
plt.title('Time per Trial vs Matrix Size', fontsize=14)

# Adding grid for better visibility
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Display the plot
plt.show()

