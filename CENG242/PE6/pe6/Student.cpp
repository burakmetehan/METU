#include "Student.h"

/* 
Initiliaze the following from arguments
* @param id
* @param fullname
* @param department

Initiliaze the following
* @param gpa 0
* @param upgrade_info 0
*/
Student::Student(int _id, string _fullname, string _department) {
	this->id = _id;
   this->gpa = 0.0;
   this->name = _fullname;
   this->department = _department;
   this->upgrade_info = false;
   this->graded_courses = 0;
}

Student::~Student() {
	// for (auto &course : this->taken_courses)
   //    delete course;
   
   // for (auto &course : this->graded_courses)
   //    delete course;
}

/* Shallow Copy */
Student::Student(const Student& student) {
	this->id = student.getId();
	this->gpa = student.getGPA();
   this->name = student.get_name();
   this->department = student.get_department();
   this->upgrade_info = student.get_upgrade_info();
   this->graded_courses = student.get_graded_courses();

   this->taken_courses = student.get_taken_courses();
}

/* @returns the id of the student. */
int Student::getId() const {
	return this->id;
}

/* @returns the GPA of the student. */
float Student::getGPA() const {
	return this->gpa;
}

/* 
@returns the courses taken by this student. 

Note that the grade taken in that course is not important. You should return all the passed and failed courses.
*/
vector<const CourseInstance*> Student::listCourses() const {
	/* taken_courses is not constant, so new vector will be created and returned */
   vector<const CourseInstance*> ret_vec;
   for(auto &x : taken_courses) {
      ret_vec.push_back(&x);
   }
   return ret_vec;
}

/* 
Calls learnGrade(): learnGrade("Programming Languages", 1234567);

* Save the grade returned by learnGrade(). 
* Recalculate the GPA of the student in this method.

GPA: Float | average of all the graded courses (The courses for which gradeCourse() method is called before or now).
*/
void Student::gradeCourse(const OpenCourse& openCourse) {
	Grade grade = learnGrade(openCourse.getName(), this->id);
   int size = graded_courses++;
   
   this->gpa = (this->gpa * size + grade) / (size + 1);

   for (auto &course : this->taken_courses)
   {
      if (openCourse.getName() == course.getName())
      {
         course.setGrade(grade);
         break;
      }
   }

   // CourseInstance* new_course = new CourseInstance(openCourse, *this);
   // this->graded_courses.push_back(new_course);
}

void Student::setUpgradeStatus() {
	this->upgrade_info = true;
}


/**** Freshman ****/

/*
/* 
Initiliaze the following from arguments
* @param id
* @param fullname
* @param department

Initiliaze the following
* @param gpa 0
* @param upgrade_info 0
*/
Freshman::Freshman(int id, string fullname, string department) {
	this->set_id(id);
   this->set_gpa(0);
   this->set_name(fullname);
   this->set_department(department);
   this->set_upgrade_info(false);
   this->set_graded_courses(0);
}

Freshman::~Freshman() {}

/* Shallow Copy */
Freshman::Freshman(const Freshman& freshman) {
	this->set_id(freshman.getId());
   this->set_gpa(freshman.getGPA());
   this->set_name(freshman.get_name());
   this->set_department(freshman.get_department());
   this->set_upgrade_info(freshman.get_upgrade_info());
   this->set_graded_courses(freshman.get_graded_courses());

   this->set_taken_courses(freshman.get_taken_courses());
}

/* 
@returns true id course could be added successfuly; otherwise, false.
*/
bool Freshman::addCourse(const OpenCourse& opencourse) {
   bool flag = false;
   auto prerequisities = opencourse.getPrerequisites();

   if (prerequisities.size() == 0)
   {
      flag = true;
   }
   else
   {
      vector<const CourseInstance *> taken_courses = this->listCourses();
      for (auto &course: prerequisities)
      {
         /* Do not satisfy */
         if (! (this->check_prerequisite(course, taken_courses)))
         {
            flag = false;
            return flag;
         }
         else;

      }

      flag = true;
   }

   if (flag)
   {
      CourseInstance* new_course = new CourseInstance(opencourse, *this);
      this->add_taken_course(*new_course);
      delete new_course;
   }
   else;

   return flag;
}


/**** Sophomore ****/

