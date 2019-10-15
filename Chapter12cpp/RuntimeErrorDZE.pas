PROGRAM RuntimeErrorDZE;

VAR
    five, fahrenheit, ratio, dze : real;
    
BEGIN
    five  := -1 + 2 - 3 + 4 + 3;
    ratio := five/9.0;

    fahrenheit := 72;

    {Runtime division by zero error.}
    dze := fahrenheit/(ratio - ratio);

    fahrenheit := 90;
END.
