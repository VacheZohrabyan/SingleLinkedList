CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address
Target = main
SRCS = SingleLinkedListMain.cpp SingleLinkedList.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(Target)

$(Target): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(Target) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(Target)
	./$(Target)

clean:
	rm -f $(Target) $(OBJS)
