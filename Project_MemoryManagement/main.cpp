#include "Heap.h"
#include "Student.h"
#include "LectureNode.h"
#include "Lecture.h"
#include "LectureNodeTypeDescriptor.h"
#include "LectureTypeDescriptor.h"
#include "StudentTypeDescriptor.h"

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
}

int main()
{
	InitHeapAndRegTypeDescriptors();

	Heap::dump();

	auto student =  (Student*)Heap::alloc("Student");
	auto student2 = (Student*)Heap::alloc("Student");

	
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

	Heap::dump();

	student2->Add(l1);

	Heap::dump();

	student2->Add(l3);

	Heap::dump();

	std::vector<GObject*> roots;
	roots.push_back(student);
	roots.push_back(student2);

	Heap::gc(roots);

	Heap::dump();

	student->Remove(l1);
	Heap::gc(roots);

	Heap::dump();

	student2->Remove(l1);
	Heap::gc(roots);

	Heap::dump();
	roots.clear();



	Heap::gc(roots);
	Heap::dump();

	std::cin.get();
}