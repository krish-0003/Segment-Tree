from binarytree import build
from tkinter import *
import tkinter.font as tkFont
import sys
from tkinter import Tk, Button, Frame, Label, StringVar, PhotoImage
from tkinter.scrolledtext import ScrolledText
import random

root = Tk()

root.geometry('1920x1080')


fontstyle = tkFont.Font(size=50)

n = 8
a = [0]*(n+1)
seg = [0]*(4*n+4)
isset = [0]*(4*n+4)
lazy = [0]*(4*n+4)


def propogate(l, r, id):
    l = int(l)
    r = int(r)
    id = int(id)
    if isset[id] == 1:
        seg[id] = (r - 1) * lazy[id]
    else:
        seg[id] += (r - 1) * lazy[id]
    if l + 1 != r:
        left = 2 * id + 1
        right = 2 * id + 2
        mid = (l + r) / 2
        if isset[id] == 1:
            lazy[left] = lazy[right] = lazy[id]
            isset[left] = isset[right] = 1
        else:
            lazy[left] += lazy[id]
            lazy[right] += lazy[id]
    lazy[id] = 0
    isset[id] = 0


def query(ql, qr, l=1, r=int(n) + 1, id=0):
    ql = int(ql)
    qr = int(qr)
    l = int(r)
    r = int(r)
    id = int(id)
    propogate(l, r, id)
    if (ql >= r or l >= qr):
        return 0
    if (ql <= l and r <= qr):
        return seg[id]
    left = 2 * id + 1
    right = 2 * id + 2
    mid = (l + r) / 2
    l1 = query(ql, qr, l, mid, left)
    r1 = query(ql, qr, mid, r, right)
    return (l1 + r1)


def update(ql, qr, val, st, l=1, r=int(n) + 1, id=0):
    ql = int(ql)
    qr = int(qr)
    st = int(st)
    l = int(l)
    r = int(r)
    id = int(id)
    propogate(l, r, id)
    if (ql >= r or l >= qr):
        return
    # assert (lazy[id] == 0)
    if (ql <= l and r <= qr):
        isset[id] = st
        lazy[id] = val
        propogate(l, r, id)
        return
    left = 2 * id + 1
    right = 2 * id + 2
    mid = (l + r) / 2
    update(ql, qr, val, st, l, mid, left)
    update(ql, qr, val, st, mid, r, right)
    seg[id] = (seg[left] + seg[right])


def build(l=1, r=int(n) + 1, id=0):
    l = int(l)
    r = int(r)
    id = int(id)
    if (l + 1 == r):
        seg[id] = a[l]
        return
    left = 2 * id + 1
    right = 2 * id + 2
    mid = (l + r) / 2
    build(l, mid, left)
    build(mid, r, right)
    seg[id] = (seg[left] + seg[right])
    return


def printnode(id, l, r, space):
    s = ""
    s += str(" " * int(space))
    s += str("[" + str(l) + "," + str(r) + ")-" + str(seg[id]) + "," + str(isset[id]) + "," + str(lazy[id]) + "")
    s += str(" " * space)
    return s


def display():
    s1 = ""
    print( "Node is : [l,r)-seg,isset,lazy")
    s1 += "\n\n\n"
    s1 += str(printnode(0, 1, 9, 65 * 3))
    s1 += "\n\n\n\n"
    s1 += str(printnode(1, 1, 5, 28 * 3))
    s1 += str(printnode(2, 5, 9, 28 * 3))
    s1 += "\n\n\n\n\n"
    s1 += "          "
    s1 += str(printnode(3, 1, 3, 10 * 3))
    s1 += str(printnode(4, 3, 5, 10 * 3))
    s1 += str(printnode(5, 5, 7, 10 * 3))
    s1 += str(printnode(6, 7, 9, 10 * 3))
    s1 += "\n\n\n\n\n\n"
    s1 += "                 "
    i = int(10)
    s1 += str(printnode(7, 1, 2, i))
    s1 += str(printnode(8, 2, 3, i))
    s1 += str(printnode(9, 3, 4, i))
    s1 += str(printnode(10, 4, 5, i))
    s1 += str(printnode(11, 5, 6, i))
    s1 += str(printnode(12, 6, 7, i))
    s1 += str(printnode(13, 7, 8, i))
    s1 += str(printnode(14, 8, 9, i))
    s1 += "\n\n\n\n\n"
    return s1

a1 = []

def my_process3():
    ss = display()
    a1.clear()
    var1.set(str(ss))


def my_process4():
    a1 = (entry1.get().split(" "))
    a2 = (entry2.get().split(" "))
    update(int(a1[0]), int(a1[1]), int(a2[0]), 0)
    ss = display()
    var1.set(str(ss))


def my_process5():
    a1 = (entry3.get().split(" "))
    a2 = (entry4.get().split(" "))
    update(int(a1[0]), int(a1[1]), int(a2[0]), 1)
    ss = display()
    var1.set(str(ss))


var1 = StringVar()

# for i in range(1, n + 1):
#     a[i] = random.randint(1, 15)
#     print(a[i])



def input_to_list():
    a1 = (entry.get().split(" "))
    print(a1)
    input_to_array(a1)

def input_to_array(a1):
    q= 1
    for x in a1:
        # print(i)
        a[q] = int(x)
        q = q + 1
        # print(a[i+1])
    for e in range(0, n+1):
        # print(a[e])
        build()



# display();

# display();
labelfont = ('ariel', 56, 'bold')
ll = Label(root, text='Segment Tree For Rangesum values(19BCE064, 19BCE072, 19BCE074)', font=("Trajan Pro", 16), justify=CENTER)
ll.place(relx=0.5, rely=0.05, anchor=CENTER)

entry = Entry(root)
entry.insert(0, "1 2 3 4 5 6 7 8")
button = Button(root, text="Enter Array elements", command=input_to_list)
entry.pack(pady=(100,10))
button.pack(pady=(0,20))
b3 = Button(root, text='Print Segment Tree(Full)', command=my_process3)
b3.pack(pady=(0,20))

entry1 = Entry(root)
entry1.insert(0, "1 5")
entry2 = Entry(root)
entry2.insert(0, "15")
b4 = Button(root, text='+x in range in Print Segment Tree(Full)', command=my_process4)
entry1.pack(pady=(0,10))
entry2.pack(pady=(0,10))
b4.pack(pady=(0,20))
entry3 = Entry(root)
entry3.insert(0, "1 7")
entry4 = Entry(root)
entry4.insert(0, "8")
b5 = Button(root, text='set value x in Print Segment Tree(Full)', command=my_process5)
entry3.pack(pady=(0,10))
entry4.pack(pady=(0,10))
b5.pack(pady=(0,20))
l1 = Label(root, textvariable=var1)
l1.pack()
root.mainloop()
