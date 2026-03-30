# Sea Shell

![SeaShell Logo](./Assets/SeaShellLogoDark.png)

### What it is?

Sea shell is a simple shell that indexes the main windows shell commands and adds some new, spicy and useful commands!

## How it works?

```
The shell operates in a loop: 
1. Displays a prompt 
2. Reads user input 
3. Tokenizes the input using strtok() 
4. Executes the command using _spawnvp() 5. Repeats until exit
```
## How it was made built?

This was made using the https://danishpraka.sh Write a Shell in C tutorial, it is a simple guide that helped me to undertand better pointers, memory allocation, here i will present the steps and what i understood of each line while making the first version of the SeaShell.

## 1. The header files used
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
```

**<stdio.h>**

The header file used to output and input data onto the terminal, The main functions used from this header are the fprintf() and printf().

**<stdlib.h>**

The header file used to manipulate memory of the computer, main used functions of this header is malloc(), free(), exit() and realloc().

**<string.h>**

The header file used to manipulate Strings, the main functions used from this header is strtok() to separate the tokens.

**<process.h>**

is used for process-related functions in Windows systems, such as spawning new processes, the main function used from  this header is _spawnvp().

## 2. The defines used

```
#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define TK_BUFF_SIZE 1024
```

**TOK_DELIM**
Was used as the delimiter of the tokens inputted on the command line, being the " " (space), \t to suppress the TAB key and use it as a delimiter, \r to delimit the ENTER key and suppress it and the \n to suppress the new line sign.

**RED**
This define is to change the terminal color of some outputs, as the error output, this can be divided in 4 parts:

"\033" , "0" , "31" , "m"

"\033" represents the Escape code, indicating that the next text will be a command.

"0" Resets the styles apllied.

"31" Indicates the selected color, that beign red, but there is a list of what number each color is, as this list indicates:

30 → Black <br>
31 → Red <br>
32 → Green <br>
33 → Yellow <br>
34 → Blue <br> 
35 → Magenta<br> 
36 → Cyan <br>
37 → White

"m" Applies the previously selected style.

**RESET**

"\033" represents the Escape code, indicating that the next text will be a command, the same as the used in **RED**.

"0" Resets the styles apllied.

"m" Applies the previously selected style.

**TK_BUFF_SIZE**

The number choosen is **1024** because it is a safe bet, it can fit most of the possible commands that the user can enter, and if the command is still too big the memory gets reallocated.

## 3. The Structure of the Shell

The shell is composed by 4 functions and the main function.

namely
```
char *read_line();
char **split_line(char *line);
int dash_dock(void);
int dash_execute(char **args);
```

all of these functions are utilized by the main function called "main".

### The main function

```
int main(void)
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        printf("Sea > ");
        line = read_line();
        args = split_line(line);

        if(args[0] != NULL)
            status = dash_execute(args);

        free(line);
        free(args);
    }

    return EXIT_SUCCESS;
}

```

The Main Function is basically a loop that will always prompt the user to write the needed command.

it firstly starts with the variable declarations, namely *line, **args and status.

char *line: register the input, that being the read_line() function and then it is utilized by the split_line function in the args declaration.

char **args: it is tokenized input, splitted the input by words using the split_line function.

int status: it register the status of the shell, if it gets changed to 0 the shell stops.

then it register the args and makes a test, if the args that read_line() got is not NULL, that meaning there was no command and the user just hit enter, it will execute the dash_execute() function and maintain the status as 1.

and then it frees the space allocated by the line and args to make space for new arguments and lines.

### The read_line() function

Firstly something important in this function is that it returns a pointer, and why that?

it is because it is not actually meant to return char, it is a group of chars, so it is a dynamic array of chars, making it basically a string.

This function NEEDS to return a String or an array of chars.

now going to the variables declared in this function, namely:

    int buffsize = TK_BUFF_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

buffsize: it gets the defined TK_BUFF_SIZE value.

position: Its the variable that stores the actual position on the buffer, that being where the next char will be placed.

*buffer: It is a pointer because malloc() returns the address of where the first element of the allocated array of chars will be placed.

c: stores the representative int of the char in ASCII.

This comparison tests if there was an memory allocation error.

```
if (!buffer)
    {
        fprintf(stderr, RED "dash: Allocation error" RESET "\n");
        exit(EXIT_FAILURE);
    }
