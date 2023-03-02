This programming project is to add support for executing queries in a database system. We will implement executors that are responsible for taking query plans and executing them. We will create executors that perform sequential scans, hash joins and aggregations.

We will use the iterator query processing model (i.e., the Iterator model). Every query plan either returns a single tuple or indicates that there are no more tuples. This lets the executor implement a loop that just keeps calling `Next` on its children to get and process their tuples.

The project is comprised of the following task:

- Executor #1 - Sequential Scans (We provide complete reference code)
- Executor #1 - Filter Sequential Scans
- Executor #2 - Nested Loop Join
- Executor #3 - Hash Join

In this project, we fixed the tuple type and table type. All tables have the same schema: 
  - `id`: int type, primary key.
  - `val1`: int type value.
  - `val2`: string type value.

## Executors

### SEQUENTIAL SCANS

Sequential scans iterate over a table and return its tuples one-at-a-time. We pass in the table to iterate in the initialization function. This simple sequential scans doesn't support filter by predicate.

### FILTER SEQUENTIAL SCANS

This executor is similar to the simple sequential scans executor. But it support the predicate filter function. We pass in the table and predicate in the initialization function.

### NESTED LOOP JOIN

This executor will have only once child that propagates tuples corresponding to the outer table of the join. For each of these tuples, you will need to find the corresponding tuple in the inner table that having the same value on the join key.

### HASH JOIN

Hash joins are used to combine the results of two child executors together. By convention the left child is used to build the hash table and the right child is used to probe.

We are providing you with a `SimpleHashJoinHashTable` implementation. You can use it to build the hash table and probe.

We also provide the `SimpleHashFunction` to convert a specify tuple attribute to a hash value. We pass in the hash function in the initialization of the executor, you can easily use it by calling `hash_fn->GetHash(tuple)` and don't need to take care of the join key.

## Build

run the following commands to build the system:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Testing

You can test the individual components of this assignment using our testing file in the (`test/`) folder, you can modify this file to test and debug the functionality.

We just provide simple sample test cases in the testing file. We will use more complex test cases for grading.

**Hint**: We recommend you to read the test code to have a clear idea about the whole query execution process. You can try the seq_scan_test first.

```
$ cd build
$ make seq_scan_test
$ ./seq_scan_test
```
