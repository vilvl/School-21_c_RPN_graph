# Expression visualizer
***== Creates graphs of functions defined by arbitrary expressions. To calculate the values ​​of expressions Dijkstra's algorithm is used for translating expressions into Reversed Polish notation. ==***

* ***Conditions***

The size of the field for displaying graphs is a rectangle of 25 by 80 points.

Definition area - [0; 4 Pi]

Range of values - [-1; 1]

Orientation of the coordinate plane - the ordinate axis is directed downward, the abscissa axis is directed to the right.

The center of coordinates is middle of the left border (point {0, 13}).

* ***Graphics***

The field should be displayed using Star symbol for the chart line and "." for the rest of the screen space.


<br/>
<br/>

 ***Example:*** 

Input: sin(cos(2*x))

Output:

```
................................................................................
................................................................................
.........***.................**..................**.................***.........
........*...................*..*................*..*...................*........
............*...................*..............*...................*............
.......*...................*........................*...................*.......
.............*...................*............*...................*.............
..........................*..........................*..........................
......*..................................................................*......
..............*..................................................*..............
..................................*..........*..................................
.........................*............................*.........................
.....*....................................................................*.....
...............*................................................*...............
...................................*........*...................................
....*...................*..............................*...................*....
................*..............................................*................
....................................*......*....................................
.......................*................................*.......................
...*.............*............................................*.............*...
......................*..............*....*..............*......................
..*...............*...................*..*...................*...............*..
**.................***.................**.................***.................**
................................................................................
................................................................................
```


## Possible operations & functions:

> "+" \
> "-" (unary and binary) \
> "*" \
> "/" \
> "^"\
> "()" \
> sin(x) \
> cos(x) \
> tan(x) \
> ctg(x) \
> sqrt(x) \
> ln(x)

