# xopen
Simple utility to run Xorg dependant commands, from a TTY or SSH session. This includes Xorg applications - terminals, browsers, etc. - to be opened from a TTY or SSH session.

## Usage

To run the xopen server, simply run `xopen` in the background.

```$ xopen```


Optionially, add the following line to your .xinitrc file, to simplify the process.

```xopen &```


To send commands to xopen, use the `xopen-client`.

```$ xopen-client "xdotool key Super_L+q"```

## Build instructions

To build.
```$ make```

To install.
```# make install```


To uninstall.
```# make uninstall```
