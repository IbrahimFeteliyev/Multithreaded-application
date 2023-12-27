There are three threads (producers threads) that put items into a set (a collection of unsorted items
that can occur only once in the collection) and two threads (consumer threads) that extract items from
the set (you have to choose a random object from the set to extract). Develop a multithreaded application
that organizes their concurrent work. Pay special attention to synchronization issues! c++


output:
Producer 3 produced: 27
Consumer 2 consumed: 27

Producer 2 produced: 43
Consumer 1 consumed: 43

Producer 1 produced: 37
Producer 3 produced: 20
Consumer 2 consumed: 20
Consumer 1 consumed: 37

Producer 1 produced: 45
Producer 2 produced: 71
Consumer 2 consumed: 71
Consumer 1 consumed: 45

