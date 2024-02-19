#include <vector>
#include <iostream>

int fastFind(std::vector<double> &A, double key){
    int middle = A.size()/2;
    int left = 1;
    int right = A.size()-1;

    while(left<=right){
        if(A[middle] == key){
            return middle;
        }
        else if(key < A[middle]){
            right = middle-1;
        }
        else{
            left = middle+1;
        }
    }
    return -1;
}