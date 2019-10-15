PROGRAM concordance (input, output);

CONST
    tablesize  = 1000;
    maxwordlen =   20;

TYPE
    charindex  = 1..maxwordlen;
    counttype  = 1..1000;
    tableindex = 1..tablesize;
    wordtype   = ARRAY [charindex] OF char;
    entrytype  = RECORD
                     word  : wordtype;
                     count : counttype;
                 END;
    tabletype  = ARRAY [tableindex] OF entrytype;

VAR
    table : tabletype;
    entry, nextentry : tableindex;
    tablefull : boolean;
    done : boolean;
    rx : integer;
    string : ARRAY [1..100] OF char;

FUNCTION isletter (ch : char) : boolean;

    VAR b : boolean;

    BEGIN
        b :=    ((ch >= 'a') AND (ch <= 'z'))
             OR ((ch >= 'A') AND (ch <= 'Z'));
        isLetter := b;  
    END;

PROCEDURE getch (VAR c : char);

    BEGIN
        rx := rx + 1;
        c  := string[rx];
        done := c = '.';
    END;

PROCEDURE readword (VAR buffer : wordtype);

    CONST
        blank = ' ';

    VAR
        charcount : integer;
        ch : char;

    BEGIN
        IF NOT done THEN BEGIN
            REPEAT
                getch(ch);
            UNTIL done OR isletter(ch);
        END;
        
        IF NOT done THEN BEGIN
            charcount := 0;
            WHILE isletter(ch) DO BEGIN
                IF charcount < maxwordlen THEN BEGIN
                    charcount := charcount + 1;
                    buffer[charcount] := ch;
                END;
                IF done THEN ch := blank
                        ELSE getch(ch);
            END;
            
            FOR charcount := charcount + 1 TO maxwordlen DO BEGIN
                buffer[charcount] := blank;
            END;
        END;
    END;

PROCEDURE printword (buffer : wordtype);

    CONST
        blank = ' ';

    VAR
        charpos : integer;

    BEGIN
        FOR charpos := 1 TO maxwordlen DO write(buffer[charpos]);
    END;

BEGIN
    done := false;
    rx := 0;
    tablefull := false;
    nextentry := 1;
    
    string := 'Now is the time for all good men to come to the aid of their party.';
    writeln(string);
    
    WHILE NOT (done OR tablefull) DO BEGIN
        readword(table[nextentry].word);
        IF NOT done THEN BEGIN
            entry := 1;
            WHILE table[entry].word <> table[nextentry].word DO BEGIN
                entry := entry + 1;
            END;
            IF entry < nextentry THEN BEGIN
                table[entry].count := table[entry].count + 1;
            END
            ELSE IF nextentry < tablesize THEN BEGIN
                nextentry := nextentry + 1;
                table[entry].count := 1;
            END
            ELSE tablefull := true;
        END;
    END;
    IF tablefull THEN BEGIN
        writeln('The table is not large enough.');
    END
    ELSE BEGIN
        writeln;
        writeln('Concordance table with ', nextentry - 1, ' words.');
        writeln;
        
        FOR entry := 1 TO nextentry - 1 DO BEGIN
            printword(table[entry].word);
            writeln(table[entry].count);
        END;
    END;
END.
