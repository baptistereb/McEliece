start: src/* include/* 
	gcc src/* -I include -o exec && ./exec
clean:
	rm -f exec