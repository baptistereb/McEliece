# McEliece

Demo allowing you to encrypt and decrypt messages with the McEliece cryptosystem (post-quantum resistant) in C


 ## Installation
```sudo apt-get install libgsl-dev```
on fedora :
```sudo dnf install gsl-devel```

## Make
gcc src/* -I include -o exec -lgsl -lgslcblas -lm -lssl -lcrypto && ./exec

![image](https://github.com/baptistereb/McEliece/assets/29438984/27ef592f-8afe-43a0-84ae-56b633430263)
