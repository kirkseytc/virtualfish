# Virtualfish
A virtual fish tank in your terminal using the ncurses library.

<b>No Longer Maintained</b>  
This project is no longer maintained.

<b>Redux Announcement</b>  
I am currently working on a "redux" of this program with all new features, be sure to [check it out](https://github.com/kirkseytc/virtualfish-redux)!

## Install
> To install this program you need `gcc`, `make` and `libncurses-dev`

> `libncurses-dev` either can be install with your package manager or by building it from [source](https://invisible-island.net/ncurses/#download)

Download the [latest release](https://github.com/kirkseytc/virtualfish/releases), unzip it, and change directory into the newly created folder.  
Then run the command `sudo make install` to install Virtualfish to the "/usr/local/bin" directory.

At this point you can delete the zip file and the created directory.

## Usage
To use the program, run this command in your terminal.
```bash
virtualfish
```

When the program runs you will be greated with an empty tank. Run some commands to bring life into it.

### Commands
To enter a command, press the esc key and type the command you want.

`Fish`

This command will spawn one fish.

Alias: f

`Quit`

This command will quit out the program

Aliases: q, exit

`Max`

This command will spawn in the max amount of fishes.

Alias: m

`Clear`

This command will remove all current fish.

Alias: c

## Release Notes
Version 1-0-0:
The initial release that met the expectations of the project.
