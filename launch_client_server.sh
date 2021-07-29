#!/bin/bash
gnome-terminal --window -- bash -ic "cd build; ./server_app; sleep 200"
gnome-terminal --window -- bash -ic "cd build; ./client_app 0; sleep 200"
gnome-terminal --window -- bash -ic "cd build; ./client_app; sleep 200"
