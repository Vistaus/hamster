# Hamster

Clipboard manager for Debian-based distributions - for elementary OS mostly

## Development

Before running app on you local machine, make sure you have *libgtkmm* lib installed

```bash
sudo apt install g++ cmake libgtkmm-3.0-dev libgtkmm-3.0-doc
```

## How to build

```bash
cd hamster
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release && make -j 8 && ./hamster
```

### Todo (last stuff)

* to check if item list size is not exceeded
* to generate translations
* to handle - white spaces symbols (\t, \n) from prefix and suffix fields
* to show small window on shift+enter hit (prefix/suffix)
* to show item lenght on the bottom of window
* to warn if capslock is on
* ...

### Issues

#### Pinned screenshot from Flameshot app

You cannot paste text if you made a screenshot and pinned to desktop

#### gsettings schema not installed

```bash
sudo cp data/com.github.slawtul.hamster.gschema.xml /usr/share/glib-2.0/schemas/
sudo /usr/bin/glib-compile-schemas /usr/share/glib-2.0/schemas/
```
