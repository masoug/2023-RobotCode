#Sample program to plog logged data

import sys
from datalog import load_datalog
import matplotlib.pyplot as plt
import tkinter as tk
from tkinter import *

#get name of log file
name = "robotlog.log" #default
if len(sys.argv) > 1:
    name = (sys.argv)[1]

log = load_datalog("../../../datalogs/" + name)
fields = log.data.keys()
to_plot = []

#Select which fields to plot
willPlot = []
selW = tk.Tk()
selW.title("Select Fields to Plot")

def plot():
    for i in range(len(fields)):
        if (willPlot[i].get()):
            plt.plot(log.time, log.data[list(fields)[i]])
    plt.xlabel("Time")
    plt.ylabel("Value")
    plt.show()

for i in range(len(fields)):
    b = BooleanVar()
    willPlot.append(b)
    Checkbutton(selW, text=list(fields)[i], variable=b, height=2, width=20).grid(row = i, sticky=W)
Button(selW, text="Plot", command=plot).grid(row = len(fields), sticky=W)

selW.mainloop()