import os
import subprocess
import matplotlib.pyplot as plt
plt.rcParams['figure.figsize'] = [15, 10]

mnk_list          = []
new_avg_time_list = []
old_avg_time_list = []

src_path = './src'

def build_and_run(old_file_name, new_file_name, show=True):
    cmd = []
    cmd.append('g++')
    cmd.append(os.path.join(src_path, 'main.cpp'))
    cmd.append(os.path.join(src_path, 'parameters.hpp'))
    cmd.append(os.path.join(src_path, new_file_name+'.cpp'))
    cmd.append(os.path.join(src_path, old_file_name+'.cpp'))
    cmd.append('-DNEW_'+new_file_name)
    cmd.append('-DOLD_'+old_file_name)
    cmd.append('-O2')
    cmp_process = subprocess.run(cmd)
    if cmp_process.returncode:
        exit(-1)
    
    cmp_process = subprocess.run(['./a.out'], stdout=subprocess.PIPE)

    res = str(cmp_process.stdout, 'utf-8')
    for line in res.split('\n')[:-1]:
        m, n, k, old_avg_time, new_avg_time, diff = line.split(' ')
        mnk_list.append(m)
        old_avg_time_list.append(float(old_avg_time))
        new_avg_time_list.append(float(new_avg_time))
        print('m={}, n={}, k={}, time_consumption(old)={}, time_consumption(new)={}, diff={}'.format(m, n, k, old_avg_time, new_avg_time, diff))

    fig, ax = plt.subplots()
    ax.plot(mnk_list, old_avg_time_list, 'bo-.', label='old:' + old_file_name)
    ax.plot(mnk_list, new_avg_time_list, 'r-*', label='new:' + new_file_name)
    ax.set(xlabel='Matix size', ylabel='Time consuming',
            title='OLD = {}, NEW = {}'.format(old_file_name, new_file_name))
    ax.grid()
    ax.legend()
    if show:
        plt.show()
    else:
        fig.savefig('test.png')
    
