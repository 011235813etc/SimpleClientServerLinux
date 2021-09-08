# SimpleClientServerLinux

# Simple client-server Linux application.

This program use client-server architecture for executing bash scripts 
to different computers.

This program I am using for learning client-server exchange by TCP/IP.

For check classes behavior I am using GoogleTest.

## Client application.

The client application is used for:
- setting several command to server.
- starting server for send commands to clients.
- executing commands from server.

See more Client/main.cpp

## Server application.

The server application is used for:
- getting several command from client.
- send commands to clients by queue.

See more Server/main.cpp


## Build Systems

- GNU make

## About build.

For build all project and unit-tests you can use **make all** command.
For build unit-tests you need to have gtest library in current directory.

For generate Doxygen documentation (html) you can use **make docs** command. 
But you need have been installed doxygen in your computer.

## About demo. 
In this program a first client load tasks numbers to server. 
All tasks are described in task_list.txt
The tasks are bash-scripts which launch simple cpp-program and passing them a string with some information. 
After the loading is complete, first client send readiness command to server.
Then server are starting to send task number for client. 
A first client application get the task number. 
Then he find task number in task list and execute it. 
After that he send message to server with execution complete status. 
It will be until all tasks are completed.
After that second client send readiness command to server and execute all tasks like first client.

For launch demo program in Demo SimpleClientServerLinux working directory run a command:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
make all
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Then in Demo working directory run a command:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
./launch.sh
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
