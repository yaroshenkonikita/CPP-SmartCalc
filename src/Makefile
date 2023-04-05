.PHONY: all install uninstall clean dvi dist tests

all: install gcov_report

install:
	@echo "Installing start..."
	@mkdir -p ../build
	@cmake -B ../build
	@cd ../build && make
	@mkdir -p ../app
	@-mv ../build/SmartCalc ../build/SmartCalc.app
	@mv ../build/SmartCalc.app ../app
	@rm -rf ../build
	@echo "Installing success"

tests:
	@echo "Tests start..."
	@g++ models/*.cc tests.cc -o test -lgtest -lgtest_main --coverage
	@./test
	@echo "Tests done"

gcov_report: tests
	@echo "Make report..."
	@mkdir -p ../report
	@-mv *.gc* models
	@lcov -t ./test -o ../report/test.info --no-external -c -d models
	@genhtml -o ../report/report_html ../report/test.info
	@echo "Report is complete"

uninstall:
	@echo "Uninstalling start..."
	@rm -rf ../app
	@echo "Uninstalling success"

dist: clean
	@mkdir -p ../dist
	tar cvzf ../dist/source_code.tar.gz .

style:
	@clang-format -n -style=google $(shell find . \( -name "*.cc" -or -name "*.h" \))

clean:
	@echo "Cleaning..."
	@rm -rf ../report *.gc* models/*.gc* test ../build ../dist logs
	@echo "Clean is done"