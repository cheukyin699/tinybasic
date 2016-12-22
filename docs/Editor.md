## The Editor

### Basic Commands

Here are some basic commands that the editor can process. Note that the commands
act a bit like vim, albeit in a simpler and non-ncurses way.

All the commands are the same upper and lower case. Spaces are sometimes
significant (when separating arguments). Commands are in the format of:

```
Xn arg0 arg1 ...
```

Where `X` is the letter the command stands for, `n` is the number of times you
want to repeat the command, and the `args` are the arguments that sometimes go
along with the command. `n`, of course, defaults to 1 when it isn't provided.

All the below examples assume that you have already loaded a file with the
following lines:

```basic
LET I = 0
PRINT I
LET I = I + 1
IF I < 10 THEN GOTO 1
```


#### Quitting

The command letter to quit is `Q`. You can only quit once.


#### Navigation Up/Down a Line

The command letters to move up/down a line is `U`/`D`, respectively. You can
repeat this command however many times you like.

```basic
>> s
0000 LET I = 0
0001 PRINT I
0002 LET I = I + 1
0003 IF I < 10 THEN GOTO 1
>> d2
0002 LET I = I + 1
>> u2
0000 LET I = 0
>> u
At top of file already
```


#### Insertion

The command letter to insert a line is `I`. You can repeat this command to
insert said line onto multiple lines below it. It inserts the line into the
buffer, ***AFTER*** the current line. If the buffer is empty, it fills it. The
current line is updated.

```basic
>> b
>> i print i
>> s
0000 LET I = 0
0001 PRINT I
0002 LET I = I + 1
0003 IF I < 10 THEN GOTO 1
0004 PRINT I
```


#### Removing

The command letter to remove a line is `R`. You can repeat this command to
remove multiple lines at the same time.

```basic
>> t
>> r2
>> s
0000 LET I = I + 1
0001 IF I < 10 THEN GOTO 1
```


#### Displaying

The command letters to display a line/all lines is `C`/`S` respectively. It
prints the line number followed by the actual content on the line. You cannot
repeat this command.

```basic
>> c
0000 LET I = 0
>> s
0000 LET I = 0
0001 PRINT I
0002 LET I = I + 1
0003 IF I < 10 THEN GOTO 1
```


#### Navigation to Top/Bottom

The command letters to do this is `T`/`B` for Top/Bottom respectively. It takes
you to the top/bottom of the file. You cannot repeat this command.

```basic
>> t
0000 LET I = 0
>> b
0003 IF I < 10 THEN GOTO 1
```


#### Saving

The command letter to do this is `W`. It takes an optional parameter of the
filename. Once you have saved it, you don't need the filename because it is
automagically applied. You cannot repeat this command.

```basic
>> w temp2
4 lines written successfully to 'temp2'
>> w
4 lines written successfully to 'temp2'
```


#### Loading

The command letter to do this is `L`. It takes an optional parameter of the
filename. Once you have loaded it, you can reload the original file if you have
altered it *without* the filename because it is automagically applied. You
cannot repeat this command.

```basic
>> l temp
4 lines read successfully from 'temp'
```


#### Execution

The command letter to do this is `X`. It executes the code in the buffer. You
cannot repeat this command.

```basic
>> x
0
1
2
3
4
5
6
7
8
9
```


#### Getting Help

You are reading it, right? There's no need!

The command letter to do this is `H`. It outputs a very limited help screen. The
author recommends that you actually read **THIS** documentation, and use the
help screen when you forget. You cannot repeat this command.


#### File Statistics

The command letter to do this is `?`. It outputs the filename (or `<untitled>`),
the line number it is on, and the total number of lines. You cannot repeat this
command.

```basic
>> l temp
4 lines read successfully from 'temp'
>> ?
Filename: temp
Current line: 0
Total lines: 4
```
