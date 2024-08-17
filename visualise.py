from matplotlib import pyplot as plt
from statistics import fmean
import csv
import os
import pickle

RESULT_ROOT = '/home/sbird/collective_results/4'
operations = ['bcast', 'reduce', 'scatter', 'gather', 'allgather', 'reduce_scatter', 'allreduce']
sizes = ['short', 'long', 'builtin']
num_runs = 30
num_ranks = 32
lengths = [2**i for i in range(20, 28)]

results = {}

for i in range(num_runs):
    print('Loading data: %d/%d' % (i, num_runs))
    for operation in operations:
        for size in sizes:
            this_result = '%s_%s' % (operation, size)
            for rank in range(num_ranks):
                if not os.path.isfile('%s/%d/%s/%s_rank_%d_run_%d.csv' % (RESULT_ROOT, i, this_result, this_result, rank, i)):
                    continue
                with open('%s/%d/%s/%s_rank_%d_run_%d.csv' % (RESULT_ROOT, i, this_result, this_result, rank, i)) as csvfile:
                    reader = csv.DictReader(csvfile, fieldnames=['length', 'time'])
                    for row in reader:
                        if this_result not in results:
                            results[this_result] = {}
                        if row['length'] not in results[this_result]:
                            results[this_result][row['length']] = []
                        results[this_result][row['length']].append(row['time'])
                    csvfile.close()

pickle.dump(results, open('results/results.pkl', 'wb'))

for operation in operations:
    print('Creating plot for %s' % operation)
    ax = plt.figure().add_subplot(111)
    for size in sizes:
        this_result = '%s_%s' % (operation, size)
        xs = []
        ys = []
        for length in lengths:
            xs.append(length)
            ys.append(fmean([float(x) for x in results[this_result][str(length)]]))
        ax.scatter(xs, ys, label=size)
    plt.legend(loc='upper left')
    plt.title('%s collective timings, 4 physical nodes' % operation)
    plt.xlabel('Vector size (# floats)')
    plt.ylabel('Time (seconds)')
    plt.savefig('results/%s.png' % operation)
    plt.close()

print('Complete')
