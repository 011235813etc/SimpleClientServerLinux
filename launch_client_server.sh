#!/bin/bash
gnome-terminal --window -- bash -ic "cd build; ./Server_app; sleep 20"
gnome-terminal --window -- bash -ic "cd build; ./Client_app; sleep 20"
