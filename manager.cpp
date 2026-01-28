//Section1 - Section1 main purpose is to set up the standard libaries needed for input/output, dynamic storage, text manipulation, and file operations
//This allows input and output via std::cin and std::count
#include <iostream>
//Provides the std::vector container to store a dynamic lis of tasks
#include <vector>
//This provides std::string for task names
#include <string>
//This provides file handling for reading/writing tasks
#include <fstream>

//section2 -  The main purpose of section 2 is to encapsulate all data and behavior for a single task making it easy to manipluate and organized.
//Define class named 
class Task {
//Specifies that the next variables are private -- using encapsulation, keeping internal data safe
private:
//Declares a privare variable called name and stores the task description
    std::string name;
//Declares a private boolean calle completed and tracks whether the task is done or not not (true/false)
    bool completed;

//Public makes it so everything below can be accessed from outside this class -- allows other parts of the program to interact with a task safely
public:
//This is a constructor- it is a special function that runs automatically when a new task object is created.
//input for the task name
//input for whether task is complete
//Sets the private variables directly
    Task(const std::string& n, bool c = false) : name(n), completed(c) {}

//Is a public method that marks completed tasks/sets boolean to true 
    void markComplete() { completed = true; }
//This is a public method that will return the completeion status of the task
    bool isCompleted() const { return completed; }
//Returns the name of the task
    std::string getName() const { return name; }
};

// Section3 -- This section shows the menu and prints the options for the user to view
//Declares function but returns no value due to void
void showMenu() {
    std::cout << "\n====== To-Do List Manager ======\n";
    std::cout << "1. View Tasks\n";
    std::cout << "2. Add Task\n";
    std::cout << "3. Remove Task\n";
    std::cout << "4. Mark Task Complete\n";
    std::cout << "5. Exit\n";
    std::cout << "================================\n";
}

// Section4 -- Displays all tasks
//Declares function
//void -- no value returned
//list of Task objects
//function will not modify vector
void displayTasks(const std::vector<Task>& tasks) {
//checks if vector has no element and tasks.empty() returns true if vector size is 0
    if (tasks.empty()) {
//Prints message if no tasks are to be displayed
        std::cout << "There are no tasks to display.\n";
//Function is exited
        return;
    }

//starts a for loop
//starts a loop counter
//loop goes on until all tasks are processed
//increments the counter
    for (size_t i = 0; i < tasks.size(); i++) {
//prints task number -- list starts at 1 instead of 0
        std::cout << i + 1 << ". ["
//Prints "X" if task is completed/true and if not true prints blank space " "
                  << (tasks[i].isCompleted() ? "X" : " ")
//Calls the getName() function
                  << "] " << tasks[i].getName() << "\n";
    }
}

//Section5 -- Adds a new task
//Declares a function named addTask, is void so funtion returns nothing
void addTask(std::vector<Task>& tasks) {
//Prompts user for a task
    std::cout << "Enter task name: ";
//Declares string named taskName/store user's input
    std::string taskName;
//Reads an entire line of text from user/stores everything user types
    std::getline(std::cin, taskName);

//Adds a new Task object to end
    tasks.emplace_back(taskName);
//Prints a confirmation message
    std::cout << "Task was added successfully.\n";
}

//Section6 -- Removes a task
//Declares function named removeTask
void removeTask(std::vector<Task>& tasks) {
//Calls function, shows user the current tasks
    displayTasks(tasks);
//Checks to see if no tasks and exits if none
    if (tasks.empty()) return;

//Prompts user to select task to delete
    std::cout << "Enter task number to remove: ";
//Declares an integer variable -- store user's input
    int index;
//Read what user said -- stores it
    std::cin >> index;
//Discards leftover and prevents input issues
    std::cin.ignore();

//Validates user input -- ensures number is a valid option
    if (index < 1 || index > static_cast<int>(tasks.size())) {
//Display error if not valid input
        std::cout << "Invalid task number.\n";
//Exits function
        return;
    }

//Removes selected task
    tasks.erase(tasks.begin() + index - 1);
//Prints statement if task was removed 
    std::cout << "Task removed successfully.\n";
}

//Section7 -- Marks a task as complete
//Declares funtion named markTaskComplete
void markTaskComplete(std::vector<Task>& tasks) {
//Calls displayTasks to show the list of tasks
    displayTasks(tasks);
//Checks to see if there are no tasks -- if empty exits
    if (tasks.empty()) return;

//Prompts user to enter task that is complete
    std::cout << "Enter task number to mark as complete: ";
//Declared integer variable
    int index;
//Reads integer and stores value
    std::cin >> index;
//Removes leftover
    std::cin.ignore();

//Validates user input
    if (index < 1 || index > static_cast<int>(tasks.size())) {
//Prints message that input was invalid
        std::cout << "Invalid task number.\n";
//Exits function
        return;
    }

//Accesses the selected task
    tasks[index - 1].markComplete();
//Prints confirmation
    std::cout << "Task marked as complete.\n";
}

//Section8 -- Loads tasks from file
//Declares a function
void loadTasksFromFile(std::vector<Task>& tasks) {
//Creates an input file
    std::ifstream file("manager_tasks.txt"); // <-- updated filename

//Check if file opened
    if (!file.is_open()) {
//Prints message letting user know there is no saved task file
        std::cout << "No existing task file found. A new one will be created.\n";
//Exits
        return;
    }

//Stores whether task is done
    bool completed;
//Stores name
    std::string name;

//Reads a boolean value from the file
    while (file >> completed) {
//Skips leftover
        file.ignore();
//Reads rest of line and stores it in name
        std::getline(file, name);
//Creates new Task object and adds it to tasks
        tasks.emplace_back(name, completed);
    }

//Close the file
    file.close();
//Confirmation
    std::cout << "Tasks loaded from file.\n";
}

//Section9 -- Saves tasks to file
//Declares function
void saveTasksToFile(const std::vector<Task>& tasks) {
//Creates an output file stream, opens file and overwrites content
    std::ofstream file("manager_tasks.txt"); 

//Loops through every task
    for (const Task& task : tasks) {
//Writes task per line to file
        file << task.isCompleted() << " " << task.getName() << "\n";
    }

//Close file
    file.close();
//Save was succesful, lets user know
    std::cout << "Tasks saved to file.\n";
}

//Section10
//Program starts
int main() {
//Creates a task list
    std::vector<Task> tasks;
//Stores users's menu selection
    int choice = 0;

//Reads previously saved tasks from file
    loadTasksFromFile(tasks);

//Begins loop
    do {
//Displays menu and prints to screen
        showMenu();
//Prompts user for choice
        std::cout << "Enter your choice: ";
//Stores the input
        std::cin >> choice;
//clear newline
        std::cin.ignore();

//Next part is full of if, else if, else statments which is simply executing what the user choice was and preforms that specific action to what they chose.
        if (choice == 1) {
            displayTasks(tasks);
        } 
        else if (choice == 2) {
            addTask(tasks);
        } 
        else if (choice == 3) {
            removeTask(tasks);
        } 
        else if (choice == 4) {
            markTaskComplete(tasks);
        } 
        else if (choice == 5) {
            saveTasksToFile(tasks);
            std::cout << "Exiting program.\n";
        } 
        else {
            std::cout << "Invalid choice. Try again.\n";
        }

//Loop doesn't stop until option 5 is selected
    } while (choice != 5);

//Ends Program
    return 0;
}

//Note:
// Class is like a blueprint for creating objects (in this case it is used for things like createing taks in the to-do list)