```

if there where any error, it will returns in red color the phrase "dash: Allocation error" using fprintf() function.

the fprintf() prints the requested text into a desired place, that can be a file or the terminal, there we using stderr, so it will be outputing on the terminal or an error file if you run SeaShell with this command:

```
./SeaShell 2>errorfile.txt
```

with the ./SeaShell running the Shell and the 2 indicates that everything wrote on the terminal as an **stderr**  will be stored on the errorfile and then after the > will be the file name that the **stderr** will be stored.

If you dont place anything before the > you will store everything wrote on the stdout that meaning the everything with printf() and stdout.

then it will exit the shell if there was a buffer error.`

```
 else
        {
            buffer[position] = c;
        }

        position++;
        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            buffer = realloc(buffer, buffsize);
            if (!buffer)
            {
                fprintf(stderr, RED "dash: Allocation error" RESET "\n");
                exit(EXIT_FAILURE);
            }
        }
```

then, the function will enter a loop that will scan everything thats on the stdin, that being the terminal, so everytime we run getchar() it will a char from the terminal in order, so if i write Hi! it will get: "H" if getchar  get run another time then the  it will gets "i" and then the "!".

and there will be the "if" condition, if the char gets an EOF (End Of File) or an \n value it will makes the actual position an \0 indicating that the line has ended and then returning the buffer.

So that char will be stored in the buffer array in the index of the actual position variable, and then adding 1 to the position so it stores the next char.

then there is another condition that will test if it used the whole allocated memory, and if that is the case it will realloc more 1024 bytes to the buffer.

Then verifying again if there was an memory allocation error, and if that is the case it will exit the program.

### The split_line() function

The split_line function returns an array of an array of chars, that means that it basically return an array of Strings.

The declared variables are:

```
int buffsize = TK_BUFF_SIZE;
int position = 0;
char **tokens = malloc(buffsize * sizeof(char *));
char *token;
```

buffsize: as said before in the read_line() function, the TK_BUFF_SIZE defines the buffsize as 1024 bytes.

position: is the actual position of the tokens array.

**tokens: The tokens is a double pointer that points to the first address of the array of Strings, and the Strings being an array of chars, it is allocated 1024 bytes to this array, because of the same motive as the *buffer of read_line(), it returns and address to an array of 1024 bytes, if it exceds the later function structure will handle it

*token: is a single token, that being just a String, or an array of chars

```
if (!tokens)
    {
        fprintf(stderr, RED "dash: Allocation error" RESET "\n");
        exit(EXIT_FAILURE);
    }
```

The if verifies if there was an memory allocation error with the token, and if it does it will return the same Allocation Error as said before

```
    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, RED "dash: Allocation error" RESET "\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
```

Then it enters a loop until the token is null, in this loop int insets the actual token on the actual position of the tokens array, subsequently adding 1 to the position.

After that it will test if the actual position exceeds the allocated size of the buffer, if it exceed it will realloc more 1024 bytes to the buffer.

Then making checking if there was a memory allocation error.

After that it the strtok() will recieve the NULL parameter and the TOK_DELIM parameter, and then it sets the actual postion of the array, the loop is to run the whole line, storing every token, when the tokens end, it will set the last position of the tokens array as NULL

### The dash_dock() function

It just returns the 0, thus ending the shell program

### The dash_execute() function

The dash execute function executes the command that the user inputed, or any command indexed by the _spawnvp() function.

```
if (strcmp(args[0], "dock") == 0)
        return dash_dock();
```

it tests if the user entered the dock token and then it executes the dock function

    int ret = _spawnvp(_P_WAIT, args[0], (const char * const *) args);
    if (ret == -1)
    {
        printf(RED "dash: command not found: %s\n" RESET, args[0]);
    }

Then it runs a program defined by the main windows programs of the Windows path if it fails it returns -1 and if it dont fail it will print that the command does not exists