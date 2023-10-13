# Optimization 1: Serial

The first optimization is of free choice for the serial version. This document will start with the first optimization made for the algorith and its proof of performance increase.

## Iteration 01.

### Step 1: Testing performance with the non modified version. Small case.

![Alt text](perf_serial_01.png)

This example demostrates the duration of the program without modifications of any kind.

### Step 2: Profiling.

![Alt text](profiling_01-1.png)

As you can see, the open_file function is being called several times. This is the part of the code to optimize.

### Step 3-4: Optimization (design).

For optimizing the solution my idea is to cut the number of cycles done by the program by breaking the two for loops when a password is found. While generating passwords is fast, this still improves performance in an interesting way, specially for bigger problems. The design is simple, a break inside the if statement that is entered when a password is successfully found.

### Step 5: Results (speedup and performance) and lessons learned.

This optimization increased the performance of the solution by reducing the number of iterations when a file has a password. The tests were done on small cases, medium and big cases will be tested as well to fill the report sheet. The results were the following:

    Serial solution:                    10,367784450
    serial solution (optimized):         10,1261633035

The performance increased successfully, and in bigger cases it will decrease time on a larger scale. Despite its simplicity I think this is an obvious improvement on code that was already optimized. In terms of load, the open_file function is still the heavier.

![Alt text](perf_serial_01-2.png)

![Alt text](perf_serial_01_1.png)

# Optimization 2: Pthread.

The second optimization is an extension of the first program, now being parallel. This optimization as mentioned in the instructions is already done, but I will show some results on the performance improvements achieved thanks to multithreading. Detailed data of the optimization and its results can be encountered on the sheet.

Here we have a comparison of performance on the same task of a serial and a parallel version of the program. Note that these mesurements are limited by the machine used which has only 4 threads. The final results written in the sheet are tested with an 8 core machine.

![Alt text](pthread_01.png)

![Alt text](pthread_02.png)

The performance increased by a lot, but the machine limited the potencial of the parallel solution. 