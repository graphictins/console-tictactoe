# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Ilib

# Sources and output
SRC = main.cpp
OUT = main


# additional flag $(CXXFLAGS)
# Build rule
$(OUT): $(SRC)
	$(CXX) $(SRC) -o $(OUT)


# Clean rule
# didnt really use
clean:
	del /q $(OUT) 2>nul || true
