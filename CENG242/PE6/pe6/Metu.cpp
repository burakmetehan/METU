#include "Metu.h"

Metu::Metu() {
   classroom = nullptr;
   classroom_size = {0, 0};
}

Metu::~Metu() {
	for (auto &student : this->students)
   {
      delete student;     
   }

   for (auto &course : this->courses)
   {
      delete course;
   }

   for (auto &course : this->open_courses)
   {
      delete course;
   }

   for (int i = 0; i < classroom_size.first; i++)
      delete[] classroom[i];
   delete[] classroom;
   classroom = nullptr;
}

/*
@returns the student whose id is given in the argument.
*/
Student& Metu::getStudent(int id) {
   for(auto &student : students)
   {
      if (student->getId() == id) 
         return *student;
   }

   /* Not Found */
   Student* student = new Student(-1, "", "");
   return *student;
}

void Metu::registerStudent(Student* student) {
	this->students.push_back(student);
}

void Metu::registerCourse(const Course& course) {
	this->courses.push_back(&course);
}

/* 
/* 
Initiliaze the following from arguments
* @param course
* @param term
* @param quota
* @param department

Also, for each student given in the corresponding lists as function arguments, the newly created OpenCourse is tried to be added in order. Note that 
   * the priority order is given from greater to less as follows: Seniors > Juniors > Sophomores > Freshmans.
   * After the priority ordering, you should try to add the course for each student of the same type in the order inside the corresponding list.
   *  Also, during the course addition, you should take the course quota in consider.
   * In the end, there may be left the students who could not add the course because of the quota or the course prerequisite. Finally, you should return the created OpenCourse object.
*/
OpenCourse& Metu::openCourse(const Course& course, string term, int quota, vector<Freshman*> freshmans, vector<Sophomore*> sophomores, vector<Junior*> juniors, vector<Senior*> seniors) {
   // @TODO
   OpenCourse* new_course = new OpenCourse(course, term, open_courses.size(), quota);
   
   // auto prerequisites = course.getPrerequisites();

   for (auto &student : seniors)
   {
      if(!quota)
         break;

      if (student->addCourse(*new_course))
         quota--;
      else;
   }

   for (auto &student : juniors)
   {
      if(!quota)
         break;

      if (student->addCourse(*new_course))
         quota--;
      else;
   }

   for (auto &student : sophomores)
   {
      if(!quota)
         break;

      if (student->addCourse(*new_course))
         quota--;
      else;
   }

   for (auto &student : freshmans)
   {
      if(!quota)
         break;

      if (student->addCourse(*new_course))
      {
         quota--;
      }
      else;
   }

   open_courses.push_back(new_course);
   return *new_course;
}

/* 
This method upgrades the given Freshman object to the Sophomore status by constructing a new Sophomore object with the properties of the given Freshman. 

Delete the given Freshman and place the newly created Sophomore object to its location in the students array of Metu object. In the end, you should return the created Sophomore.
*/
Sophomore* Metu::upgradeStudent(Freshman& student) {
   Sophomore* new_sophomore = new Sophomore(student);
   new_sophomore->setUpgradeStatus();

   /* Finding place of student */
   vector<Student *>::iterator it = find_student(student);

   if (it != this->students.end()) // student is found
   {
      delete (*it);
      *it = new_sophomore;
   }
   else // student not found, so needs to add the list
   {
      this->students.push_back(new_sophomore);
   }
   
   return new_sophomore;
}

/*
This method upgrades the given Sophomore object to the Junior status by constructing a new Junior object with the properties of the given Sophomore. 

Delete the given Sophomore and place the newly created Junior object to its location in the students array of Metu object. In the end, you should return the created Junior.
*/
Junior* Metu::upgradeStudent(Sophomore& student) {
	Junior* new_juniour = new Junior(student);
   new_juniour->setUpgradeStatus();

   /* Finding place of student */
   vector<Student *>::iterator it = find_student(student);

   if (it != this->students.end()) // student is found
   {
      delete (*it);
      *it = new_juniour;
   }
   else // student not found, so needs to add the list
   {
      this->students.push_back(new_juniour);
   }
   
   return new_juniour;
}

/* 
This method upgrades the given Junior object to the Senior status by constructing a new Senior object with the properties of the given Junior. 

Delete the given Junior and place the newly created Senior object to its location in the students array of Metu object. In the end, you should return the created Senior.
*/
Senior* Metu::upgradeStudent(Junior& student) {
	Senior* new_senior = new Senior(student);
   new_senior->setUpgradeStatus();

   /* Finding place of student */
   vector<Student *>::iterator it = find_student(student);

   if (it != this->students.end()) // student is found
   {
      delete (*it);
      *it = new_senior;
   }
   else // student not found, so needs to add the list
   {
      this->students.push_back(new_senior);
   }
   
   return new_senior;
}

