NAME= polyset
CXX = c++

CXXFLAGS = -std=c++98 -O3 -I. -I./include
LDFLAGS = -lm
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)	
all: $(NAME)
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(NAME)
.PHONY: all clean