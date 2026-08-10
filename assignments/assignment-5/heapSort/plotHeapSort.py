import csv
import matplotlib.pyplot as plt

sizes = {"Random": [], "Ascending": [], "Descending": []}
times = {"Random": [], "Ascending": [], "Descending": []}

with open("heapsort_results.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        input_type = row["InputType"]
        sizes[input_type].append(int(row["Size"]))
        times[input_type].append(float(row["Heap"]))

plt.figure(figsize=(9, 6))

plt.plot(sizes["Random"], times["Random"], marker='o', label="Random")
plt.plot(sizes["Ascending"], times["Ascending"], marker='s', label="Ascending")
plt.plot(sizes["Descending"], times["Descending"], marker='^', label="Descending")

plt.xlabel("Input Size (n)")
plt.ylabel("Time (ms)")
plt.title("Heap Sort Runtime vs Input Size")
plt.legend()
plt.grid(True)

plt.savefig("heapsort_plot.png")
plt.show()