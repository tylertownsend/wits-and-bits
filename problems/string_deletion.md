# Problem
Given a stirng and a dictionary, write a function to determine the minimum number of characters to delete to make a word.

## Example
```
dictionary: ["a", "aa", "aaa"]
query: "abc"

-------
output: 2
```

# Questions
- why exactly are parameters of a dictionary:
  - is it a native set?
  - Is it a class
- Is the dicionary static (not being updated)
- Are we frequently accessing => if not we can do some preprocessing

# Problem Breakdown
- consider BFS
```
        abc            0 characters removed
     /   |   \
    /    |    \
   ab    ac    bc      1 character removed
  /  \  /  \  /  \
  a  b  a  c  b  c     2 characters removed
```

Firstr string we find in dictionary we will be the answer
Always find the shortest path first
Can reduce time not necessarily better complextity