start: src/* include/* 
	gcc src/* -I include -o exec -lgsl -lgslcblas -lm -lssl -lcrypto && ./exec
clean:
	rm -f exec