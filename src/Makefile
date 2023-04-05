.PHONY: all install uninstall clean dvi dist tests

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17 -lgtest -lgtest_main --coverage
OS = $(shell uname -s)
PROJECT_NAME = SmartCalc
APP = app
BUILD = build
REPORT = report
DOCUMENTATION = documentation
DIST = dist

all: install gcov_report

install:
	@echo "Installing start..."
	@mkdir -p ../$(BUILD)
	@cmake -B ../$(BUILD)
	@cd ../$(BUILD) && make
	@mkdir -p ../app
ifeq ($(OS), Darwin)
	@mv ../$(BUILD)/$(PROJECT_NAME).app ../$(APP)
else
	@mv ../$(BUILD)/$(PROJECT_NAME) ../$(APP)
endif
	@rm -rf ../$(BUILD)
	@echo "Installing success"

tests:
	@echo "Tests start..."
	@$(CXX) models/*.cc tests.cc -o test $(CXX_FLAGS)
	@./test
	@echo "Tests done"

gcov_report: tests
	@echo "Make report..."
	@mkdir -p ../$(REPORT)
	@-mv *.gc* models
	@lcov -t ./test -o ../$(REPORT)/test.info --no-external -c -d models
	@genhtml -o ../$(REPORT)/report_html ../$(REPORT)/test.info
	@echo "Report is complete"

uninstall:
	@echo "Uninstalling start..."
	@rm -rf ../$(APP)
	@echo "Uninstalling success"

dvi:
	doxygen Doxyfile

dist: clean
	@mkdir -p ../$(DIST)
	tar cvzf ../$(DIST)/source_code.tar.gz .

style:
	@clang-format -n -style=google $(shell find . \( -name "*.cc" -or -name "*.h" \))

clean:
	@echo "Cleaning..."
	@rm -rf ../$(REPORT) *.gc* models/*.gc* test ../$(BUILD) ../$(DIST) logs ../$(DOCUMENTATION)
	@echo "Clean is done"
