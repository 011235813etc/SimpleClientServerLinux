TARGET		:= program
SOURCE 		:= main.cpp
OBJECTS		:= main.o

CXX 		:= g++
CXXFLAGS	:= -Wall -fexceptions -g -std=c++11


.PHONY: default
default: clean link

link: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@
	@rm -f $(OBJECTS)
	@echo 'Program build successfully!'

$(OBJECTS): $(SOURCE)
	$(CXX) -c $(CXXFLAGS) $^ -o $*.o

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)


#TARGET		:= task
#SOURCE 		:= main.cpp
#OBJECTS		:= main.o
#BUILD_DIR	:= build
#
#CXX 		:= g++
#CXXFLAGS	:= -Wall -fexceptions -g -std=c++11
#
#
#.PHONY: default
#default: clean create link
#
#create: 
#	@mkdir -p $(BUILD_DIR)
#	@echo > $(SOURCE)
#	@echo "#include <iostream>" 												>> $(SOURCE)
#	@echo "" 																	>> $(SOURCE)
#	@echo "int main(int argc, const char* argv[]) {" 							>> $(SOURCE)
#	@echo "" 																	>> $(SOURCE)
#	@echo "	std::cout << \"task # \" << argv[1] << std::endl << std::endl;" 	>> $(SOURCE)
#	@echo "" 																	>> $(SOURCE)
#	@echo "}" 																	>> $(SOURCE)
#
#link: $(BUILD_DIR)/$(TARGET)
#$(BUILD_DIR)/$(TARGET): $(OBJECTS)
#	$(CXX) $(OBJECTS) -o $@
#	@rm -f $(OBJECTS)
#	@echo 'Program build successfully!'
#
#$(OBJECTS): $(SOURCE)
#	$(CXX) -c $(CXXFLAGS) $^ -o $*.o
#
#.PHONY: clean
#clean:
#	@rm -rf $(BUILD_DIR)
#
