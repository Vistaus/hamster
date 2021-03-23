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

* to generate translations
* to export items to json file and import when app starts
* to prepare debian package
* to change project structure
* to handle memory leak (ask on stackoverflow)

### Issues

#### 1. Pinned screenshot from Flameshot app

You cannot paste text if you made a screenshot and pinned to desktop

#### 2. Gsettings schema not installed

```bash
sudo cp data/com.github.slawtul.hamster.gschema.xml /usr/share/glib-2.0/schemas/
sudo /usr/bin/glib-compile-schemas /usr/share/glib-2.0/schemas/
```
