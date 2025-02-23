//****************************************************************
// Name        : CS-300 Project Two								 *
// Author      : Joseph Roberts									 *
// Version     : 1.0											 *
// Description : This program is to load data for .CSV file		 *
//				 Print a list of courses in alphabetical order,  *
//				 along with a specific course with prerequisites *
//****************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// Define the structure for storing course information
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Function to load courses from a CSV file into the hash table
void loadCourses(const std::string& filename, std::unordered_map<std::string, Course>& courseTable) {
    std::ifstream file("CS 300 ABCU_Advising_Program_Input.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string courseNumber, courseTitle, prereq;
        std::getline(ss, courseNumber, ',');
        std::getline(ss, courseTitle, ',');

        Course course = { courseNumber, courseTitle, {} };

        while (std::getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courseTable[courseNumber] = course;
    }
}

// Function to display the menu options
void displayMenu() {
    std::cout << "Menu Options:\n";
    std::cout << "1. Load data\n";
    std::cout << "2. Print all courses\n";
    std::cout << "3. Print course details\n";
    std::cout << "9. Exit\n";
}

// Function to load data into the hash table
void loadData(std::unordered_map<std::string, Course>& courseTable) {
    std::string filename = "CS300_ABCU_Advising_Program_Input.csv";
    loadCourses(filename, courseTable);
    std::cout << "Data loaded successfully!\n";
}

// Function to print all courses in alphanumeric order
void printAllCourses(const std::unordered_map<std::string, Course>& courseTable) {
    std::vector<std::string> courseNumbers;

    for (const auto& entry : courseTable) {
        courseNumbers.push_back(entry.first);
    }

    std::sort(courseNumbers.begin(), courseNumbers.end());

    std::cout << "Course List:\n";
    for (const auto& courseNumber : courseNumbers) {
        std::cout << courseNumber << ": " << courseTable.at(courseNumber).courseTitle << "\n";
    }
}

// Function to print course details based on the course number
void printCourseDetails(const std::unordered_map<std::string, Course>& courseTable) {
    std::string courseNumber;
    std::cout << "Enter the course number: ";
    std::cin >> courseNumber;

    auto it = courseTable.find(courseNumber);
    if (it != courseTable.end()) {
        const Course& course = it->second;
        std::cout << course.courseNumber << ": " << course.courseTitle << "\n";
        std::cout << "Prerequisites: ";
        for (const auto& prereq : course.prerequisites) {
            std::cout << prereq << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Course not found.\n";
    }
}

// Main function to drive the program
int main() {
    std::unordered_map<std::string, Course> courseTable;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            loadData(courseTable);
            break;
        case 2:
            printAllCourses(courseTable);
            break;
        case 3:
            printCourseDetails(courseTable);
            break;
        case 9:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
