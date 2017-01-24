#ifndef CONSOLE_H
#define CONSOLE_H

static const void MakeMeFocused(char *output,bool type)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsoleOutput,
		(type ? FOREGROUND_GREEN : FOREGROUND_RED) |FOREGROUND_INTENSITY);

	printf(output);
	printf("\n");
	SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
}

#endif // CONSOLE_H
