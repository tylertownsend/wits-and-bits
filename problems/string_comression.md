# String Compression
## Problem
Given a string, write a function to compress it by shortening every sequence of the same character to the character followed by the number of repititions. If the compressed string is longer than the original return the original.

### Examples
| Input | Output |
|-------| ------ |
|"a" | "a" |
| "aaa" | "a3" |
| "aaabccc | "a3bc3 |

## Breakdown
Let's break down the problem and understand what we are trying to do. We know that there are two possible results:
1. A compressed string
2. The original string

1 is only possible if 2 is smaller.

### Strategy
 1. Let's loop through the string and keep a count of the current character
   - This assumes, we should be able to reconstruct the string given the compressed string.
   - If we do not need to reconstruct, then we could simply create a frequency array.
 2. Look ahead of  the current character and check to see if the next character is the same
    1. If it is, then we can increase the count.
    2. If not then we append the current character and count and reset the count to 1 for the next character
 3. Once the for loop ends, we must add the last result

## Code
```java
public String compress(String originalString) {
  String compressedString = "";
  int count = 1;

  for (int i = 0; i <= originalString.length() - 1; i++) {
    if (originalString.charAt(i) == originalString.charAt(i + 1)) {
      count++;
    } else {
      compressedString = compressedString + originalString.charAt(i) + String.parseInt(count);
      count = 1;
    }
  }
  compressedString = compressedString + originalString.charAt(originalString.length() - 1) + String.parseInt(count);
  return compressedString.length() < originalString.length() ?
    compressedString :
    originalString;
}
```

### Complexity
The algorithm appends characters to a string, an increments a counter variable. Both of these operations are `O(1)`. Since the
algorithm iterates looks at every character in the original string, the upper bound on the numbr of iterations is `n`.

Therfore, the time complexity is `O(n)`.