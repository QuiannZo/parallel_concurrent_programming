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

### Step 5: Results (speedup and performance) and lessons learned.