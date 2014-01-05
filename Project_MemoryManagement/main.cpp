#include "Heap.h"
#include "Student.h"
#include "LectureNode.h"
#include "Lecture.h"
#include "LectureNodeTypeDescriptor.h"
#include "LectureTypeDescriptor.h"
#include "StudentTypeDescriptor.h"
#include "StudentList.h"
#include "StudentListTypeDescriptor.h"
#include "StudentNodeTypeDescriptor.h"

#include <iostream>


void InitHeapAndRegTypeDescriptors()
{
	Heap::initHeap();

	auto lNodeTd = new LectureNodeTypeDescriptor();
	Heap::registerType(lNodeTd->GetClassName(), lNodeTd);

	auto lTd = new LectureTypeDescriptor();
	Heap::registerType(lTd->GetClassName(), lTd);

	auto sTd = new StudentTypeDescriptor();
	Heap::registerType(sTd->GetClassName(), sTd);

	auto sNtd = new StudentNodeTypeDescriptor();
	Heap::registerType(sNtd->GetClassName(), sNtd);

	auto sLtd = new StudentListTypeDescriptor();
	Heap::registerType(sLtd->GetClassName(), sLtd);
}

int main()
{
	InitHeapAndRegTypeDescriptors();
	std::vector<GObject*> roots;

	cout << "Initial state:" << endl;
	Heap::dump();


	cout << "Create the objects:" << endl;

	cout << "Creating object graph:" << endl;

	auto studentList = (StudentList*) Heap::alloc("StudentList");

	auto student =  (Student*)Heap::alloc("Student");
	auto student2 = (Student*)Heap::alloc("Student");
	auto student3 = (Student*) Heap::alloc("Student");

	studentList->Add(student);
	studentList->Add(student2);
	studentList->Add(student3);

	auto l1 = (Lecture*)Heap::alloc("Lecture");
	l1->SetId(1);
	l1->SetName("System Software");
	l1->SetSemester(2);
	student->Add(l1);

	auto l2 = (Lecture*)Heap::alloc("Lecture");
	l2->SetId(2);
	l2->SetName("Principals of Programming Languanges");
	l2->SetSemester(2);
	student->Add(l2);

	auto l3 = (Lecture*)Heap::alloc("Lecture");
	l3->SetId(3);
	l3->SetName("HCI");
	l3->SetSemester(2);
	student->Add(l3);	

	student2->Add(l1);
	student2->Add(l3);

	student3->Add(l2);
	student3->Add(l3);

	Heap::dump();

	cout << "Call GC the first time (without removing anything)" << endl;
	roots.push_back(studentList);
	Heap::gc(roots);
	Heap::dump();

	cout << "Remove first lecture from student1 and call GC" << endl;

	student->Remove(l1);
	Heap::gc(roots);

	Heap::dump();

	cout << "Remove first lecture from student 2 and call GC. After this point l1 is removed" << endl;

	student2->Remove(l1);
	Heap::gc(roots);

	Heap::dump();
	
	cout << "Remove student1" << endl;

	studentList->Remove(student);
	Heap::gc(roots);
	Heap::dump();



	cout << "Remove the list from the roots" << endl;
	roots.clear();
	

	Heap::gc(roots);
	Heap::dump();

	std::cin.get();
}