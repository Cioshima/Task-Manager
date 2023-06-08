#include <iostream>
#include <string>
using namespace std;

// define a struct to represent a task
struct Task {
    string description;
    int priority;
    Task* next;

    ~Task() { //Composition Relationship
        cout << "Task \"" << description << "\" destroyed." << endl;
    }


};



// define a class to represent the task manager
class TaskManager {
public:
    TaskManager() {
        head = NULL;
    }

    ~TaskManager() { //Composition Relationship
        Task* current = head;
        while (current != NULL) {
            Task* next = current->next;
            delete current;
            current = next;
        }
        cout << "TaskManager destroyed." << endl;
    }

    // method to add a new task to the linked list
    void addTask(string description, int priority) {
        Task* newTask = new Task;
        newTask->description = description;
        newTask->priority = priority;
        newTask->next = nullptr;

        // Insert the new task into the linked list based on priority.
        // The list is already sorted, so we only need to check the head
        // and the first task whose priority is lower than the new task.
        if (head == nullptr || priority > head->priority) {
            newTask->next = head;
            head = newTask;
        }
        else {
            Task* current = head;
            while (current->next != nullptr && priority <= current->next->priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
    }

    Task* findTask(string description) {
        Task* current = head;
        while (current != NULL) {
            if (current->description == description) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }


    // method to display all tasks in order of priority
    void displayTasks() {
        Task* current = head;
        while (current != NULL) {
            cout << current->description << " (priority: " << current->priority << ")" << endl;
            current = current->next;
        }
    }

    void sortTasks() {
        if (head == nullptr || head->next == nullptr) {
            // List is empty or has only one element, so it's already sorted
            return;
        }

        Task* i, * j, * min;
        for (i = head; i->next != nullptr; i = i->next) {
            min = i;
            for (j = i->next; j != nullptr; j = j->next) {
                if (j->priority < min->priority) {
                    min = j;
                }
            }
            if (min != i) {
                // Swap the two tasks
                Task temp = *i;
                i->description = min->description;
                i->priority = min->priority;
                min->description = temp.description;
                min->priority = temp.priority;
            }
        }
    }


    void deleteTask(string description) {
        Task* current = head;
        Task* prev = nullptr;

        while (current != nullptr && current->description != description) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Task \"" << description << "\" not found." << endl;
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }

        cout << "Task \"" << current->description << "\" with priority " << current->priority << " deleted." << endl;
        delete current;
    }
private:
    Task* head;
};

// function to display a simple command-line interface

void displayCommandLineUI() {
    TaskManager taskManager;

    cout << "Welcome to the task manager!" << endl;

    while (true) {
        cout << endl << "What would you like to do?" << endl;
        cout << "1. Add a task" << endl;
        cout << "2. Display all tasks" << endl;
        cout << "3. Search for a task" << endl;
        cout << "4. Delete a task" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;


        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            string description;
            int priority = 0;

            cout << "Enter task description: ";
            getline(cin >> ws, description);

            cout << "Enter task priority (1-10, 10 being the highest priority): ";

            bool valid_input = false;
            while (!valid_input) {
                cout << "Enter task priority (1-10, 1 being the highest priority): ";
                if (cin >> priority) {
                    if (priority >= 1 && priority <= 10) {
                        valid_input = true;
                    }
                    else {
                        cout << "Invalid priority. Please enter a number between 1 and 10." << endl;
                    }
                }
                else {
                    cout << "Invalid input. Please enter a number between 1 and 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }


            //clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');


            taskManager.addTask(description, priority);
            cout << "Task added successfully." << endl;
            break;
        }
        case 2: {
            cout << "Tasks:" << endl;
            taskManager.sortTasks();
            taskManager.displayTasks();
            break;
        }

        case 3: {
            string description;
            cout << "Enter task description to search for: ";
            getline(cin >> ws, description);
            Task* foundTask = taskManager.findTask(description);
            if (foundTask != NULL) {
                cout << "Found task \"" << foundTask->description << "\" with priority " << foundTask->priority << "." << endl;
            }
            else {
                cout << "Task \"" << description << "\" not found." << endl;
            }
            break;
        }

        case 4: {
            string description;
            cout << "Enter task description to delete: ";
            getline(cin >> ws, description);
            taskManager.deleteTask(description);
            break;
        }

        case 5: {
            cout << "Exiting task manager." << endl;
            return;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
}





// example usage of the task manager with a command-line interface
int main() {
    displayCommandLineUI();
    return 0;
}
