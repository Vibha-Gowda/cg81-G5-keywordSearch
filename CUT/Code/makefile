

keywordSearch: main.o keyword.o
	gcc bin/main.o bin/keyword.o -o bin/keywordSearch.exe

main.o: src/main.c
	gcc -c src/main.c -o bin/main.o
	

keyword.o: src/keyword.c
	gcc -c src/keyword.c -o bin/keyword.o

clean:
	rm -rf ./bin/*.exe ./bin/*.o

