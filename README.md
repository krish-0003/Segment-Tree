# Segment-Tree

When there are many updates and updates are done on a range, we can postpone some updates (avoid recursive calls in update) and do those updates only when required.
A node in segment tree stores or represents result of a query for a range of indexes. And if this node’s range lies within the update operation range, then all descendants of the node must also be updated.


We have done this Project Using Cpp and Python (For GUI representation in Tkinter)



https://user-images.githubusercontent.com/71602041/166803216-806f83f5-7abc-45c6-b621-bb6753dece8f.mp4



1. Using C++
    1. SegTreeSum.cpp
    2. SegTreeMin.cpp
    3. SegTreePolinomialQuery.cpp




2. Using Python and Tkinter Library
    1. treemin.py 
    2. rangesum.py 

## Operation

In Range Updation and Query, we have used Lazy Propogation, which will give us a time complexity of O(logn).
![image](https://user-images.githubusercontent.com/71602041/166803426-cabcfe2f-fea0-4b02-a0aa-b02cdab45919.png)


### In both segment tree (Min and Sum) :: 
* Rage Updation by Specific value
* Range Updation by Incrementing value
* Range Updation by Arithmetic Prgression

## dependencies:
Tkinter

