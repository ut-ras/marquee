import matplotlib.pyplot as plt
import numpy as np

def reset_lfsr(seed):
    global lfsr
    lfsr = seed

def step_lfsr():
    global lfsr
    # taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1
    input = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1
    lfsr = (lfsr >> 1) | (input << 15)
    return (lfsr, input)

def get_dist_std(bins):
    a = np.array(bins)
    return np.std(a)
    # print(np.std(a))

best_seed = None
best_seed_std = None

NUM_BUCKETS = 8
CHOOSE_N_BUCKETS_PER_IT = int(NUM_BUCKETS/4)
NUM_ITERATIONS = 2**8 - 1
for seed in range(1, 0xFFFF):
    reset_lfsr(seed)
    
    bins = [0 for i in range(0, NUM_BUCKETS)]
    x_vals = []
    y_vals = []
    colors = []
    for i in range(NUM_ITERATIONS):
        for j in range(CHOOSE_N_BUCKETS_PER_IT):
            y_vals.append(i)
            (res, _) = step_lfsr()
            res = res%NUM_BUCKETS
            x_vals.append(res)
            bins[res] += 1
            colors.append((i/NUM_ITERATIONS, 0, 0))
            
    std = get_dist_std(bins)
    # print(f"seed: {seed} w/ std: {std}")
    if best_seed is None or best_seed_std > std:
        print(f"new best std: {std}")
        best_seed = seed
        best_seed_std = std        

print(f'Plotting lfsr w/ best seed {best_seed}')
reset_lfsr(best_seed)

NUM_ITERATIONS = 2**16 - 1
bins = [0 for i in range(0, NUM_BUCKETS)]
x_vals = []
y_vals = []
colors = []
for i in range(NUM_ITERATIONS):
    for j in range(CHOOSE_N_BUCKETS_PER_IT):
        y_vals.append(i)
        (res, _) = step_lfsr()
        res = res%NUM_BUCKETS
        x_vals.append(res)
        bins[res] += 1
        colors.append((i/NUM_ITERATIONS, 0, 0))

print(f'Best seed: {best_seed} w/ std: {get_dist_std(bins)}')
print([i/(NUM_ITERATIONS) for i in bins])
# plt.plot([i for i in range(NUM_BUCKETS)], [i/(NUM_ITERATIONS) for i in bins])
# plt.scatter(x_vals, y_vals, s=3, c=colors)
# plt.show()

print('First 256 bits from lfsr:')
reset_lfsr(best_seed)
for i in range(256):
    (res, bit) = step_lfsr()
    print(bit, end='')
    
print('First 256 bits from lfsr masked by the next bit:')
reset_lfsr(best_seed)
for i in range(256):
    (res, bit) = step_lfsr()
    (res2, bit2) = step_lfsr()
    print(bit&bit2, end='')
    if (i % NUM_BUCKETS) == 0:
        print()