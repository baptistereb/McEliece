# McEliece
 
```sudo apt-get install libgsl-dev```
ou sur fedora :
```sudo dnf install gsl-devel```


gcc src/* -I include -o exec -lgsl -lgslcblas -lm -lssl -lcrypto && ./exec