#!/bin/bash
gnome-terminal --window --title="server" 	-- bash -ic "./../build/server_app 30; 								sleep 200"
gnome-terminal --window --title="client_1" 	-- bash -ic "./../build/client_app ./tasks/task_list.txt loader; 	sleep 200"
gnome-terminal --window --title="client_2" 	-- bash -ic "./../build/client_app ./tasks/task_list.txt; 			sleep 200"
