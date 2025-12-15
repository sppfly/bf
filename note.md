Bloom filter is a data structure of probability that tells whether an element is within a set. 
A bloom filter is essentially a bit vector of size M, with some hash functions. The number of hash function is N. Of course should M > N, otherwise the additional hash functions are wasted.

To test if an element belongs to a set. Of course we need to tell what the set is. 
For all elements in the set:
    1. Hash them  