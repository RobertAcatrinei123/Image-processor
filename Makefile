CXX = clang++
CXXFLAGS = -std=c++20 -Wall -g -I include -fprofile-instr-generate -fcoverage-mapping

TARGET = app
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -fprofile-instr-generate -fcoverage-mapping

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f src/*.o
	rm -f *.gcda *.gcno *.gcov *.profraw *.profdata *.info *.txt
	rm -f lcov.info coverage.txt coverage.profraw coverage.profdata

run_coverage: all
	LLVM_PROFILE_FILE="coverage.profraw" ./$(TARGET)

llvm_coverage_report: run_coverage
	/opt/homebrew/opt/llvm/bin/llvm-profdata merge -sparse coverage.profraw -o coverage.profdata
	/opt/homebrew/opt/llvm/bin/llvm-cov show ./$(TARGET) -instr-profile=coverage.profdata > coverage.txt

llvm_lcov: run_coverage
	/opt/homebrew/opt/llvm/bin/llvm-profdata merge -sparse coverage.profraw -o coverage.profdata
	/opt/homebrew/opt/llvm/bin/llvm-cov export --format=lcov ./$(TARGET) -instr-profile=coverage.profdata > lcov.info
	rm -f coverage.profraw
	rm -f coverage.profdata
	rm -f coverage.txt

leaks:
	leaks -atExit -- ./$(TARGET)

docs:
	doxygen Doxyfile
	firebase deploy

.PHONY: all clean obj run_coverage llvm_coverage_report llvm_lcov