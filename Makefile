CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCS = main.cpp caesar/caesar.cpp playfair/playfair.cpp transposisi_kolom/transposisi_kolom.cpp gabungan/gabungan.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = crypto

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
