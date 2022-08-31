#ifndef __METU_H__
#define __METU_H__


#include "Course.h"
#include "Student.h"

class Metu {

private:

	vector<Student *> students;
	vector<const Course *> courses;
	vector<OpenCourse *> open_courses;

	/* Non_related Competitive Part Variables */
	pair<int, int> classroom_size; // {row_size, column_size}
	int **classroom;

	typedef struct seating_plan_student
	{
		int id;
		int row;
		int column;

		seating_plan_student(int id, int row, int column)
		{
			this->id = id;
			this->row = row;
			this->column = column;
		}
	} sp_student;

	typedef struct input_student
	{
		int id, left, right, top, bottom;
		bool visited; // Show index inside vector

		input_student(int id = -1, int left = -1, int right = -1, int top = -1, int bottom = -1, bool visited = false)
		{
			this->id = id; this->left = left; this->right = right; this->top = top; this->bottom = bottom;
			this->visited = visited;
		}
	} i_student;
	

	vector<sp_student> sp_students;

	vector<i_student> i_students;

	/* @returns index if student id is matched, otherwise false */
	int find_student_index(vector<sp_student>& students, int id)
	{
		for (int i=0; i < students.size(); i++)
		{
			if (students[i].id == id)
				return i;
		}

		return -1;
	}

	int find_student_index(vector<i_student>& students, int id)
	{
		for (int i=0; i < students.size(); i++)
		{
			if (students[i].id == id)
				return i;
		}

		return -1;
	}

	bool is_student(vector<sp_student>& sp, int id)
	{
		for (auto &student : sp)
		{
			if (student.id == id)
				return true;
		}

		return false;
	}

	void create_sp_students(i_student& stu, int row, int column, vector<sp_student>& sp)
	{
		if (stu.visited)
			return;
		else;
		
		stu.visited = true;
		sp.push_back(seating_plan_student(stu.id, row, column));
		
		/* left visit */
		if (stu.left != -1) { create_sp_students(i_students[stu.left], row, column-1, sp); } else;

		/* right visit */
		if (stu.right != -1) { create_sp_students(i_students[stu.right], row, column+1,sp); } else;

		/* top visit */
		if (stu.top != -1) { create_sp_students(i_students[stu.top], row-1,column, sp); } else;

		/* bottom visit */
		if (stu.bottom != -1) { create_sp_students(i_students[stu.bottom], row+1, column, sp); } else;

		return;
	}

	/* min_row and min_column <= 0 */
	pair<sp_student, pair<int, int> > find_minimums(vector<sp_student>& sp)
	{
		sp_student first_student = sp[0];
		int min_row = first_student.row, min_column = first_student.column;

		for (int i = 1; i < sp.size(); i++)
		{
			sp_student comp_student = sp[i];

			/* Checking minimum student */
			if (comp_student.row < first_student.row)
				first_student = comp_student;
			else if (comp_student.row == first_student.row && comp_student.column < first_student.column)
				first_student = comp_student;
			else;

			/* Checking minimum coordinates */
			if (comp_student.row < min_row)
				min_row = comp_student.row;
			else;

			if (comp_student.column < min_column)
				min_column = comp_student.column;
			else;
		}

		return {first_student, {min_row, min_column}};
	}

	/* Additional Methods */
	vector<Student *>::iterator find_student(Student &student) {
		vector<Student *>::iterator it;

		for (it = this->students.begin(); it != this->students.end(); it++)
		{
			if ((*it)->getId() == student.getId())
			{
				return it;
			}
			else;
		}
		
		return it;
	}

	int find_index_of_student(Student &student)
	{
		for (int i = 0; i < students.size(); i++)
		{
			if (students[i]->getId() == student.getId())
				return i;
			else;
		}

		return -1;
	}
public:

	/* Do NOT change the below part. */

	Metu();
	~Metu();

	Student& getStudent(int);
	void registerStudent(Student*);
	void registerCourse(const Course&);
	OpenCourse& openCourse(const Course&, string, int, vector<Freshman*>, vector<Sophomore*>, vector<Junior*>, vector<Senior*>);

	Sophomore* upgradeStudent(Freshman&);
	Junior* upgradeStudent(Sophomore&);
	Senior* upgradeStudent(Junior&);

	void setClassroomSize(int, int);
	void addCheatInfo(int, int, string);
	void printSeatingPlan();

};

#endif
