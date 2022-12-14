#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <fstream> 
#include <string>
#include <string>
#include <vector>
#include <list>

using namespace std;


//struct for housing each course object
struct Course {
    string course_id; // unique identifier
    string course_name;
    string course_prereq;
    string course_prereq_two;
    //initialize a base course object
    Course() {
        course_id = "000";
        course_prereq = "-1";
        course_prereq_two = "-1";
    }
};
//function to print out information for a course
void displayCourse(Course course){
    cout<< course.course_id << " : "<< course.course_name;
    if (course.course_prereq != "-1"){
        cout<<" | Prerequisites: "<< course.course_prereq;
    } 
    if(course.course_prereq_two != "-1"){
        cout<<" , "<< course.course_prereq_two;
    }
    cout<<endl;
}

//function to find and print out information for a given course 
void print_course(string coursenumber, bool prereq, vector<Course> vec){
    //create a course variable
    Course course;
    //search through the given vector for the course
    for(int i = 0; i < vec.size(); i++){
        if(coursenumber == vec[i].course_id){
            course = vec[i];
        }
    }
    //if it is not found, return
    if(course.course_id == "000"){
        cout<<"course not found"<<endl;
        return;
    }
    else{
        //if it is found print out info
        displayCourse(course);
        //if this is the first call we will print out any prerequisites
        if(prereq){
            if (course.course_prereq != "-1"){
                cout<<"\t";
                print_course(course.course_prereq, false, vec);
            }
            if (course.course_prereq_two != "-1"){
                cout<<"\t";
                print_course(course.course_prereq, false, vec);
            }
        }
    }
}

vector<Course> loadCourses(string fileName) {
    // Define a vector data structure to hold a collection of courses.
    vector<Course> courses;
    //this is the delimeter
    const char seperator = ',';
    //obejct to open the file
    ifstream inFS;
    string input, val;
    vector<string> curr_line;
    //try to open file
    inFS.open(fileName);
    //if it doesnt open, return
    if(inFS.fail()){
        cout<<"Invalid File Name"<<endl;
        return courses;
    }
    // loop to read rows of a file
    while (getline(inFS,input)) {
        stringstream streamData(input);
        //loop to read words of the row
        while(getline(streamData, val,seperator)){
            curr_line.push_back(val);
        }
        //based on how many words in the row we create the course
        Course course;
        if(curr_line.size() == 2){
            
            course.course_id = curr_line[0];
            course.course_name = curr_line[1];
        }
        
        if(curr_line.size() == 3){
            
            course.course_id = curr_line[0];
            course.course_name = curr_line[1];
            course.course_prereq = curr_line[2];
        }

        if(curr_line.size() == 4){
            
            course.course_id = curr_line[0];
            course.course_name = curr_line[1];
            course.course_prereq = curr_line[2];
            course.course_prereq_two = curr_line[3];
        }
        //add the course to an array
        courses.push_back(course);
        curr_line.clear();
    }
    //clsoe the file
    inFS.close();
    //return the array with the courses
    return courses;
}
//function to compare courses alphabetically
bool compare(Course first, Course second){
    return first.course_id < second.course_id;
}

//function to print out the menu
void printMenu(){
    cout<<"1. Load course data from a file"<<endl;
    cout<<"2. Print all courses in alphabetical order"<<endl;
    cout<<"3. Print a specific course"<<endl;
    cout<<"9. Exit"<<endl;
}

int main(){
    //initialize a vector of courses
    vector<Course> courses;

    //variables to keep track of user input
    int choice = 0;
    string filename;
    string course_search;

    //main loop
    while(choice != 9){
        printMenu();
        cin>>choice;
        if(cin.fail()){
            cout<<"invalid choice"<<endl;
            cin.ignore();
            cin.clear();
            choice = 0;
        }
        switch (choice)
        {
            case 1:
                cout<<"enter file name"<<endl;
                cin>>filename;
                courses = loadCourses(filename);
                if(courses.size() > 0){
                    cout<<"courses loaded successfully"<<endl;
                }
                for(int i = 0;i < courses.size();i++){
                    displayCourse(courses[i]);
                }
                break;
            
            case 2:
                //this will sort the courses alphanumerically by course ID
                //can be changed to sort by course name by changing the "compare" function
                sort(courses.begin(),courses.end(),compare);
                for(int i = 0;i < courses.size();i++){
                    displayCourse(courses[i]);
                }
                break;
            case 3:
                cout<<"which course would you like to see?"<<endl;
                cin>>course_search;
                if (cin.fail()){
                    cout<<"Invalid entry"<<endl;
                    cin.ignore();
                    cin.clear();
                    break;
                }
                print_course(course_search,true,courses);
                break;
            case 9:
                cout<<"goodbye!"<<endl;
                break;
            default:
                cout<<"invalid choice"<<endl;
                choice = 0;
                break;
            
        }


    }
    return 0;
    
}