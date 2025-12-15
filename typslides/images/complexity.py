import matplotlib.pyplot as plt
import numpy as np

plt.rcParams.update({'font.size': 16})

# Data
years = [
    1965, 1969, 1978, 1979, 1981, 1981, 1981, 1986, 1990,
    2010, 2012, 2014, 2020, 2022, 2024, 2024
]

omega = [
    3.00, 2.8074, 2.796, 2.780, 2.522, 2.517, 2.496, 2.479, 2.3755,
    2.3737, 2.3729, 2.3728639, 2.3728596, 2.371866, 2.371552, 2.371339
]

labels = [
    "Naive",
    "Strassen",
    "Pan",
    "Bini et al.",
    "Schönhage",
    "Romani",
    "Coppersmith–Winograd",
    "Strassen",
    "Coppersmith–Winograd",
    "Stothers",
    "Williams",
    "Le Gall",
    "Alman–Williams",
    "Duan–Wu–Zhou",
    "Williams et al.",
    "Alman et al."
]

# Plot
plt.figure(figsize=(10, 6))
plt.plot(years, omega, marker='o', linestyle='-', linewidth=2)

# Create jitter offsets
#x_jitter = np.linspace(-1, 1, len(labels))
y_jitter =  nums = np.random.uniform(0, 10, size=len(labels))
x_jitter =  nums = np.random.uniform(0, 10, size=len(labels))

# Annotate with jitter
for x, y, label, dx, dy in zip(years, omega, labels, x_jitter, y_jitter):
    plt.annotate(
        label,
        (x, y),
        textcoords="offset points",
        xytext=(dx, dy),
        fontsize=8,
        rotation=75,
        arrowprops=dict(arrowstyle='-', lw=0.5, alpha=0.6)
    )

# Formatting
plt.xlabel("Year")
plt.ylabel("Matrix Multiplication Exponent (ω)")
plt.title("Progress on the Matrix Multiplication Exponent")
plt.grid(True)

plt.tight_layout()
plt.savefig("complexity.pdf", format='pdf', bbox_inches='tight')

