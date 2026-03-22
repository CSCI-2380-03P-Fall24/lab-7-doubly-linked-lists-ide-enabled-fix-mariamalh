	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList(): head(nullptr), tail(nullptr), numStudents(0){}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* newNode = new Node(s, head, nullptr);
		if (head != nullptr){
			head-> prev = newNode;
		}
		else{
			tail = newNode;
		}
		head = newNode;
		++numStudents;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* newNode = new Node(s, nullptr, tail);
		if (tail != nullptr){
			tail-> next = newNode;
		}
		else{
			head = newNode;
		}
		tail = newNode;
		++numStudents;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node* current = head;
		while(current != nullptr){
			std::cout << current-> data.name << " ";
			current = current-> next;
		}
		std::cout << endl;
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (tail == nullptr){
			std::cout << "Cannot pop list is empty." << endl;
		}
		else{
			Node* temp = tail;
			tail = tail-> prev;
			if (tail != nullptr){
				tail-> next = nullptr;
			}
			else{
				head = nullptr;
			}
			delete temp;
			--numStudents;
		}
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if (head == nullptr){
			std::cout << "Cannot pop list is empty." << endl;
		}
		else{
			Node* temp = head;
			head = head-> next;
			if (head != nullptr){
				head-> prev = nullptr;
			}
			else{
				tail = nullptr;
			}
			delete temp;
			--numStudents;
		}
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if (index <= 0){
			addFront(s);
		}
		else if (index >= numStudents){
			std::cout << "Index is out of range. Adding to the back of the list." << endl;
			addBack(s);
		}
		else{
			Node* current = head;
			for(int i = 0; i < index; ++i){
				current = current-> next;
			}
			Node* newNode = new Node(s, current, current-> prev);
			current->prev-> next = newNode;
			current->prev = newNode;
			++numStudents;
		}
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Node* current = head;
		while (current != nullptr){
			if (current-> data.id == idNum){
				return current-> data;
			}
			current = current-> next;
		}
		std::cout << "Student ID not found." << endl;
		return Student();

	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		Node* current = head;
		while (current != nullptr){
			if (current-> data.id == idNum){
				if (current == head){
					popFront();
				}
				else if (current == tail){
					popBack();
				}
				else{
					current->prev-> next = current-> next;
					current->next-> prev = current-> prev;
					delete current;
					--numStudents;
				}
				return;
			}
			current = current-> next;
		}
		std::cout << "Student ID not found." << endl;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node* current = head;
		while (current != nullptr){
			if (current-> data.id == idNum){
				current-> data.GPA = newGPA;
				return;
			}
			current = current-> next;
		}
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if (otherList.head == nullptr){
			return;
		}
		if (head == nullptr){
			head = otherList.head;
			tail = otherList.tail;
		}
		else{
			tail->next = otherList.head;
			otherList.head->prev = tail;
			tail = otherList.tail;
		}
		numStudents += otherList.numStudents;
		otherList.numStudents = 0;
		otherList.head = nullptr;
		otherList.tail = nullptr;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		Node* current = head;
		StudentList list;
		while (current != nullptr){
			if (current-> data.GPA >= minGPA){
				list.addBack(current-> data);
			}
			current = current-> next;
		}
		return list;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if (head == nullptr){
			std::cout << "The list is empty." << endl;
			return;
		}
		Node* current = head;
		while (current != nullptr){
			Node* next = current-> next;
			if (current-> data.GPA < threshold){
				removeStudentById(current-> data.id);
			}
			current = next;
		}
	}
