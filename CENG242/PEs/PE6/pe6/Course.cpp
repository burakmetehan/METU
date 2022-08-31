#include "Student.h"
#include "Course.h"

vector< vector<Student *> > OpenCourse::registered_students;

Course::Course(string name) {
	this->name = name;
}

Course::~Course() {}

/* Shallow Copy */
Course::Course(const Course& course) {
   this->name = course.getName();
   this->prerequisites = course.getPrerequisites();
}

void Course::addPrerequisite(const Course& course) {
	this->prerequisites.push_back(&course);
}

/* @returns the prerequisites of the course. */
const vector<const Course*> Course::getPrerequisites() const {
   return this->prerequisites;
}

/* @returns the name of the course. */
string Course::getName() const {
	return this->name;
}

/* @returns true if the two courses have the same name, false otherwise.
*/
bool Course::operator== (const Course& rhs) const {
	return this->name == rhs.getName();
}

 
/* 
Initiliaze the following from arguments
* @param term
* @param course_index the index of the course in the array of OpenCourses at Metu.
* @param quota the upper limit for the number of students who takes the course.
*/
OpenCourse::OpenCourse(const Course& course, string term, int course_index, int quota) : Course(course) {
	this->term = term;
   this->course_index = course_index;
   this->quota = quota;

   registered_students.push_back(vector<Student *>());
}

OpenCourse::~OpenCourse() {
}

/* Shallow Copy. */
OpenCourse::OpenCourse(const OpenCourse& opencourse) {
   this->set_name(opencourse.getName());

   for (auto &x : this->getPrerequisites()) {
      this->addPrerequisite(*x);
   }
   
   this->term = opencourse.get_term();
   this->course_index = opencourse.get_course_index();
   this->quota = opencourse.get_quota();

   registered_students.push_back(vector<Student *>());
}

/* 
@returns the ids of the students who take the current OpenCourse.
*/
const vector<int> OpenCourse::showStudentList() const {
   vector<int> ret_vec;

   for (auto &student : this->get_students())
   {
      ret_vec.push_back(student->getId());
   }

   return ret_vec;
}

/* 
This method calls the gradeCourse() method to grade the current OpenCourse for each student who take the course.
*/
void OpenCourse::finalize() {
   for (auto &student : this->get_students())
   {
      student->gradeCourse(*this);
   }
}


/* 
Initiliaze the following from arguments
* @param term
* @param course_index the index of the course in the array of OpenCourses at Metu.
* @param quota the upper limit for the number of students who takes the course.

This method initializes the grade corresponding to this CourseInstance to Grade::NA.
*/
CourseInstance::CourseInstance(const OpenCourse& opencourse, Student& student) : OpenCourse(opencourse) {
   this->student = &student;
   this->grade = NA;

   OpenCourse::add_student(student);
}

CourseInstance::~CourseInstance() {
	// TODO
}

/* This method saves the given grade value into the corresponding class member */
void CourseInstance::setGrade(enum Grade grade) {
	this->grade = grade;
}

/* This method returns the grade of the CourseInstance. */
enum Grade CourseInstance::getGrade() const {
	return this->grade;
}
