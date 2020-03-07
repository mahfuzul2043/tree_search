# tree_search
 
```
Description: This program demonstrates the relationship between classes that use inheritance and multiple inheritance in programming. For example,
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
```