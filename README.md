# strfetch
A minimal, fun fetch in plain C.

## About
I felt like it, so I made it.

strfetch prints a silly message along with your fetch, which can be default or custom.

A config file with custom strings is on the to-do list.

## Compile
Compilation for macOS and Linux. 
Install GCC, then:

`chmod +x build.command`

`./build.command`

Copy the resulting executable to a directory in PATH. 

## Usage
`strfetch "<string>"`

strfetch will display your string as an alert in the fetch on the first line. If there is none parsed, a random default based on your computer's time as a seed will be shown.
