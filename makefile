TARGET_CLIENT	:= client_app
TARGET_SERVER	:= server_app

BUILD_DIR	:= build
SRC_DIR 	:= src

CXX 		:= g++
CXXFLAGS	:= -Wall -fexceptions -g -std=c++11

CLIENT_DIR := src/Client
CLIENT_SRC = $(shell find $(CLIENT_DIR) -name '*.cpp')

SERVER_DIR := src/Server
SERVER_SRC = $(shell find $(SERVER_DIR) -name '*.cpp')

ifeq "$(MAKECMDGOALS)" "server"
TARGET	:= $(TARGET_SERVER)
SOURCES := $(filter-out $(CLIENT_SRC),$(shell find $(SRC_DIR) -name '*.cpp'))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES:%.cpp=%.o))
$(info "exclude_client_folder")
$(info $(SOURCES))
$(info $(OBJECTS))
endif

ifeq "$(MAKECMDGOALS)" "client"
TARGET	:= $(TARGET_CLIENT)
SOURCES := $(filter-out $(SERVER_SRC),$(shell find $(SRC_DIR) -name '*.cpp'))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES:%.cpp=%.o))
$(info "exclude_server_folder")
$(info $(SOURCES))
$(info $(OBJECTS))
endif

.PHONY: server
server: $(BUILD_DIR)/$(TARGET)

.PHONY: client
client: $(BUILD_DIR)/$(TARGET)

# link
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(dir $@)
	$(info "linking!")
	$(info $(OBJECTS))
	$(info $(SOURCES))
	$(CXX) $(OBJECTS) -o $@

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)
# compile and generate dependency info
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(info "objects!")
	$(CXX) -c $(CXXFLAGS) -I$(dir $<) $^ -o $(BUILD_DIR)/$*.o
	$(CXX) -MM $(CXXFLAGS) $^ > $(BUILD_DIR)/$*.d

# set default command
.DEFAULT_GOAL := default

.PHONY: default
default: 
	$(MAKE) client
	$(MAKE) server

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
