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
endif

ifeq "$(MAKECMDGOALS)" "client"
TARGET	:= $(TARGET_CLIENT)
SOURCES := $(filter-out $(SERVER_SRC),$(shell find $(SRC_DIR) -name '*.cpp'))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES:%.cpp=%.o))
endif

.PHONY: server
server: $(BUILD_DIR)/$(TARGET)

.PHONY: client
client: $(BUILD_DIR)/$(TARGET)

# link
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@
	@echo ' '
	@echo 'Program build successfully!'

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)
# compile and generate dependency info
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) -I$(dir $<) $^ -o $(BUILD_DIR)/$*.o
	$(CXX) -MM $(CXXFLAGS) $^ > $(BUILD_DIR)/$*.d
	@echo ' '

# set default command
.DEFAULT_GOAL := default

.PHONY: default
default: 
	@$(MAKE) client
	@$(MAKE) server
	@$(MAKE) unit

.PHONY: all
all: clean default
#all: docs

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

docs:
	@doxygen

###############################################################################
UNIT_TARTGET	:= unit
UNIT_SRC_DIR 	:= test
UNIT			:=  $(BUILD_DIR)/$(UNIT_TARTGET)

PROGRAMM_SOURCES := src/Client/ClientResponse.cpp \
					src/Server/ServerResponse.cpp \
					src/Message/Message.cpp \
					src/BaseResponse/BaseResponse.cpp \
					src/TaskList/TaskList.cpp		\
					src/Client/Client.cpp

UNIT_SOURCES := $(shell find $(UNIT_SRC_DIR) -name '*.cpp') $(PROGRAMM_SOURCES)
UNIT_OBJECTS := $(addprefix $(BUILD_DIR)/,$(UNIT_SOURCES:%.cpp=%.o))

.PHONY: inf
inf:
	$(info $(UNIT_SOURCES))
	$(info $(UNIT_OBJECTS))
	

CXXGTESTFLAGS = -g -L./gtest/lib -lgtest -lgtest_main -lpthread
INCS = -I./gtest/include

link: $(BUILD_DIR)/$(UNIT_TARTGET)
$(BUILD_DIR)/$(UNIT_TARTGET): $(UNIT_OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(INCS) -o $@ $(UNIT_OBJECTS) $(CXXGTESTFLAGS)
	@echo ' '
	@echo 'Unit tests build successfull!'
	
# pull in dependency info for *existing* .o files
-include $(UNIT_OBJECTS:.o=.d)
# compile and generate dependency info
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) -I$(dir $<) $^ -o $(BUILD_DIR)/$*.o $(INCS)
	$(CXX) -MM $(CXXFLAGS) $^ > $(BUILD_DIR)/$*.d $(INCS)
	@echo ' '

.PHONY: unit
unit: link
# unit: clean unit_compile $(UNIT)
