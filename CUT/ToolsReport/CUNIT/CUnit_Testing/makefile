Main_testdriver.c : Main_testdriver.o valid.o valid_suite.o result.o result_suite.o
	gcc -o bin/file.tests bin/Main_testdriver.o bin/valid.o bin/valid_suite.o bin/result.o bin/result_suite.o -lcunit 


Main_testdriver.o: src/Main_testdriver.c
	gcc -o bin/Main_testdriver.o -c src/Main_testdriver.c 

valid.o: src/valid.c
	gcc -o bin/valid.o -c src/valid.c 

valid_suite.o: src/valid_suite.c
	gcc -o bin/valid_suite.o -c src/valid_suite.c

result.o: src/result.c
	gcc -o bin/result.o -c src/result.c 

result_suite.o: src/result_suite.c
	gcc -o bin/result_suite.o -c src/result_suite.c

clean: 
	echo "Cleaning files ..."
	rm bin/Main_testdriver.c bin/Main_testdriver.o bin/valid.o bin/valid_suite.o bin/result.o bin/result_suite.o 
