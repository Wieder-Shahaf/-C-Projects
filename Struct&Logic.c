#include <stdio.h>
#include <stdlib.h>

// Define a node structure for a doubly linked list
typedef struct node_t {
    int data;            // Data of the node
    struct node_t *next; // Pointer to the next node
    struct node_t *prev; // Pointer to the previous node
} node_t;

// Define a structure for a set, include nested doubly linked list struct
typedef struct {
    node_t *head; // Pointer to the head of the linked list
    int size;     // Size of the set
} Set;

// Function declaration
void set_init(Set* s, int v[], int num_elements_in_v);
void set_print(Set* s);
Set* set_union(Set* a, Set* b);
Set* set_intersect(Set* a, Set* b);
Set* set_diff(Set* a, Set* b);
int set_contains(Set* s, int element);
void set_add(Set* s, int data);
void remove_duplicates(Set* s);
void set_free(Set* s);


int evaluate_grade() {
    Set set1, set2, *result;
    int v1[] = {1, 2, 3, 4, 5};
    int v2[] = {4, 5, 6, 7, 8};
    int grade = 0;
    int max_grade = 100;
    int error_count = 0;
    int empty_arr[] = {};

    // Test case 1: set_union with empty set
    set_init(&set1, v1, 5);
    set_init(&set2, empty_arr, 0);

    result = set_union(&set1, &set2);


    // Test case 2: set_intersect with empty set
    set_init(&set1, v1, 5);
    set_init(&set2, empty_arr, 0);
    result = set_intersect(&set1, &set2);


    // Test case 3: set_diff with empty set
    set_init(&set1, v1, 5);
    set_init(&set2, empty_arr, 0);
    result = set_diff(&set1, &set2);


    // Test case 4: set_intersect with duplicate elements
    int v3[] = {1, 2, 3, 4, 5, 5};
    set_init(&set1, v1, 5);
    set_init(&set2, v3, 6);
    result = set_intersect(&set1, &set2);


    // Test case 5: set_diff with large sets
    int v4[1000], v5[1000];
    for (int i = 0; i < 1000; i++) {
        v4[i] = i;
        v5[i] = i + 500;
    }
    set_init(&set1, v4, 1000);
    set_init(&set2, v5, 1000);
    result = set_diff(&set1, &set2);


    // Test case 6: Mixed test
    set_init(&set1, v1, 5);
}
int main() {
    // TODO: Remember to use free() for sets created manually and set_free() for sets created with set_init()
    //      to deallocate memory properly before the program exits.
    evaluate_grade();
    return 0;
}

/** Function to initialize a set with elements from an array
    @param s: Pointer to the initialized set
    @param v: Array containing elements to initialize the set with
    @param num_elements_in_v: Number of elements in the array 'v'**/
