#include <stdio.h>
#include <stdlib.h>
/* Function Prototypes */
void change_regular(int n, float coins[], float to_change);
int *copyarray(int *elements, int size);
int *sort_arr(int *elements, int size);

int main() {
    // TODO: If you use the copyarray or sort_arr functions, remember to free the memory allocated for the copied array.

    return 0;
}
/* Function Definitions */

/*
   Calculate the smallest number of coins to be returned as change.

   Parameters:
     - size: The number of elements in the coins array.
     - coins: An array containing coins values.
     - to_change: The amount for which change needs to be calculated.

   Description:
   This function calculates the smallest number of coins required to provide change for the given amount.
   It first sorts the coins array in decreasing order using Insertion Sort.
   Then, it removes duplicate coins values from the sorted array and extracts unique coin amount.
   Next, it calculates the number of coins required for each unique coin to provide change.
   Finally, it prints the number of coins for each value and indicates whether exact change is possible.

   Note:
   The function assumes that coins[] contains only positive values and to_change is non-negative.
*/
void change_regular(int n, float coins[], float to_change){
    /* Sort coins[] using Insertion Sort in decreasing order */
    float key;
    int j;
    for(int i = 1; i < n; i++){
        key = coins[i];
        j = i-1;
        while(j>=0 && coins[j] < key){
            coins[j+1] = coins[j];
            j--;
        }
        coins[j+1] = key;
    }
    /* Find unique coins and assigned 0 for duplicates from the sorted coins array*/
    int current_index = 0; // The element we next_index to
    int next_index = 1; // the element that suspected to be a duplicate
    int count_unique_coins = 0; // will be the size of unique_coins[]
    int flag = 0; // to determent if a unique coins is discover
    while(next_index < n){
        if(coins[current_index] == coins[next_index]) {
            if (!flag) {
                flag = 1;
            }
            coins[next_index++] = 0;
        }
        else{
            flag = 0;
            current_index = next_index;
            next_index++;
        }
    }
    //Initialize the variable count_unique_coins
    for(int i = 0; i < n; i++){
        if(coins[i] != 0){
            count_unique_coins++;
        }
    }

    /*In case coins[] is already unique*/
    if(!count_unique_coins){
        count_unique_coins = n;
    }

    /*Initialize unique_coins array and insert all unique coins from original array*/
    float unique_coins[count_unique_coins];
    int index_coins = 0;
    int index_unique_coins =0;
    while(index_coins < n){
        if(coins[index_coins] != 0){
            unique_coins[index_unique_coins++] = coins[index_coins++];
        }
        else{
            index_coins++;
        }
    }

    /* Initialize an empty change array */
    int change_arr[count_unique_coins];
    for(int i= 0; i < count_unique_coins; i++){
        change_arr[i] = 0;
    }
    /* Calculate change and insert result to change_arr */
    for(int i = 0; i < count_unique_coins; i++){
        if(to_change / unique_coins[i] >= 1){
            change_arr[i] = (int)(to_change / unique_coins[i]);
            to_change = to_change - unique_coins[i] * (float)change_arr[i];
        }
        else{
            continue;
        }
    }
    /* Check if there is no remainder, exact change */
    if(to_change > -0.001 && to_change < 0.001 ){
        int coins_count = 0;
        for(int i = 0; i < count_unique_coins; i++){
            printf("%d coins of type %.2f\n", change_arr[i], unique_coins[i]);
            coins_count = coins_count + change_arr[i];
        }
        printf("Returned exact change!\n");
        printf("%d coins are needed for change\n", coins_count);
    }
    /* If there is a remainder */
    else{
        int coins_count = 0;
        for(int i = 0; i < count_unique_coins; i++){
            printf("%d coins of type %.2f\n", change_arr[i], unique_coins[i]);
            coins_count = coins_count + change_arr[i];
        }
        printf("Exact change is impossible! %.2f reminded.\n", to_change);
        printf("%d coins are needed for change\n", coins_count);
    }
}

/*
   Creates a copy of the input array.

   Parameters:
     - elements: Pointer to the array to be copied.
     - size: Number of elements in the array.

   Description:
   This function creates a new array that is a copy of the input array.
   It allocates memory for the copy using malloc and then copies each element from the original array to the copy.
   The caller is responsible for freeing the memory allocated for the copy using free() when it's no longer needed.

   Returns:
   A pointer to the newly created copy of the array. If memory allocation fails, it returns NULL.
*/
int *copyarray(int *elements, int size){
    /* This pointer will hold the base address of the block created for the copy array */
    int *ptr = (int*) malloc (size * sizeof(int));
    /* Check if malloc failed and print an error message */
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    /* This for loop will copy the array elements to ptr using the pointer elements to the original array */
    for(int i = 0; i < size; i++){
        ptr[i] = *elements++;
    }
    return ptr;
}

/*
   Creates a new sorted array from the input array.

   Parameters:
     - elements: Pointer to the array to be sorted.
     - size: Number of elements in the array.

   Description:
   This function creates a new array that is a sorted copy of the input array.
   It first creates a copy of the input array using the copyarray function.
   Then, it sorts the copy using Insertion Sort in ascending order.
   The caller is responsible for freeing the memory allocated for the sorted array using free() when it's no longer needed.

   Returns:
   A pointer to the newly created sorted array. If memory allocation fails, it returns NULL.
*/
int *sort_arr(int *elements, int size){
    /* Call to copyarray to create a copy to sort and return */
    int *copy = copyarray(elements, size);
    /* Implementing Insertion Sort in ascending order */
    int key, j;
    for(int i = 1; i < size; i++){
        key = copy[i];
        j = i-1;
        while(j >= 0 && copy[j] > key){
            copy[j+1] = copy[j];
            j--;
        }
        copy[j+1] = key;
    }
    return copy;
}

