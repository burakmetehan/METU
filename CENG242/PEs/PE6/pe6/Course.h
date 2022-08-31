#ifndef __COURSE_H__
#define __COURSE_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student;

enum Grade {
	AA = 100,
	BA = 85,
	BB = 80,
	CB = 75,
	CC = 70,
	DC = 65,
	DD = 60,
	FF = 1,
	NA = 0
};

class Course {

private:

	string name;
	vector<const Course *> prerequisites;

protected:

	Course() {}

	/* Setter */
	void set_name(string name) { this-> name = name; }

	void set_prerequisites(vector<const Course *> courses) { this->prerequisites = courses; }

public:

	/* Do NOT change the below part. */

	Course(string);
	~Course();
	Course(const Course&);

	void addPrerequisite(const Course&);
	const vector<const Course*> getPrerequisites() const;
	string getName() const;
	bool operator== (const Course&) const;

};


class OpenCourse : public Course {

private:

	string term;
	int course_index, quota;

	static vector<int> reg_stu_ids;
	static vector< vector<Student *> > registered_students;

protected:
	
	OpenCourse() {}

	// OpenCourse(const OpenCourse& opencourse, Student& student)

	/* Setters */
	void set_term(string term) { this->term = term; }
	void set_course_index(int index) { this->course_index = index; }
	void set_quota(int quota) { this->quota = quota; }

	/* Getters */
	string get_term() const { return this->term; }
	int get_course_index() const { return this->course_index; }
	int get_quota() const { return this->quota; }

	/* Other Methods */

	void add_student(Student& student) { 
		registered_students[get_course_index()].push_back(&student);
	}

	vector<Student *>& get_students() const { return registered_students[course_index]; }


public:

	/* Do NOT change the below part. */

	OpenCourse(const Course&, string, int, int);
	~OpenCourse();
	OpenCourse(const OpenCourse&);
	const vector<int> showStudentList() const;
	void finalize();

};


class CourseInstance : public OpenCourse {

private:

	Student* student;
	Grade grade;

protected:

public:

	/* Do NOT change the below part. */

	CourseInstance(const OpenCourse&, Student&);
	~CourseInstance();
	void setGrade(enum Grade);
	enum Grade getGrade() const;

};

#endif
