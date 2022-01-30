# TowerOfHanoi

[Tower of Hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi) is an age old puzzle with three rods, and a number of discs stacked onto one another in decreasing order. <br>
Objective of the puzzle is to move the entire structure to the third rod, following this rule- 
> You can only move one disk at a time, and can only place a disk on an empty rod, or a rod containing a disk larger than current disk.

Initial state - `[1,2,3,4]` `[]` `[]` <br>
State to achieve - `[]` `[]` `[1,2,3,4]` <br>
There are various solutions of this puzzle(with 3 cubes(or disks)), here are the two I know -  

### Soln1 -> Dynamic programming

After visualizing the [problem](http://towersofhanoi.info/Animate.aspx) again and again, maybe you will see a pattern? <br> <br>
We follow a specific pattern of moving cubes, first from rod1 -> rod2, then rod1 -> rod3, then rod2 -> rod3, in ... every ... damn ... situation! <br>
If moving from rod1 -> rod2 is illegal, then no problem, rod2 -> rod1 will definitely be a legal move. (Think on why rod1 -> rod2 was illegal in the first place). <br>
So, we just need to check if a move is legal, and repeat 1->2, 1->3, 2->3, until we reach our goal, as easy as that!

### Soln2 -> Good old Recursion

This is the solution you most probaly read everywhere - <br>
So we need to do - `[1,2,3,4]` `[]` `[]` $\rightarrow$ `[]` `[]` `[1,2,3,4]`, i.e. move `[1,2,3,4]` from rod1 to rod3 <br>
Which can be broken down into - Moving `[1,2,3]`, rod1 -> rod2 + Moving `[4]` rod1 -> rod3 + Moving `[1,2,3]`, rod2 -> rod3
$\implies$ (Moving `[1,2]`, rod1 -> rod3 + Moving `[3]`, rod1 -> rod2 + Moving `[1,2]`, rod3 -> rod2 ) + Moving `[4]` from rod1 to rod3 + (Moving `[1,2]`, rod2 -> rod1 + Moving `[3]`, rod2 -> rod3 + Moving `[1,2]`, rod1 -> rod3 ) <br>
and so on...
It can be visualized by drawing a recursive tree. <br>
Here is the recurrence relation - <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = T(n-1) + 1 + T(n-1)"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2\times T(n-1) + 1"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2\times[2\times T(n-2) + 1] + 1"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2\times [2\times [2\times T(n-3) + 1] + 1] + 1"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2^{k} \times T(n-k) + (2^{k}-1)"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2^{n-1} \times T(1) + (2^{n-1}-1)"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2^{n-1} + 2^{n-1}-1"> <br>
<img src="https://render.githubusercontent.com/render/math?math=T(n) = 2^{n}-1"> <br>

So, its time complexity is exponential.
