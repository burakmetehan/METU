#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "Course.h"

enum Grade learnGrade(string course_name, int student_id);

class Student {

private:

	int id;
	float gpa;
	string name, department;
	bool upgrade_info;
		
	vector<CourseInstance> taken_courses;
	//vector<CourseInstance> take_courses;
	//vector<CourseInstance *> graded_courses;
	int graded_courses;

protected:

	Student() {} // Default Constructor that will not be used

	/* Setters */
	void set_id(int id) { this->id = id; }
	void set_gpa(float gpa) { this->gpa = gpa; }
	void set_name(string name) { this->name = name; }
	void set_department(string department) { this->department = department; }
	void set_upgrade_info(bool info) { this->upgrade_info = info; }
	void set_graded_courses(int x) { this->graded_courses = x; }

	void set_taken_courses(vector<CourseInstance> courses) { this->taken_courses = courses; }

	/* Getters */
	string get_name() const { return this->name; }
	string get_department() const { return this->department; }
	bool get_upgrade_info() const { return this->upgrade_info; }
	int get_graded_courses() const { return this->graded_courses; }

	vector<CourseInstance> get_taken_courses() const { return this->taken_courses; }

	/* Vector */
	void add_taken_course(CourseInstance course) { this->taken_courses.push_back(course); }
	//void add_graded_course(CourseInstance* course) { this->graded_courses.push_back(course); }

	/* Other Methods */
	/* @returns true if prerequisite is satisfied; otherwise, false */
	bool check_prerequisite(const Course* course, vector<const CourseInstance *>& taken_courses) const {
		for (auto &taken_course : taken_courses)
		{
			if (course->getName() == taken_course->getName())
			{
				return true;
			}
		}

		return false;
	}

public:

	/* Do NOT change the below part. */

	Student(int id, string fullname, string department);
	~Student();
	Student(const Student&);
	int getId() const;
	float getGPA() const;
	vector<const CourseInstance*> listCourses() const;
	void gradeCourse(const OpenCourse& openCourse);
	void setUpgradeStatus();

};


class Freshman : public Student {

private:

protected:

	Freshman() {}

public:

	/* Do NOT change the below part. */
	
	Freshman(int id, string fullname, string department);
	~Freshman();
	Freshman(const Freshman&);
	bool addCourse(const OpenCourse&);
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.

};


class Sophomore : public Freshman {

private:

	bool internship_1, internship_2;

protected:

	Sophomore() {}

	/* Setter */
	void set_interships(bool inter_1 = false, bool inter_2 = false) { 
		this->internship_1 = inter_1; 
		this->internship_2 = inter_2;
	}
	void set_inter_1(bool inter = false) { this->internship_1 = inter; }
	void set_inter_2(bool inter = false) { this->internship_2 = inter; }

	/* Getters */
	pair<bool, bool> get_interships() const { 
		return {this->internship_1, this->internship_2};
	}
	bool get_inter_1() const { return this->internship_1; }
	bool get_inter_2() const { return this->internship_2; }

public:

	/* Do NOT change the below part. */

	Sophomore(int id, string fullname, string department);
	Sophomore(const Freshman&);
	~Sophomore();
	Sophomore(const Sophomore&);
	void doAnInternship(int);
	bool getInternshipStatus(int);
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.
};



class Junior : public Sophomore {

private:

protected:

	Junior() {}

public:

	/* Do NOT change the below part. */
	
	Junior(int, string, string);
	Junior(const Sophomore&);
	~Junior();
	Junior(const Junior&);
	void selectElectiveCourse();
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.
};


class Senior : public Junior {

private:

protected:

	Senior() {}

public:

	/* Do NOT change the below part. */

	Senior(int, string, string);
	Senior(const Junior&);
	~Senior();
	Senior(const Senior&);
	bool graduate();
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.
};

#endif
