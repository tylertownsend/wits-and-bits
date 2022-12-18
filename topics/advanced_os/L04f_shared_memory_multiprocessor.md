# Overview
Understand principals that go into shared memory multiprocessor.

# OS for Parallel Machines
- Memory latency increases
- Non uniform access machine (NUMA)
  - Memory local to it or accessing memory on another machine
- Deep memory heirarchy
- False sharing
  - No programtic sharing but due to cores sharing the same cacheline then it appears shared.

## Principals
1. Cache conscious decisions
  - locality
2. limit amount of sharing in system data structures
3. Keep memory access local

## Page fault service
1. CPU generates virtual page number
2. CPU does a TLB lookup
3. If TLB lookup fails, then the cpu checks if the page has been looaded in page table
   from disk
4. Handler locate file on disck
5. OS service allocates a page frame for the dataa
6. Page Table is updated `vpn` and `pfn` (Virtual page number) and (page frame number)
7. TLB is updated with `vpn` and `pfn`
8. Page Frame service complete.

Always  avoid serialization (I/O).

TLB and PT Lookups and TLB updates are thread and processor sepcific, respecitiely and avoid serialization.

## Parallel OS and Page Fault Service
| Easy Scenario | Hard Scenario |
| ------------- | ------------ |
| Multiprocess workload | Multithreaded workloaded |
| Threaads independent | Address space shared |
| Page tables distinct | Page Table Shared |
| No Serialization | Shared entries in processors TLB |

## Scalable Structure for Parallel OS
- minimize share data structures for each sub system
- where possible replicate/partition system data structures for each sub system
  - less locing and more concurrency

## Tornado
Clustered Object- Illusion of single object, but under coveres has multiple representations
- degree of clustering
  - choice of service

## Traditional Structure
Virtual memory substyem and File system uses a page cache (DRAM), which uses Storage Substystem (on disk)

For scalability, we eliminate centralized datastructures as possible.

# Objectation
## Memory Management
Address space is broken into regions.
- Carve up backing storage => file cache manager for each region
- Page Frame Manager => DRAM object
- Page I/O => Cached object representation (COR)

## Dynamic Memory Allocation
[Stack | Heap | Static | Code]
Parition heap with regions for each processor

## IPC
Clustered objects needs to communicate with the microkernel design.
Object calls between client/server arch

- Realized by PPC
- Replicas manangement is done by software