/* This method sets the number of rows and number of columns in a standard Metu classroom with the given arguments, respectively.
*/
void Metu::setClassroomSize(int row_size, int column_size) {
	this->classroom_size = {row_size, column_size};
}

/* 
This method tries to construct the 2D seating plan by using the given information as function argument one-by-one. The information consists of 2 integers and 1 string argument.
   * The string parameter can be either "|" or "-".
      *  If it is "|", then it means location of the student whose id given in the first argument is <row_id, column_id> whereas location of the student whose id given in the second argument is <row_id + 1, column_id>.
      * If it is "-", then it means location of the student whose id given in the first argument is <row_id, column_id> whereas location of the student whose id given in the second argument is <row_id, column_id + 1>.
*/
void Metu::addCheatInfo(int from_student_id, int to_student_id, string dir) {
   int stu_1 = find_student_index(i_students, from_student_id);
   int stu_2 = find_student_index(i_students, to_student_id);

   int size = i_students.size();

   if (stu_1 == -1 && stu_2 == -1) // both not found
   {
      if (dir == "-")
      {
         // order is matter
         i_students.push_back(input_student(from_student_id, -1, size+1, -1, -1));
         i_students.push_back(input_student(to_student_id, size, -1, -1, -1));
      }
      else
      {
         // order is matter
         i_students.push_back(input_student(from_student_id, -1, -1, -1, size+1));
         i_students.push_back(input_student(to_student_id, -1, -1, size, -1));
      }
   }
   else if (stu_1 == -1 && stu_2 != -1) // stu_2 found
   {
      if (dir == "-")
      {
         i_students.push_back(input_student(from_student_id, -1, stu_2, -1, -1));
         i_students[stu_2].left = size;
      }
      else
      {
         i_students.push_back(input_student(from_student_id, -1, -1, -1, stu_2));
         i_students[stu_2].top = size;
      }      
   }
   else if (stu_1 != -1 && stu_2 == -1) // stu_1 found
   {
      if (dir == "-")
      {
         i_students[stu_1].right = size;
         i_students.push_back(input_student(to_student_id, stu_1, -1, -1, -1));
      }
      else
      {
         i_students[stu_1].bottom = size;
         i_students.push_back(input_student(to_student_id, -1, -1, stu_1, -1));
      }
   }
   else // bot found
   {
      if (dir == "-")
      {
         i_students[stu_1].right = stu_2;
         i_students[stu_2].left = stu_1;
      }
      else
      {
         i_students[stu_1].bottom = stu_2;
         i_students[stu_2].top = stu_1;
      }
   }
}

/* 
This method prints the given seating plan, in other words the 2D array. Between each seat, print an empty space, i.e. " " character. Also, put an empty space to the end of each row. After each row (including the last one), print a new line, i.e. "\n" character.

For the empty seats, print a "X" character (uppercase). For non-empty seats, print the id of the student sitting there.
*/
void Metu::printSeatingPlan() {
   if (i_students.size() == 0) // No student
   {
      for (int i = 0; i < classroom_size.first; i++)
      {
         for (int j = 0; j < classroom_size.second; j++)
            cout << "X" << " ";
         cout << endl;
      }
   }
   
   i_student temp = i_students[0];

   create_sp_students(i_students[0], 0, 0, sp_students);

   pair<sp_student, pair<int, int>> minimums = find_minimums(sp_students);

   for (auto &stu : sp_students)
   {
      stu.row -= minimums.second.first;
      stu.column -= minimums.second.second;
   }

   classroom = new int*[classroom_size.first];
   for (int i = 0; i < classroom_size.first; i++)
   {
      classroom[i] = new int[classroom_size.second];
      for (int j = 0; j < classroom_size.second; j++)
      {
         classroom[i][j] = -1;
      }
   }

   for ( auto &stu : sp_students)
   {
      classroom[stu.row][stu.column] = stu.id;
   }

   for (int i = 0; i < classroom_size.first; i++)
   {
      for (int j = 0; j < classroom_size.second; j++)
      {
         if (classroom[i][j] == -1)
            cout << "X" << " ";
         else
            cout << classroom[i][j] << " ";
      }
      cout << endl;
   }
}
