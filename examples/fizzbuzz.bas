LET A = 20
LET I = 1
IF I >= A THEN GOTO 15
GOSUB 6
LET I = I + 1
GOTO 2
LET J = I / 3
LET R = I - J * 3
LET K = I / 5
LET S = I - K * 5
IF R = 0 THEN IF S = 0 THEN PRINT "FIZZBUZZ"
IF R = 0 THEN IF S > 0 THEN PRINT "FIZZ"
IF S = 0 THEN IF R > 0 THEN PRINT "BUZZ"
IF R > 0 THEN IF S > 0 THEN PRINT I
RETURN
PRINT "DONE"
