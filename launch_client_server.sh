#!/bin/bash
gnome-terminal --window --title="server" \
                -- bash -ic "cd build; ./server_app; sleep 200"
gnome-terminal --window --title="client_1" \
                -- bash -ic "cd build; ./client_app ./tasks/task_list.txt; sleep 200"
gnome-terminal --window --title="client_2" \
                -- bash -ic "cd build; ./client_app; sleep 200"
