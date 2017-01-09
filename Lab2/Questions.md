#Question 1
- `ps -e` shows all processes.  Identical to -A
- `ps -l` enables the long formatter

#Question 2
- `kill $(ps -e | grep firefox | egrep -o '^[0-9]+ ')`

#Question 3
- Twice. (One for child and one for parent)

#Question 4
- `pstree` shows a tree hierarchy of all processes

