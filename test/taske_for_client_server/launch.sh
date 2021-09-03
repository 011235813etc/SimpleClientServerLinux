#!/bin/bash
gnome-terminal --window --title="server" \
                -- bash -ic "cd build; ./server_app; sleep 200"
gnome-terminal --window --title="client_1" \
                -- bash -ic "cd build; ./client_app loader; sleep 200"
