red := \e[1;31;49m
blue := \e[1;34;49m
normal := \e[0;0;49m

Source := $(wildcard *.cpp)
Delete := $(wildcard ./Info/*)
DoxPdf := $(patsubst %.cpp,%.conf, $(Source))
Target := ./SOURCE/Project
LOCATION := ./Info/G_tools
CC_Flags := --coverage -g -pg 
GP_Flags := -p -q -A -T -y 
GC_Flag  := gcov $(Source) -m

all: clean info Project  

info:
	@echo "\n\t $(red) -*- $(blue)In this makefile you can use the folowing comands $(red)-*-$(blue) \
		   \n\t         $(red) -*- $(blue)writing $(red)make$(blue) and the $(red)comand$(blue) name $(red)-*-$(blue) \
		   \n \
		   \n\t $(red)Code_Coverage_Report$(blue) .....for branch and line coverage \
		   \n\t $(red)Profile$(blue) ..................for have a look the source code work \
		   \n\t $(red)Memory_leak$(blue) ..............to view memory usage \
		   \n\t $(red)html_pdf$(blue) .................for creating the html and pdf file \
		   \n\t $(red)debug$(blue) ....................for debuging current code $(normal)\
		   \n\n"

Project: $(Source)
	@ctags -R
	@mkdir ./Info
	@mkdir ./Info/G_tools
	@mkdir ./SOURCE
	@gcc $(CC_Flags) $(Source) -o $(Target) -O2 -lstdc++
	@$(Target)
	@$(GC_Flag)
	@find -name '*.gcno' -exec mv -t $(LOCATION) {} +
	@find -name '*.gcda' -exec mv -t $(LOCATION) {} +
	@find -name '*.out' -exec mv -t $(LOCATION) {} +

Code_Coverage_Report:
	@lcov -t "$(Target)" -o ./Info/coverage.info -c -d . --rc lcov_branch_coverage=1
	@genhtml -o Info/Report ./Info/coverage.info --rc lcov_branch_coverage=1
	@xdg-open ./Info/Report/index.html

Profile:
	@gprof $(Target) $(LOCATION)/gmon.out $(GP_Flags)
	@find -name '*.tcc-ann' -exec mv -t $(LOCATION) {} +
	@find -name '*.cpp-ann' -exec mv -t $(LOCATION) {} +

Memory_leak:
	@gcc $(Source) -o ./SOURCE/$@ -lstdc++
	@valgrind --tool=memcheck \
			 --leak-check=full \
			 --show-reachable=yes \
			 --show-leak-kinds=all \
			 --num-callers=20 \
			 --track-fds=yes \
			 --track-origins=yes \
			 --verbose \
			 --log-file=./Info/G_tools/valgrind-out.txt \
			 ./SOURCE/$@
	@xdg-open ./Info/G_tools/valgrind-out.txt

html_pdf:
	@doxygen -g $(LOCATION)/$(DoxPdf)
	@doxygen $(LOCATION)/$(DoxPdf)
	@find -name 'html' -exec mv -t $(LOCATION) {} +
	@make -C ./latex
	@find -name 'latex' -exec mv -t $(LOCATION) {} +
	@xdg-open ./Info/G_tools/html/index.html
	@xdg-open $(LOCATION)/latex/refman.pdf

debug:
	@gdb $(Target)

clean:
	@rm -rf tags $(filter-out $(LOCATION), $(Delete)) ./SOURCE $(LOCATION)/* Info
