//
//  linear.cpp
//  Homework3_Linear
//
//  Created by Tom Slavonia on 2/10/23.
//


bool somePredicate(double x);

// Return true if the somePredicate function returns true for at
      // least one of the array elements; return false otherwise.
    bool anyTrue(const double a[], int n)
    {
        if (n <= 0) {
            return(false);
        }
        else if (somePredicate(a[n - 1])) {
            return(true);
        }
        
        return(anyTrue(a, n - 1));
    }

      // Return the number of elements in the array for which the
      // somePredicate function returns true.
    int countTrue(const double a[], int n) // check this
    {
        int found = 0;
        if (n <= 0) {
            return(found);
        }
        if (somePredicate(a[n-1])) {
            found = found + 1;
        }
        return (found + countTrue(a, n - 1));
    }

      // Return the subscript of the first element in the array for which
      // the somePredicate function returns true.  If there is no such
      // element, return -1.
    int firstTrue(const double a[], int n) // fix this
    {
        n = n - 1;
        if (n < 0) {
            return(-1);
        }
        
        
        if (somePredicate(a[n])) {
            return(n);
        }
        
        return (firstTrue(a, n));
    }

      // Return the subscript of the smallest element in the array (i.e.,
      // return the smallest subscript m such that a[m] <= a[k] for all
      // k from 0 to n-1).  If the function is told that no doubles are to
      // be considered in the array, return -1.
    int indexOfMinimum(const double a[], int n) // fix this
    {
        if (n <= 0) {
            return(-1);
        }
        if (n == 1) {
            return(0);
        }
        int min = indexOfMinimum(a, n - 1);
        if (a[n - 1] < a[min]) { // compares
            return(n - 1); // min index changes
        }
        
        return(min); // keeps min index
    }

      // If all n1 elements of a1 appear in the n2 element array a2, in
      // the same order (though not necessarily consecutively), then
      // return true; otherwise (i.e., if the array a1 is not a
      // not-necessarily-contiguous subsequence of a2), return false.
      // (Of course, if a1 is empty (i.e., n1 is 0), return true.)
      // For example, if a2 is the 7 element array
      //    10 50 40 20 50 40 30
      // then the function should return true if a1 is
      //    50 20 30
      // or
      //    50 40 40
      // and it should return false if a1 is
      //    50 30 20
      // or
      //    10 20 20
    bool isIn(const double a1[], int n1, const double a2[], int n2)
    {
        if (n1 < 0 || n2 < 0) {
            return(false);
        }
        if (n1 > n2) {
            return(false);
        }
        if (n1 == 0 && n2 == 0) {
            return(true);
        }
        
        if (a1[0] == a2[0]) {
            return(isIn(a1 + 1, n1 - 1, a2 + 1, n2 - 1));
        }
        
        return(isIn(a1, n1, a2 + 1, n2 - 1));
        
    }