/* 
/* 
Initiliaze the following from arguments
* @param id
* @param fullname
* @param department

Initiliaze the following
* @param gpa 0
* @param upgrade_info 0
* @param graded_courses 0
* @internship_1 false
* @internship_2 false
*/
Sophomore::Sophomore(int id, string fullname, string department) {
	this->set_id(id);
   this->set_gpa(0);
   this->set_name(fullname);
   this->set_department(department);
   this->set_interships();
   this->set_upgrade_info(false);
   this->set_graded_courses(0);
}

Sophomore::Sophomore(const Freshman& freshman) : Freshman(freshman) {
	this->set_interships();
}

Sophomore::~Sophomore() {}

/* Shallow Copy */
Sophomore::Sophomore(const Sophomore& sophomore) {
	this->set_id(sophomore.getId());
   this->set_gpa(sophomore.getGPA());
   this->set_name(sophomore.get_name());
   this->set_department(sophomore.get_department());
   this->set_upgrade_info(sophomore.get_upgrade_info());
   this->set_interships(sophomore.get_inter_1(), sophomore.get_inter_2());

   this->set_taken_courses(sophomore.get_taken_courses());
   

   this->set_graded_courses(sophomore.get_graded_courses());
}

/* 
This method grades the internship with the given id(1 or 2). In order to grade the internship, learnGrade() method is called. learnGrade() method is already implemented by the HW admin, yet it is invisible to you. You call it by giving the internship name as the first argument and student id as the second argument. For instance;
   learnGrade("INTERNSHIP-1", 1234567); or
	learnGrade("INTERNSHIP-2", 1234567);
If the grade returned by learnGrade() method is greater than or equal to DD, then restore the value of the corresponding internship variable as true, else leave it as false.
*/
void Sophomore::doAnInternship(int intership_no) {
   Grade grade;
	if (intership_no == 1)
   {
      grade = learnGrade("INTERNSHIP-1", this->getId());
      this->set_inter_1(grade >= DD);
   }
   else if (intership_no == 2)
   {
      grade = learnGrade("INTERNSHIP-2", this->getId());
      this->set_inter_2(grade >= DD);
   }
   else;
}

/*
@returns the status of given internship_no
*/
bool Sophomore::getInternshipStatus(int intership_no) {
	if (intership_no == 1)
      return this->get_inter_1();
   else if (intership_no == 2)
      return this->get_inter_2();
   else
      return false;
}


/**** Junior ****/
Junior::Junior(int id, string fullname, string department) {
	this->set_id(id);
   this->set_gpa(0);
   this->set_name(fullname);
   this->set_department(department);
   this->set_interships();
   this->set_upgrade_info(false);
   this->set_graded_courses(0);
}

Junior::Junior(const Sophomore& sophomore) : Sophomore(sophomore) {}

Junior::~Junior() {}

Junior::Junior(const Junior& junior) {
	this->set_id(junior.getId());
   this->set_gpa(junior.getGPA());
   this->set_name(junior.get_name());
   this->set_department(junior.get_department());
   this->set_upgrade_info(junior.get_upgrade_info());
   this->set_interships(junior.get_inter_1(), junior.get_inter_2());

   this->set_taken_courses(junior.get_taken_courses());
   this->set_graded_courses(junior.get_graded_courses());
}

void Junior::selectElectiveCourse() {}


/**** Senior ****/
Senior::Senior(int id, string fullname, string department) {
	this->set_id(id);
   this->set_gpa(100);
   this->set_name(fullname);
   this->set_department(department);
   this->set_interships();
   this->set_upgrade_info(false);
   this->set_graded_courses(0);
}

Senior::Senior(const Junior& junior) : Junior(junior) {}

Senior::~Senior() {}

Senior::Senior(const Senior& senior) {
	this->set_id(senior.getId());
   this->set_gpa(senior.getGPA());
   this->set_name(senior.get_name());
   this->set_department(senior.get_department());
   this->set_upgrade_info(senior.get_upgrade_info());
   this->set_interships(senior.get_inter_1(), senior.get_inter_2());

   this->set_taken_courses(senior.get_taken_courses());
   this->set_graded_courses(senior.get_graded_courses());
}

bool Senior::graduate() { return true; }
