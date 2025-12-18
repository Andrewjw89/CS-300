#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;           // Course number
    string title;                  // Course title
    vector<string> prerequisites;  // List of prerequisite course numbers
};

// Node for the binary search tree
struct Node {
    Course course; // Course stored at this node
    Node* left;    // Pointer to left child
    Node* right;   // Pointer to right child

    // Constructor to initialize a new node with a course
    Node(const Course& aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class for Course objects
class CourseBST {
public:
    CourseBST() : root(nullptr) {}

    // Destructor to ensure all dynamically allocated nodes are freed
    ~CourseBST() {
        clear();
    }

    // Insert a course into the BST
    void insert(const Course& course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            insertNode(root, course);
        }
    }

    // Search for a course by courseNumber
    // Returns a pointer to the desired course if found, else returns nullptr
    const Course* search(const string& courseNumber) const {
        Node* current = root;
        while (current != nullptr) {
            if (courseNumber == current->course.courseNumber) {
                return &(current->course);
            }
            else if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr; // Course not found in search
    }

    // In-order traversal printing "courseNumber, title"
    // Prints courses in alphanumeric order by courseNumber
    void inOrderTraversal() const {
        inOrder(root);
    }

    // Returns true if the tree is empty
    bool isEmpty() const {
        return root == nullptr;
    }

    // Clears the tree by deleting all the nodes for memory management 
    void clear() {
        destroyTree(root);
        root = nullptr;
    }

private:
    Node* root; // Root pointer for the BST

    // Recursively inserts a course into the tree
    void insertNode(Node* node, const Course& course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                insertNode(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                insertNode(node->right, course);
            }
        }
    }

    // Recursive in-order traversal
    static void inOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        inOrder(node->right);
    }

    // Recursively deletes all nodes in the tree to free memory
    static void destroyTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
};



// Trim whitespace from both ends of a string
string trim(const string& s) {
    string result = s;

    // Trim front (leading whitespace)
    while (!result.empty() && isspace(result.front())) {
        result.erase(result.begin());
    }

    // Trim back (trailing whitespace)
    while (!result.empty() && isspace(result.back())) {
        result.pop_back();
    }

    return result;
}

// Convert a string to uppercase so course lookups are in proper search case.
string toUpper(const string& s) {
    string result = s;
    for (char& c : result) {
        c = toupper(c);
    }
    return result;
}



// loadCoursesIntoTree(fileName, courseTree)
// Reads the CSV file and inserts Course objects into the BST.
// Returns true if at least one course was loaded successfully.
bool loadCoursesIntoTree(const string& fileName, CourseBST& courseTree) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cout << "Could not open file '" << fileName
            << "'. Please check the name and try again." << endl;
        return false;
    }

    // Start with a fresh tree in case of user loaded file
    courseTree.clear();

    string line;
    int lineNumber = 0;
    int coursesLoaded = 0;

    // Each line represents one course and up to two prereqs    
    while (getline(inFile, line)) {
        ++lineNumber;
        line = trim(line);
        if (line.empty()) {
            continue; // skip empty lines
        }

        string courseNumber;
        string title;
        string prereq1;
        string prereq2;

        stringstream ss(line);
        getline(ss, courseNumber, ',');
        getline(ss, title, ',');
        getline(ss, prereq1, ',');
        getline(ss, prereq2, ',');

        Course course;
        // Ensures proper spacing and case for course number and title
        course.courseNumber = toUpper(trim(courseNumber));
        course.title = trim(title);

        // If prereqs are present, trims white space and stores
        prereq1 = trim(prereq1);
        prereq2 = trim(prereq2);

        if (!prereq1.empty()) {
            course.prerequisites.push_back(toUpper(prereq1));
        }
        if (!prereq2.empty()) {
            course.prerequisites.push_back(toUpper(prereq2));
        }

        if (!course.courseNumber.empty()) {
            courseTree.insert(course);
            ++coursesLoaded;
        }
    }

    if (coursesLoaded == 0) {
        cout << "No course data found in file '" << fileName << "'." << endl;
        return false;
    }

    cout << "Loaded " << coursesLoaded << " courses from '" << fileName << "'." << endl;
    return true;
}

// printCourseListTree(courseTree)
// Prints all courses in alphanumeric order using in-order traversal.
void printCourseListTree(const CourseBST& courseTree) {
    if (courseTree.isEmpty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    cout << "Here is a sample schedule:" << endl;
    courseTree.inOrderTraversal();
}

// printCourseInformation(courseTree)
// Prompts the user, looks up a course, and prints course title and prerequisites.
void printCourseInformation(const CourseBST& courseTree) {
    cout << "What course do you want to know about? ";
    string input;
    cin >> input;

    // Converts user input to uppercase to match stored course numbers
    string courseNumber = toUpper(input);

    const Course* course = courseTree.search(courseNumber);
    if (course == nullptr) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    // Print course number and title
    cout << course->courseNumber << ", " << course->title << endl;

    // If no prereq is found prints "None"
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            if (i > 0) {
                cout << ", ";
            }
            // Print just the prereq course numbers
            cout << course->prerequisites[i];
        }
        cout << endl;
    }
}

//Main program 

int main() {

    // Default file name for course data
    const string defaultFile = "CS 300 ABCU_Advising_Program_Input.csv";

    CourseBST courseTree;      // BST that stores all the course information
    bool loadedData = false;  // Boolean to check if data is loaded

    cout << "Welcome to the course planner." << endl;

    int choice = 0;

    // Menu loop, continues until user chooses 9
    while (choice != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            // Handles non-numeric input for menu choice
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from the menu." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            // ignores all remaining characters up to and including the newline character
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the name of the data file (press Enter for default): ";
            string fileName;
            getline(cin, fileName);

            fileName = trim(fileName);
            if (fileName.empty()) {
                fileName = defaultFile;
            }

            // Load the course data into the BST and update loadedData
            loadedData = loadCoursesIntoTree(fileName, courseTree);
            break;
        }

        case 2:
            if (!loadedData) {
                cout << "Please load the data structure first." << endl;
            }
            else {
                printCourseListTree(courseTree);
            }
            break;

        case 3:
            if (!loadedData) {
                cout << "Please load the data structure first." << endl;
            }
            else {
                printCourseInformation(courseTree);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            // If user choice is not 1, 2, 3, or 9
            cout << choice << " is not a valid option." << endl;
            break;
        }

        if (choice != 9) {
            cout << endl; // blank line for readability between menus
        }
    }

    return 0;
}
