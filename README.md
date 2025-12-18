# CS-300

//analysis of the run-time and memory for the data structures.

Operation	                   Vector	          Hash Table		            Binary Search Tree
Load from file (worst case)	 O(n)	            O(n²) (hash collisions)		O(n²) (an unbalanced tree)
Sorted listing	             O(n log n)	      O(n log n)		            O(n)  in-order traversal
Search for course	           O(n)	            O(1) avg, O(n) worst		  O(log n) avg, O(n) worst
Memory usage	               O(n)	            O(n)		                  O(n)

-Explain the advantages and disadvantages of each structure in your evaluation.
The vector data structure provides the most consistent and fastest loading performance, because new elements are simply appended to the end of the list in O(1) time. However, vectors do not support efficient searching. To locate a specific course, the program must scan through the entire list, which results in a slow O(n) lookup time. Vectors also do not maintain sorted ordering automatically, so displaying an alphanumeric list of courses would require an additional sorting step.
The hash table structure provides very fast average-case searching and retrieval, with O(1) lookup time when hash collisions are low. This makes it a strong option for quickly finding a single course along with its prerequisites. The main drawback is that hash tables do not store elements in any specific order. To print all courses in alphanumeric order, the program would need to extract every entry and sort them first, making the operation less efficient. Collisions can also significantly slow performance under certain input patterns.
The binary search tree (BST) supports efficient average-case search and insertion in O(log n) time by comparing course numbers and traversing left or right through the tree. A major advantage of the BST is that it naturally maintains the courses in sorted order as they are inserted, enabling fast and straightforward alphanumeric listing using in-order traversal. The main disadvantage is that if the tree becomes unbalanced, such as when course numbers are inserted in sorted order, the height of the tree can grow to n-1. This causes searches and insertions to go from O(log n) on average to O(n) in the worst case.


-make a recommendation for which data structure you plan to use in your code.
After comparing all three data structures, the binary search tree is the best overall choice for this advising program. Vectors are easy to use, but because they rely on linear searches, finding a specific course would get slower as the course list grows. Hash tables are much faster for lookups, but they don’t keep the data in any particular order. That means we would have to pull everything out and sort it separately anytime we need an alphabetical list. 
	The BST gives us the best balance of features for what the advisors want to do. It allows quick lookups and insertions on average, and it automatically keeps courses sorted by course number. That makes printing the entire list in alphanumeric order simple and efficient with an in-order traversal. Even though a BST can slow down if it becomes unbalanced, its strengths in both searching and sorted output makes it the most effective structure to use in this project.


//code that will sort and print out a list of the courses in the Computer Science program in alphanumeric order.

// Prints all courses in alphanumeric order using in-order traversal.
void printCourseListTree(const CourseBST& courseTree) {
    if (courseTree.isEmpty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    cout << "Here is a sample schedule:" << endl;
    courseTree.inOrderTraversal();
}
