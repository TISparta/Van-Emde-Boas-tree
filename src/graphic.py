import matplotlib.pyplot as plt
from matplotlib.pyplot import clf

n_elements = [1, 2, 3, 4, 5, 6]

def parse (s):
    arr = s.split()
    t_VEB_Tree = float(arr[3])
    t_set = float(arr[5])
    return t_VEB_Tree, t_set

N_OPERATIONS = 5

times_VEB_Tree = [[] for _ in range(N_OPERATIONS)]
times_set = [[] for _ in range(N_OPERATIONS)]

for n in n_elements:
    file_name = "./times/time-" + str(10 ** n) + ".md"
    with open(file_name) as file:
        header = file.readline()
        _ = file.readline()
        for op in range(N_OPERATIONS):
            a, b = parse(file.readline())
            times_VEB_Tree[op].append(a)
            times_set[op].append(b)

# Insert
plt.plot(n_elements, times_VEB_Tree[0], color = 'red')
plt.plot(n_elements, times_set[0], color = 'blue')
plt.xlabel('k: Number elements (10 ^ k)')
plt.ylabel('Time (s)')
plt.legend(['Insert VEB Tree', 'Insert std::set'])
plt.savefig('./graphics/insert.jpg')
clf()

# Lookup
plt.plot(n_elements, times_VEB_Tree[1], color = 'red')
plt.plot(n_elements, times_set[1], color = 'blue')
plt.xlabel('k: Number elements (10 ^ k)')
plt.ylabel('Time (s)')
plt.legend(['Lookup VEB Tree', 'Lookup std::set'])
plt.savefig('./graphics/lookup.jpg')
clf()

# Predecessor
plt.plot(n_elements, times_VEB_Tree[2], color = 'red')
plt.plot(n_elements, times_set[2], color = 'blue')
plt.xlabel('k: Number elements (10 ^ k)')
plt.ylabel('Time (s)')
plt.legend(['Predecessor VEB Tree', 'Predecessor std::set'])
plt.savefig('./graphics/predecessor.jpg')
clf()

# Successor
plt.plot(n_elements, times_VEB_Tree[3], color = 'red')
plt.plot(n_elements, times_set[3], color = 'blue')
plt.xlabel('k: Number elements (10 ^ k)')
plt.ylabel('Time (s)')
plt.legend(['Successor VEB Tree', 'Successor std::set'])
plt.savefig('./graphics/successor.jpg')
clf()

# Erase
plt.plot(n_elements, times_VEB_Tree[4], color = 'red')
plt.plot(n_elements, times_set[4], color = 'blue')
plt.xlabel('k: Number elements (10 ^ k)')
plt.ylabel('Time (s)')
plt.legend(['Erase VEB Tree', 'Erase std::set'])
plt.savefig('./graphics/erase.jpg')
clf()

