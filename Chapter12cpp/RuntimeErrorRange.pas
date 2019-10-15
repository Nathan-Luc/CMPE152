PROGRAM RuntimeErrorRange;

VAR
    n : 1..10;
    
BEGIN
    n := 5;   writeln('n = ', n);
    n := 1;   writeln('n = ', n);
    n := 11;  writeln('n = ', n);
    n := -3;  writeln('n = ', n);
    n := 0;   writeln('n = ', n);
END.
