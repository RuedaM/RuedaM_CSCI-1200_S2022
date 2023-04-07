//cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Lecture_Notes/Exam02

// This will be posted in an announcement: https://clang.llvm.org/docs/AddressSanitizer.html
// For clang ASAN (Address Sanitizer)
// clang++ -g -fsanitize=address -fno-omit-frame-pointer buggy.cpp
/* Do NOT use the -O1 it may optimize out code (for example, with
 * -O1 you will not see the out of bounds write near the end of
 * our buggy program!) */

// If I'm on Mac need environment variable
//    ASAN_OPTIONS=detect_leaks=1
//   (not going to troubleshoot that. But for one time use, we can do)
//   ASAN_OPTIONS=detect_leaks=1 ./a.out
// On Linux/WSL (maybe Mac) can get better traces with environment variable
//     ASAN_SYMBOLIZER_PATH=[location to llvm-symbolizer]
// On Mac may need to do llvm-dsymutil on your a.out as well?
//     -- I don't have an M1 Mac to test this on.
// On my WSL... we need to find llvm-symbolizer (without version number)
//      ASAN_SYMBOLIZER_PATH=/usr/lib/llvm-6.0/bin/llvm-symbolizer ./a.out

// For clang MSAN (Memory Sanitizer)
// clang++ -O1 -g -fsanitize=memory -fno-omit-frame-pointer buggy.cpp
// Note that this will detect uninitialized reads, ASAN does not!

#include <iostream>

int main() {

  int *p = new int;
  if (*p != 10) std::cout << "hi" << std::endl;

  int *a = new int[3];
  a[3] = 12;
  delete [] a;

}
