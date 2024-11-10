#include <stdio.h>

void print_union(int a[], int b[], int length_a, int length_b);
void print_union_sorted_arrays(int a_sorted[], int b_sorted[], int length_a, int length_b);
void print_intersect(int a[], int b[], int length_a, int length_b);
void print_intersect_sorted_arrays(int a_sorted[], int b_sorted[], int length_a, int length_b);
void print_diff(int a[], int b[], int length_a, int length_b);


/*
 * This function prints the union of two integer arrays 'a' and 'b'.
 * The union of two sets is a set containing all the distinct elements from both sets.
 * The input arrays are assumed to not include duplicate elements.
 *
 * @param a ,integer array representing the first set.
 * @param b ,integer array representing the second set.
 * @param length_a The number of elements in array 'a'.
 * @param length_b The number of elements in array 'b'.
 * */
void print_union(int a[], int b[], int length_a, int length_b) {
    // Check if both arrays are empty
    if (length_a == 0 && length_b == 0) {
        printf("{}\n");
        return;
    }
    // If array 'a' is empty, print elements of array 'b'
    if (length_a == 0) {
        printf("{");
        for (int i = 0; i < length_b; i++) {
            printf("%d ", b[i]);
        }
        printf("}\n");
        return;
    }
    // If array 'b' is empty, print elements of array 'a'
    if (length_b == 0) {
        printf("{");
        for (int i = 0; i < length_a; i++) {
            printf("%d ", a[i]);

        }
        printf("}\n");
        return;
    }else {

        printf("{");
        // Print elements of array 'a'
        for (int i = 0; i < length_a; i++) {
            printf("%d ", a[i]);
        }
        // Check elements of array 'b' against array 'a'
        for (int i = 0; i < length_b; i++) {
            // Counter to track the number of matches found in array 'a' for each element in array 'b'
            int count = 0;
            for (int j = 0; j < length_a; j++) {
                if (b[i] == a[j]) {
                    break;// Exit inner loop if a match is found
                }
                count++;
                // If no match found in array 'a', print the element from array 'b'
                if (count == length_a ) {
                    printf("%d ", b[i]);
                }
            }
        }
        printf("}\n");
    }
}
/*
 * This function prints the union of two sorted integer arrays 'a_sorted' and 'b_sorted'.
 * The union of two sets is a set containing all the distinct elements from both sets.
 * The input arrays are assumed to be sorted in ascending order.
 * The input arrays are assumed to not include duplicate elements.
 *
 * @param a_sorted, integer array representing the first sorted set.
 * @param b_sorted, integer array representing the second sorted set.
 * @param length_a The number of elements in the first sorted array 'a_sorted'.
 * @param length_b The number of elements in the second sorted array 'b_sorted'.
 * */
void print_union_sortedArrays(int a_sorted[], int b_sorted[], int length_a, int length_b){
    int i = 0; // Index for array 'a_sorted'
    int j = 0; // Index for array 'b_sorted'
    printf("{");
    // Iterate through both arrays until one of them reaches its end
    while(i < length_a && j < length_b){
        // If the current element in 'a_sorted' is smaller, print it
        if(a_sorted[i] < b_sorted[j]){
            printf("%d ", a_sorted[i++]);
        }
        // If the current element in 'b_sorted' is smaller, print it
        else if (b_sorted[j] < a_sorted[i]){
            printf("%d ", b_sorted[j++]);
        }
        // If both elements are equal, print one and move both pointers
        else{
            printf("%d ", a_sorted[i++]);
            j++;
        }
    }
    // Print remaining elements from array 'a_sorted'
    while(i < length_a){
        printf("%d ", a_sorted[i++]);
    }
    // Print remaining elements from array 'b_sorted'
    while(j < length_b){
        printf("%d ", b_sorted[j++]);
    }

    printf("}\n");
}
/*
 * This function prints the intersection of two integer arrays 'a' and 'b'.
 * The intersection of two sets is a set containing all the distinct elements that are common to both sets.
 * The input arrays are assumed to not include duplicate elements.
 *
 * @param a, integer array representing the first set.
 * @param b, integer array representing the second set.
 * @param length_a The number of elements in array 'a'.
 * @param length_b The number of elements in array 'b'.
 * */
