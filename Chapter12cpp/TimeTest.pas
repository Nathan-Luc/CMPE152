PROGRAM TimeTest;

VAR
    now, later: time;
    wrong: time;

BEGIN
	now := later;
	now.hour := 0;
	now.hour := later.hour;
END.
