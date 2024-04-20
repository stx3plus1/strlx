# strfetch
A minimal, fun fetch in plain C.

## About
I felt like it, so I made it.

strfetch prints a silly message along with your fetch, which can be default or custom.

A config file with custom strings is on the to-do list.

## Usage
`strfetch <string>`

strfetch will display your string as an alert in the fetch on the first line. If there is none parsed, a random default based on your computer's time as a seed will be shown.

Strings do not require quotes but using them if implementing strfetch into your shell, for example, is good practice. 

## Compile/Install
Compilation for macOS and Linux. 

Remember to set CC to your compiler if you aren't using GCC, or clang aliased to "gcc" (Apple...)

Make sure a good C compiler and sufficient headers are installed, then:

`make && sudo make install`

to compile then add strfetch to /usr/local/bin. If your shell doesn't have it in PATH, add it!