void print_intersect(int a[], int b[], int length_a,int length_b) {
    // Check if both arrays are empty
    if (length_a == 0 && length_b == 0) {
        printf("{}\n");
        return;
    }
    // Check if array 'a' is empty
    if (length_a == 0 && length_b != 0) {
        printf("{}\n");
        return;
    }
    // Check if array 'b' is empty
    if (length_a != 0 && length_b == 0) {
        printf("{}\n");
        return;
    // Print the intersection
    }else {
        printf("{");
        for (int i = 0; i < length_b; i++) {
            for (int j = 0; j < length_a; j++) {
                // If there's a match between elements of 'a' and 'b', print the element
                if (b[i] == a[j]) {
                    printf("%d ", b[i]);
                    break;
                }
            }
        }
        printf("}\n");
    }
}
/*
 * This function prints the intersection of two sorted integer arrays 'a_sorted' and 'b_sorted'.
 * The intersection of two sets is a set containing all the distinct elements that are common to both sets.
 * The input arrays are assumed to be sorted in ascending order.
 * The input arrays are assumed to not include duplicate elements.
 *
 * @param a_sorted, integer array representing the first sorted set.
 * @param b_sorted, integer array representing the second sorted set.
 * @param length_a The number of elements in the first sorted array 'a_sorted'.
 * @param length_b The number of elements in the second sorted array 'b_sorted'.
 * */
void print_intersect_sortedArrays(int a_sorted[], int b_sorted[], int length_a, int length_b) {
    int i = 0; // Index for array 'a_sorted'
    int j = 0; // Index for array 'b_sorted'
    printf("{");
    // Iterate through both arrays until one of them reaches its end
    while(i < length_a && j < length_b){
        // If the current element in 'a_sorted' is less than the current element in 'b_sorted', move to the next element in 'a_sorted'
        if(a_sorted[i] < b_sorted[j]){
            i++;
        }
        // If the current element in 'b_sorted' is less than the current element in 'a_sorted', move to the next element in 'b_sorted'
        else if (b_sorted[j] < a_sorted[i]){
            j++;
        }
        // If both elements are equal, print the element and update the flag
        else{
            printf("%d ", a_sorted[i++]); // Print & Move to the next element in 'a_sorted'
            j++; // Move to the next element in 'b_sorted'
        }
    }
    printf("}\n");
}
/*
 * This function prints the difference between two integer arrays 'a' and 'b'.
 * The difference between two sets is a set containing all the elements that are present in 'a' but not present in 'b'.
 * The input arrays are assumed to not include duplicate elements.
 *
 * @param a, integer array representing the first set.
 * @param b, integer array representing the second set.
 * @param length_a The number of elements in array 'a'.
 * @param length_b The number of elements in array 'b'.
 * */
void print_diff(int a[], int b[],int length_a, int length_b){
    // If array 'a' is empty, print an empty set
    if (length_a == 0) {
        printf("{}\n");
        return;
    }
    // If array 'b' is empty, print all elements of array 'a'
    if(length_b == 0){
        printf("{");
        for(int i = 0; i < length_a; i++){
            printf("%d ", a[i]);
        }
        printf("}");
        return;
    }else{
        printf("{");
        // Iterate through elements of array 'a'
        for(int i = 0; i < length_a; i++){
            // Check if the current element of 'a' exists in array 'b'
            for(int j = 0; j < length_b; j++){
                // If a match is found, break the inner loop and move to the next element in 'a'
                if(a[i] == b[j]){
                    break;
                }
                // If the current element of 'a' does not exist in 'b', print it
                if(j == length_b - 1) {
                    printf("%d ", a[i]);
                }
            }
        }
        printf("}\n");
        return;
    }
}

int main() {
    return 0;
}

