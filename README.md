# AdvancedProgramming-1
Advanced Programming 1 project by Amit Hazan and Simon Fraiberg
to compile follow this simple steps:
1)download the project files by pressing in the main reposetory page on the arrow in the green button "code" then press download zip.
2)extract the zip to a folder.
3)open your terminal in the folder destination using dc command.
4)run the "make" command on the planet server to compile.
now you have the a.out file. you need run the file with 3 arguments:
1)the K for the KNN fucntion that indicates the number of neighbors in the function.
2)the file name of the database to run the KNN function on.
3)a string representation of the distance formula to use for calculating the distances in the KNN function.
the string representation of the formulas are as follows:
1)AUC - auclidian distance.
2)MAN - manhattan distance.
3)CHB - chebyshev distance.
4)CAN - canberra distance.
5)MIN - minkowski distance.

for example ,/a.out 5 wine_Classified.csv AUC will be ready to get vectors and check thier classification based on the KNN function with k=5 and the auclidian distance.

enter the the numbers of the vector with space between them then press enter
the classification based on the KNN function will print

you can input as much vectors as you would like.

if you want to change to a different k or different data base just stop the run of the program and start it with different arguments.

//info on the distance formulas//
the functions used the similarity of the Euclidean and Manhattan that are based on the Minkowski formula.
when p = 1 we get Euclidean distance and for p = 2 we get Manhattan distance so we have a general function to calculate the formula.
all of the 5 different distance function are in Distance class that has static functions for each distance method.
its a static method so it would not be necessary to make an Distance object to use them. just like the known math class.

##the minikowski function was calculated as p = 2 in the formula##
