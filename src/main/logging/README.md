# Robot data logging

## C++ DataLogger Class
Contained in the `main` folder, this class contains functionality for recording the value of set "data fields" over time and pushing those recorded values to a log file on the roborio.

## Python utils
The `datalog.py` file contains functionality to process the raw log file into a numpy array that associates each data field with its value over time.

The `plotter.py` file graphically plots the data in a raw log file, whose name can be passed in as a command line argument (for example, to plot `robotlog.log`, type `python plotter.py robotlog.log`.