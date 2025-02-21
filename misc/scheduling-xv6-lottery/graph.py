import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV data
data = pd.read_csv('output.csv', header=None)

# Initialize a list to hold each process' tick counts
process_columns = {}

# Iterate through the columns of the CSV file (skip the first column which is iteration)
for col in range(1, data.shape[1], 2):  # Start at 1, increment by 2 (PID, Ticks)
    pid_col = data.iloc[:, col]  # PID column
    ticks_col = data.iloc[:, col + 1]  # Ticks column
    process_columns[f"Process {pid_col.iloc[0]}"] = ticks_col

# Plotting
plt.figure(figsize=(10, 6))

# Plot each process' ticks over iterations
for process, ticks in process_columns.items():
    plt.plot(data[0], ticks, label=process)

# Add labels and title
plt.xlabel('Iteration')
plt.ylabel('Ticks')
plt.title('Process Ticks Over Time')
plt.legend()

# Show the graph
plt.show()
