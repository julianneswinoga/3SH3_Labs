#Question 1
- ps -e shows all processes.  Identical to -A
- ps -l enables the long formatter

#Question 2
- ps -e | grep firefox | egrep -o '^[0-9]+ '
