BLOOM FILTER IMPLEMENTATION
===========================

Description
-----------
A C++ implementation of a probabilistic Bloom filter data structure with console interface. The Bloom filter efficiently tests whether an element is part of a set, trading some accuracy (possible false positives) for significant memory savings.

Key Features
------------
- Configurable filter size (bit array size)
- Adjustable number of hash functions
- Add elements to the filter
- Check for element presence
- Clear/reset the filter
- Estimate false positive probability
- Interactive console menu system

Technical Specifications
------------------------
Data Structure:
- Uses bit array for compact storage
- Multiple hash functions (based on std::hash with seed variation)
- Configurable size and hash count

Performance:
- Space complexity: O(m) - where m is filter size
- Time complexity: O(k) - where k is number of hash functions
- False positive rate can be mathematically estimated

Building and Running
--------------------
Requirements:
- C++11 compatible compiler (g++ or clang++ recommended)

Compilation:
> g++ bloom_filter.cpp -o bloom_filter -std=c++11

Execution:
> ./bloom_filter

Usage Guide
-----------
1. When starting, you'll be prompted to configure:
   - Filter size (in bits)
   - Number of hash functions to use

2. Main menu options:
   - [1] Add - Insert new element
   - [2] Check - Test if element exists
   - [3] Clear - Reset all bits to 0
   - [4] Estimate - Calculate false positive probability
   - [5] Exit - Quit program

Example Use Cases
-----------------
- Spell checking systems
- Network packet filtering
- Duplicate detection
- Database query optimization
- Blockchain applications

Limitations
-----------
- Cannot remove elements (standard Bloom filter limitation)
- False positives possible (but tunable via parameters)
- Requires upfront sizing based on expected elements

Mathematical Notes
------------------
False positive probability estimated by:
$(1 - e^\frac{-k \times n}{m})^k$
Where:
- k = number of hash functions
- n = number of elements
- m = filter size (bits)