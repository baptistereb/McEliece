start: src/* include/* 
	gcc src/* -I include -o exec -lgsl -lgslcblas -lm && ./exec
clean:
	rm -f exec