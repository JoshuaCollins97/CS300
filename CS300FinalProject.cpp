#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Course structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Function to load courses from file into a map
void loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, title, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, title, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.title = title;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseNumber] = course;
    }

    file.close();
    cout << "Courses successfully loaded from file." << endl;
}

// Function to print all courses in alphanumeric order
void printAllCourses(const map<string, Course>& courses) {
    vector<string> sortedCourses;
    for (const auto& entry : courses) {
        sortedCourses.push_back(entry.first);
    }

    sort(sortedCourses.begin(), sortedCourses.end());

    for (const auto& courseNumber : sortedCourses) {
        const auto& course = courses.at(courseNumber);
        cout << course.courseNumber << ": " << course.title << endl;
    }
}

// Function to print specific course details
void printCourseDetails(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Error: Course not found." << endl;
        return;
    }

    const auto& course = it->second;
    cout << course.courseNumber << ": " << course.title << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "No prerequisites." << endl;
    }
}

// Main menu function
void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1. Load Course Data" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Details" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    map<string, Course> courses;
    int choice;
    string filename;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            cin >> filename;
            loadCourses(filename, courses);
            break;
        case 2:
            if (courses.empty()) {
                cout << "No courses loaded. Please load the data first." << endl;
            }
            else {
                printAllCourses(courses);
            }
            break;
        case 3: {
            if (courses.empty()) {
                cout << "No courses loaded. Please load the data first." << endl;
            }
            else {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;
                printCourseDetails(courses, courseNumber);
            }
            break;
        }
        case 9:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 9);

    return 0;
}
