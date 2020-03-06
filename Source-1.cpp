//Creator: Haque, Mahfuzul
//Date: 2/19/2018

/*Description: This program demonstrates the relationship between classes that use inheritance and multiple inheritance in programming. For example,
a class Date can extend Time, and a class Appointment can extend Date. This is an example of inheritance; Date inherits the member functions and data members
of Time, and Appointment inherits the member functions and data members of both Time AND Appointment. A good example of multiple inheritance would be say, 
a class Circle. It can inherit member functions and data members from a class Shape AND Point, where Point and Shape are not related, but Circle is related
to both Shape and Point. In this case, Shape and Point are both base classes, and they are both extended by Circle. This program functions to determine these
relationships and illustrate them in the form of a tree.

When launching the application, you will be presented with a blank console. On the first line, you are to enter the number of inheritance relationships you want
to input. After entering this number, for every line, you will proceed to enter pairs of relationships in the form "SubClass, BaseClass". The following is a sample input:

4
Kid Parent
Parent Grandparent
Grandparent GreatGrandparent
Kid Parent2

The sample input above will yield the following output by the program. Note that Kid inherits both Parent and Parent2 (multiple inheritance), and Parent inherits from
Grandparent, who inherits from GreatGrandparent (inheritance/transitive inheritance):

GreatGrandparent
     Grandparent
          Parent
               Kid
----------
Parent2
     Kid
----------

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
	Node(string label) : name(label) { }
	Node* find(string toFind) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i]->getName() == toFind) {        //for each node in the children vector, check if its name matches toFind. If so, return it. if not, return nullptr
				return children[i];
			}
		}
		return nullptr;
	}

	void print(int numSpaces, Node* ptr) {
		for (int i = 0; i < ptr->children.size(); i++) {
			for (int y = 0; y < numSpaces; y++) {          //print numSpaces amount of spaces before printing name (multiples of 5 spaces)
				cout << " ";
			}
			cout << ptr->children[i]->getName() << endl;
			if (ptr->children.size() != 0) {
				print(numSpaces + 5, ptr->children[i]);   //if parent node has children, and the children of the parent have children (etc.), then recursively call print so it can iterate through all children down to the last level of the tree.
			}											  //For each recursive call, append 5 spaces to demonstrate the inheritance relationship
		}
	}

	void addChild(Node* childPtr) {   
		childPtr->extends.push_back(this);  //when adding a child, make sure its extends vector points to the current object, which is the parent
		children.push_back(childPtr);		//make sure the children vector of the current object (the parent) points to the new childPtr
	}
	string getName() {
		return name;
	}
	friend class Program; //allow program class to access private variables
private:
	string name;
	vector<Node*> children;
	vector<Node*> extends;
};

class Program {
public:
	/* This find function will check the forest level-by-level. First it will check level 0 and level 1(the parents and children of parents), then it will set the children of parents as the new parents and check levels 2 and 3, then levels 4 and 5, etc. until it finds a matching node OR until it reaches a level in which the number of nodes = 0 */
	Node* find(string toFind) { 
		vector<Node*> inner;                                                
		vector<Node*> toSearch = classes;                                  //initialize the search with the root
		while (toSearch.size() != 0) {									   //break when the loop reaches a level in which the number of nodes = 0
			inner.clear();												   //clear inner vector so it can append and check the new children
			for (int i = 0; i < toSearch.size(); i++) {
				if (toSearch[i]->getName() == toFind) {                    //if toSearch vector contains a node that matches toFind, return the node
					return classes[i];
				}
				else if (toSearch[i]->find(toFind) != nullptr) {           //if the children of a node from the toSearch vector matches toFind, then return it
					return toSearch[i]->find(toFind);
				}
				for (int y = 0; y < toSearch[i]->children.size(); y++) {   //else append ALL children nodes (whose children has a size > 0) to a vector to check in proceeding iteration
					if (toSearch[i]->children[y]->children.size() != 0) {  //if children of the base node does not contain any children, then do not append because it does not need to be checked. It was already checked in line 56
						inner.push_back(toSearch[i]->children[y]);
					}
				}
			}
			toSearch = inner;											  //set toSearch to the inner vector. This makes it so that the children of the root are now the new base. This will continue until the toSearch vector has size 0
		}
		return nullptr;
	}
	void print() {
		for (int i = 0; i < classes.size(); i++) {
			cout << classes[i]->getName() << endl;   //for each root node, print the name
			classes[i]->print(5, classes[i]);		 //for each root node, execute its print function
			cout << "----------" << endl;			 //after each root node is displayed all the way down to its last child, separate with dashes
		}
	}
	void add(string subClass, string base) {
		Node* basePtr = find(base);
		Node* subPtr = find(subClass);
		if (basePtr == nullptr && subPtr == nullptr) {   //if neither a basePtr nor subPtr exists, then make new nodes for each and append basePtr to root
			basePtr = new Node(base);
			subPtr = new Node(subClass);
			basePtr->addChild(subPtr);
			classes.push_back(basePtr);
		}
		else if (basePtr != nullptr && subPtr == nullptr) {    //if basePtr is found, but subPtr is not, then simply add subPtr to basePtr
			subPtr = new Node(subClass);
			basePtr->addChild(subPtr);
		}
		else if (basePtr == nullptr && subPtr != nullptr) {
			basePtr = new Node(base);
			basePtr->addChild(subPtr);
			int index = nodeIndex(classes, subPtr); //check if subPtr exists in the root. 
			if (index != -1) {                      //if subPtr exists in root, replace with basePtr because subPtr is now a child of basePtr
				classes[index] = basePtr;
			}else{                                  //else append basePtr to root vector because subPtr does not exist in root, but it's still a child of another node (multiple inheritance)
				classes.push_back(basePtr); 
			}
		}
		else if(basePtr != nullptr && subPtr != nullptr) {    //if both a basePtr and a subPtr have been found, simply add subPtr to basePtr
			basePtr->addChild(subPtr);
			int index = nodeIndex(classes, subPtr);
			if (index != -1) {
				classes.erase(classes.begin() + index);      //if subPtr exists as a root, then delete it because it is now the child of another node (inheritance)
			}
		}
	}
private:
	int nodeIndex(vector<Node*> nodelist, Node* node) { //get index of a root node
		for (int i = 0; i < nodelist.size(); i++) {
			if (node == nodelist[i]) {
				return i;
			}
		}
		return -1;
	}
	vector<Node*> classes;
};

int main() {
	Program program;
	string name1, name2;
	int numPairs;

	cin >> numPairs;
	for (int i = 0; i < numPairs; i++)
	{
		cin >> name1 >> name2;
		program.add(name1, name2);
	}
	program.print();
	return 0;
}