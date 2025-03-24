# strlx
A "getting started" guide for version 3.0.

## Basics
<img src=".github/setup.png">

strlx prints a message along with your system information by default.

## Usage
`strlx <string>`

strlx will display your string in the information. If there is none parsed, a random (sometimes a bit odd) default will show.

Strings do not require quotes - strlx prints the entirety of argv - but using them is good practice. 

## Installation

There are 2 methods for installation - compiling manually, or grabbing the latest release from [Releases](https://github.com/stx3plus1/strlx/releases/).

Run `chmod +x <the executable>` to mark it as executable, if you cannot run it (ex  [shell] - Killed    [shell]: permission denied).

You can install properly by copying it to /usr/local/bin (`sudo cp strlx /usr/local/bin`)

strlx will automatically write a configuration file on first run (which is defined in src/include/main.h, btw)

## Compile
strlx is designed for Linux and very similar Linux like systems. Not UNIX-like or compliant OSes in general, keep in mind.

Remember to set CC to your compiler if you aren't using gcc and your compiler does not provide it. 

`sudo make install`

to compile then add to /usr/bin/. Make sure /usr/bin is in PATH to ensure strlx can be found in your shell.

## Configuration

strlx looks for your config in  `~/.config/strlx/config.json`, where ~ is the home directory, or makes one if it doesn't exist.

### The file works like this:

The ASCII logo is set with the "ascii" key - which can be "apple", "tux" or "auto". 3.0 revisions will introduce more!

The color is set with the "color" key, which is any hex encoded RGB color with or without a # symbol.

"items" contains your items to fetch with. This is where you put all "inf" or "pri" items.

"pri" allows you to print preset custom messages, the only input is the text in the key option.

"inf" is where all the fetch modules are. There are quite a few, so here they are:

- syst (user@localhost)

- dist (Arch Linux, ...)

- krnl (Linux, version X)

- shll (bash, zsh...)

- proc (Intel Core iX, AMD Ryzen X, ...)

- uptm (5h 10m...)

- memr (43.24GB / 0.01GB)

Finally... "str", which displays the string of choice from either 2 sets of built in strings, or your own input.
