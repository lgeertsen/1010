# Projet noté "1010 le casse brique"

## Mettre a jour github avec ton code

aller dans le dossier 1010
```bash
git pull
git add -A
git commit -m "*message qui explique les changements*"
git push
```

copier dossier sur nouvelle machine
```bash
git clone https://github.com/lgeertsen/1010.git
```

## Compiler
```bash
g++ -Wall -ansi -pedantic main.cpp window.cpp *+tout autres classes* -lncurses -o 1010
```