void set_init(Set* s, int v[], int num_elements_in_v) {
    s->head = NULL; // Initialize head pointer to NULL
    s->size = 0;    // Initialize size of the set to 0

    // Iterate through the array elements and add them to the set
    for (int i = 0; i < num_elements_in_v; i++) {
        // Check if the current element already exist in the set
        int element_found = 0;
        node_t *current = s->head;
        while (current != NULL) {
            if (current->data == v[i]) {
                element_found = 1;
                break;
            }
            current = current->next;
        }

        // If the element doesn't exist, add it to the set
        if (!element_found) {
            node_t *new_node = (node_t*)malloc(sizeof(node_t));
            if (new_node == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            new_node->data = v[i];
            new_node->next = NULL;
            new_node->prev = NULL;

            // Add the new node to the end of the linked list
            if (s->head == NULL) {
                s->head = new_node;
            } else {
                current = s->head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = new_node;
                new_node->prev = current;
            }

            s->size++;
        }
    }
}

/** Function to print the elements of a set
    @param s: Pointer to the set to be printed **/
void set_print(Set* s) {
    printf("{ ");
    node_t *current = s->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf(" }\n");
}

/**
 * Computes the union of two sets 'a' and 'b'.
 * Duplicates are removed from the resulting set.
 *
 * @param a Pointer to the first set
 * @param b Pointer to the second set
 * @return Pointer to the result set (union of sets 'a' and 'b')
 */
Set* set_union(Set* a, Set* b) {
    Set* result = (Set*)malloc(sizeof(Set));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    set_init(result, NULL, 0); // Initialize an empty set for the result

    // Add elements of set 'a' to the result set, removing duplicates
    node_t *current = a->head;
    while (current != NULL) {
        int data = current->data;
        if (!set_contains(result, data)) {
            set_add(result, data);
        }
        current = current->next;
    }

    // Add elements of set 'b' to the result set, removing duplicates
    current = b->head;
    while (current != NULL) {
        int data = current->data;
        if (!set_contains(result, data)) {
            set_add(result, data);
        }
        current = current->next;
    }

    // Print the result set
    set_print(result);

    return result;
}

/**
 * Computes the intersection of two sets 'a' and 'b'.
 *
 * This function modifies set 'a' to store the intersection of sets 'a' and 'b'.
 * It iterates through the elements of set 'a' and removes them if they do not exist in set 'b'.
 * After finding the intersection, it ensures that the result set contains no duplicates.
 * Finally, it prints the resulting set and returns it.
 *
 * @param a Pointer to the first set
 * @param b Pointer to the second set
 * @return Pointer to the result set (intersection of sets 'a' and 'b')
 */
Set* set_intersect(Set* a, Set* b) {
    // Remove duplicates from sets 'a' and 'b'
    remove_duplicates(a);
    remove_duplicates(b);
    // Check if either of the sets is empty
    if (a->head == NULL || b->head == NULL) {
        // If one or both sets are empty, the intersection is empty
        printf("{ }\n");
        return a; // Returning a or b as the result is equivalent when the intersection is empty
    }

    node_t* current = a->head;
    node_t* prev = NULL;

    // Iterate through the elements of set 'a'
    while (current != NULL) {
        int data = current->data;
        if (!set_contains(b, data)) {
            // If the current element of 'a' is not in 'b', remove it
            if (prev == NULL) {
                // If the current node is the head of 'a'
                a->head = current->next;
                free(current);
                current = a->head;
            } else {
                // If the current node is not the head of 'a'
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
            a->size--;
        } else {
            // Move to the next node
            prev = current;
            current = current->next;
        }
    }

    // Print the result set
    set_print(a);

    return a;
}

/**
 * Computes the difference of two sets 'a' and 'b'.
 * The difference of sets 'a' and 'b' is the set of elements that are in 'a' but not in 'b'.
 *
 * @param a Pointer to the first set
 * @param b Pointer to the second set
 * @return Pointer to the result set (difference of sets 'a' and 'b')
 */
Set* set_diff(Set* a, Set* b) {
    // Create a new set for the result
    Set* result = (Set*)malloc(sizeof(Set));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    set_init(result, NULL, 0); // Initialize an empty set for the result

    // Remove duplicates from set 'b'
    Set* unique_b = (Set*)malloc(sizeof(Set));
    if (unique_b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    set_init(unique_b, NULL, 0); // Initialize an empty set for unique elements of 'b'

    node_t* current_b = b->head;
    while (current_b != NULL) {
        set_add(unique_b, current_b->data);
        current_b = current_b->next;
    }

    // Remove elements of set 'b' from set 'a'
    node_t* current_a = a->head;
    while (current_a != NULL) {
        if (!set_contains(unique_b, current_a->data)) {
            set_add(result, current_a->data);
        }
        current_a = current_a->next;
    }

    // Free memory allocated for unique elements of set 'b'
    set_free(unique_b);

    // Print the result set
    set_print(result);

    return result;
}

/**
 * Checks if a given element exists in the set.
 *
 * @param s Pointer to the set
 * @param element The element to search for
 * @return 1 if the element exists in the set, 0 otherwise
 */
int set_contains(Set* s, int element) {
    // Iterate through all elements of the set
    node_t *current = s->head;
    while (current != NULL) {
        // If the element is found, return 1 (true)
        if (current->data == element) {
            return 1;
        }
        current = current->next;
    }
    // If the element is not found, return 0 (false)
    return 0;
}

/**
 * Adds a new element to the set if it doesn't already exist.
 *
 * @param s Pointer to the set
 * @param data The data value of the element to be added
 */
void set_add(Set* s, int data) {
    // Check if the element already exists in the set
    if (set_contains(s, data)) {
        // If the element already exists, return without adding it again
        return;
    }

    // Create a new node for the element
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // If the set is empty, set the new node as the head
    if (s->head == NULL) {
        s->head = new_node;
    } else {
        // Find the last node in the linked list
        node_t *current = s->head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Append the new node to the end of the linked list
        current->next = new_node;
        new_node->prev = current;
    }

    // Increment the size of the set
    s->size++;
}

/**
 * Removes duplicate elements from a given set.
 * If the set is empty or contains only one element, no duplicates are present to remove.
 * This function iterates through each element of the set and checks for duplicates.
 * If a duplicate is found, it removes the duplicate node from the set.
 * The function updates the size of the set accordingly after removing duplicates.
 *
 * @param s Pointer to the set from which duplicates are to be removed
 */
void remove_duplicates(Set* s) {
    // If the set is empty or contains only one element, no duplicates to remove
    if (s->head == NULL || s->head->next == NULL) {
        return;
    }

    // Create a pointer to traverse the set
    node_t* current = s->head;

    // Outer loop to iterate through each element of the set
    while (current != NULL) {
        // Inner loop to check for duplicates of the current element
        node_t* forward = current->next;
        node_t* prev = current; // Pointer to the node before 'forward'

        while (forward != NULL) {
            // If a duplicate is found, remove it
            if (forward->data == current->data) {
                // Remove the duplicate node
                prev->next = forward->next;
                free(forward);
                forward = prev->next;
                s->size--;
            } else {
                // Move to the next node
                prev = forward;
                forward = forward->next;
            }
        }

        // Move to the next node in the outer loop
        current = current->next;
    }
}

/**
 * Frees the memory allocated for the set and its elements.
 *
 * This function deallocates memory for each node in the set and the set itself.
 * It iterates through the linked list starting from the head, frees each node,
 * and updates the current pointer until all nodes are freed. Afterward, it frees
 * the memory allocated for the set structure itself.
 *
 * @param s Pointer to the set to be freed
 *
 * Usage: When you no longer need a set created using set_init(),
 * call this function to free the memory allocated for the set and its elements.
 */
void set_free(Set* s) {
    node_t* current = s->head;
    while (current != NULL) {
        node_t* next = current->next;
        free(current);
        current = next;
    }
}

