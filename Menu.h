#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <sstream>
#include "LazyBST.h"

using namespace std;

class Menu {
  private:
    int counterStudent;
    int counterFaculty;
  public:
    BST<Student> masterStudent;
    BST<Faculty> masterFaculty;


    Menu();
    ~Menu();

    void writeFile();

    void printMS(TreeNode<Student> *s);
    void printMF(TreeNode<Faculty> *f);

    //This is where i can delete things
    void outputMS(TreeNode<Student> *s, string student);
    void outputMF(TreeNode<Faculty> *f, string faculty);
    void clearFile(string filename);
    void combineFiles(string studentFile, string facultyFile, string combinedFile);

    TreeNode<Student>* getMSRoot();
    TreeNode<Faculty>* getMFRoot();

    void printMenu();
    void printAllStudents();
    void printAllFaculty();
    void printStudent();
    void printFaculty();

    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisor();
    void removeAdvisee();


    void exit();
};
