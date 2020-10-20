.PHONY: build

build:
	g++ ./main.cpp -o main

default_goal: build def 
.PHONY: def
def:
	./main -iInput.txt --input=Omg.txt -o --output=Ret.txt -v7 --value=111

.PHONY: run

run:
	./main -h


.DEFAULT_GOAL:=default_goal