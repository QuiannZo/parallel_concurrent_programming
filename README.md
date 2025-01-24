# concurrente23b-quiann_zolfaghari

## Glossary

- Serial programming: The program runs in a single thread of a process. This means that the program is executed serially as the name implies.

- Concurrent programming: You have several tasks running that do not necessarily run at the same time. A task can progress independently of the others. It executes x program concurrently, and memory can be shared in the parent process.

- Parallel programming: Runs concurrently. Parts of a process that can run independently are identified, in order to achieve parallelism. OMP allows marking the regions where this can be done.

- Task concurrency: Refers to the simultaneous execution of several independent tasks.

- Data parallelism: Data is divided and processed in parallel. This involves separating units of work and mapping.

- Thread: Unit of execution dependent on a process. A program can have multiple threads of execution, each performing tasks concurrently.

- Indeterminism: Refers to the impossibility of predicting the exact order of execution of tasks in a concurrent program. This is natural, however, it can be “avoided” by using barriers.

- Private and shared memory: Shared memory is the memory that all threads of a program share. Private memory is the memory of each thread, with its parameters, or whatever data it wants to store.

- Active waiting: Consists of a thread actively waiting for something to happen without using resources. This is obviously negative since it wastes resources.

- Race condition: The result of the execution of a program depends on the execution order of the instructions, and this order is not somehow determined by the programmer. This causes errors.

- Concurrency control: Refers to the techniques and mechanisms used to ensure that concurrent operations do not interfere with each other.

- Conditional safety: Can be used in data parallelism. It allows threads to access data without generating race conditions.

- Mutual exclusion: Two or more threads cannot execute critical sections of code simultaneously.

- Semaphore: A semaphore is a synchronization variable used to control access to resources shared by threads.

- Barrier: A synchronization mechanism that allows multiple threads to wait until all threads have reached a specific point of execution before continuing with the process. When it reaches x amount, it “lets threads through”.

- Condition variable: A variable used to synchronize threads. Signal lets one thread through, broadcast to all.

- Read-write lock: A mechanism that allows multiple threads to simultaneously read a critical section but where only one thread can write to the section at a time.

- Decomposition: Breaking a large problem into smaller parts that can be solved concurrently. It is directly related to mapping.

- Mapping: Mapping consists of dividing a workload so that it can be worked concurrently. There are several types of mapping that should be used depending on the usefulness in each case.

- Speed increase: The improvement in the performance of a program achieved through parallel or concurrent programming.

- Point-to-point inter-process communication: Direct data transfer between two concurrent processes.

- Collective inter-process communication: Transfer of data between multiple processes.

- Reduction: A process in which multiple partial results are combined to produce a final result. Some operation must be performed at the end to “join” the data.