# Tufts Junior Design 2020, Team Smaragdine

## Project summary
This code is to control a small "Swarmbot" consisting of DC motors, photosensors, hall effect sensors, collision detection switches, and a 2 MHz radio communication system. The final bot will be capable of following different-colored tracks, responding to collisions, and transmitting/receiving radio signal to interface with a partner bot.

## Joe's ridiculously granular style guide
### Naming conventions
* `camelCase` is used for variable and function names
* `CAPS_SNAKE` is used for constants
* Enumerated types are denoted by `_t`.
* For pointer declarations, the asterisk goes with the identifier, not the type:
```c++
int *myPointer;
```

* Avoid abbreviations unless the name would otherwise be absurdly long.
* Specific abbreviations `cur`, `prv`, `nxt` when necessary
* Prefer booleans denoted `isFoo` unless this muddles the intent of the name
* Specificity of compound names generailly increases toward the right, e.g. `motorLeft`, `mtrLeftFwd`, `mtrLeftFwdPin`.
* Classes should `#define` `<CLASSNAME>_H` formatted as such.
* Prefer `and`/`or` keywords over `&&`/`||`
* For things like constructors where it makes sense for parameters to have the same name as data members, do it. Example:
```c++
class myClass {
    public:
        myClass(int data);
    private:
        int data;
};


/* Purpose: Initialize data members in a sane way
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
myClass::myClass(int data) {
    this->data = data;
}
```

### Commenting
* Generally avoid `//` comments unless noting something small, like variable units (`// milliseconds`)  or to denote what keyword a closing bracket belongs to (`// switch`).
* If you have to use `//` on consecutive lines, pad with spaces to align them:
```c++
bool foobar; // Comment about foobar
int  baz;    // Comment about baz
```

* For brief descriptions of short blocks, use `/* Block line comments */`
* For functions and any blocks that require more than one line of explanation, use the following template:
```c++
/* Multi
 * line
 * comment
 * The final `/` is in column 75
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 ```
 
 * Function contracts and file headings should follow this template:
 ```c++
/* <For file headers, one line saying what this file is>
 *
 * Purpose: <multi line purpose continues on the next line after 4 additional
 *     space characters.>
 *
 * Parameters:
 *     <foo> : <Don't include parameters section if there aren't any>
 *     <bar> : <Multi-line parameter descriptions are kinda uncomfortable, but
 *             for now I've been continuing flush with the previous line>
 *
 *     <bigLongName> : <Add a newline if changing the indentation amount>
 *
 *  Returns: <Description of return value, what it could be, when it takes
 *      those values, only include if non-void>
 *
 *  Effects: <Descibe whether/when any state is modified by the function, if
 *      applicable. Otherwise, omit this section too>
 *
 *  TODO/Notes/Known bugs: <If there are any of these, include them separated
 *      by newlines like the rest of these sections>
 * 
 *     <New paragraphs skip a line and inherit indentation>
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
```
 
### Indentation, brackets, and spacing
* Use SPACE characters, not tab, for leading whitespace.
* If possible, wrap long lines to be visually inside any brackets:
```c++
void myBigLongFunction(unsigned long bigVariableName, 
                       int paramsContinued) {

    /* Above should all be spaces */

    if (condition1 and condition2 and condition3 or
        cond3 and cond4);
}
```

* Functions, loops, conditionals, and other curly-brace blocks open on same-line
* Place `else`s on the same line as previous `if` closing braces
* DO use braces for single-statement loops/conditionals. You can put the statement in-line if it fits:
```c++
    if (condition) {single_statement();}
    else {foo = some_value;}
    // etc...
```
* Think of bits of code as phrases, sentences, paragraphs, etc. Keep related code close together and don't be afraid of newlines when changing the focus.
* Group variable declarations by type whenever possible, but make them as separate statements to make future editing faster.
* Separate functions and other major blocks by two empty lines. (Only use double-newlines at the global level, not within functions):
```c++
#ifndef EXAMPLE_H
#define EXAMPLE_H


/* Includes, constants, objects etc are kinda their own thing */
#include "foo.h"

const int A = 1;
const int B = 2;
const int C = 3;


/* Purpose: Example function
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
void myFunc() {
    /* STUB */
}


#endif
```

### Miscellaneous
* For overloaded constructors, better to make a private init function and call it from the constructors. Reduces redundancy.
* List built-in headers like `<Arduino.h>` before `"foo.h"`
* Only `#include` what is strictly needed for the current file. For instance, don't `#include` something in a header just because you think the implementation will require it. If only the implementation needs it, only include it in the implementation.
* In general, code what you mean. Even though `1000 >> 1` is faster, strictly speaking, than `1000 / 2`, the latter is preferable if you mean to say "1000 divided by 2" and not "1000 arithmetic shift right." The exception is if a particular bit of code is bottlenecking the process and compiler optimization isn't working.
* To make the control flow more explicit, favor `else` blocks rather than early returns. For example:
```c++
/* THIS IS MISLEADING */
int myFunc(bool isFoo) {
    if (isFoo) {
        do_something();
        return 1;
    }
    return 0;
}


/* THIS IS BETTER */
int myfunc(bool isFoo) {
    if (isFoo) {
        do_something
        return 1;
    else {return 0;}
}


/* Ternary operator is pretty fun, but use it sparingly */
int myFunc(bool isFoo) {
    return isFoo ? 1 : 0; 
}
```
