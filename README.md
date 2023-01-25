
# Advenced_Exercises - UNIX only
This repo used for Advenced computing exercise 4
In this exercise we had to make KNN algorithm using cpp. KNN in a primitive ML algorithm that get as an input Data that seperate into 2 main parts: features and labels. Based on the features we want to make a prediction for a label for a new sample of data. The way KNN works is by calculating a distance function between the new sample to all the data in the training set. the label of the most fluent sampels with the smallest distance will be the prediction label of the new sample.
In this exercise we implemented a server side client side method therefore the user reach the client side and insert an input. This input is convey to the server side there the caclculation has been made and after it the result is transfering to the client side and the client side show this input to the user.
Furthermore you continued to implement a threading method for enabling access for multiple clients in a paralel way. For each client we fetched a menu and the client can chose the options formt he menu in order the upload and download data for the server to classify:

![image](https://user-images.githubusercontent.com/91119719/214695067-6fe8b3bc-e4f8-404a-9050-a905e9215fb7.png)

In this Excercise we have to make an implementation for 5 types of distances: 
1. Euclidain Distance
2. Manheten Distance
3. Chebyshev Distance
4. Canberra Distance
5. Minkowski Distance

When you run the file you wil face an empty line for input there you will have the insert your vector input.
The insertation of the vector should be with spaces between the numbers like the following example:

The our that you will get is the class out by the KNN model

# IMPORTANT CLARIFICATION:
1. The path for the file must be correct - otherwise you will get a new message for upload the correct path
2. You have to choose numeric value for K and correct distance function for the metric (AUC, MAN, CHB, MIN, CAN) if not, you will get second message to upload the correct params.
3. The run of the program for the client side should be from the client.out for the user (using the client side)
4. The run of the program for the server side should be from the server.out for the server
5. You have to finish previous steps in order to proceed. If not, the instructions message will pop up for that
6. If the menu shows up you will have to choose option from (1 2 3 4 5 8) otherwise, a message will show up for inserting a new input
7. You can stop this program by insert 8 as input
8. In order that communication tunnel will be crate the port must be the same (otherwise no output will show up - you need to enforce it youself because there is no limitations due to network routing and capabillities)

# COMPILING AND RUNNING COMMANDS:
In this repo there is a makefile for compiling the program. The instruction for run this program are:
1. run the command: <code>make</code> on your terminal
2. use ls to see that indeed <code>server.out</code>, <code>client.out</code> files were created
3. run <code>./server.out \<port> </code> in order to run <code>server.out</code> file in the designated terminal resource
4. run <code>./client.out \<port> </code> in order to run <code>client.out</code> file in the designated terminal resource
5. K = Notice K must be a number between 1 - 100 (Can be double but know that double double will be rounded - better to use int)
6. Data file must be only fro this group = {iris_classified.csv, wine_Classified.csv, beans_Classified.csv} - Other input will now accept
7. Distance function will be from the group = {AUC, MAN, CHB, CAN, MIN} - Other input will not accept

