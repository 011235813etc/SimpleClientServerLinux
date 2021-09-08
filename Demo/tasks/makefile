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
