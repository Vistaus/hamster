# Hamster

Clipboard manager for Debian-based distributions - for elementary OS mostly

## Development

Before running app on you local machine, make sure you have *libgtkmm* lib installed and g++ (min. 10.1.0)

```bash
sudo apt install g++ cmake libgtkmm-3.0-dev libgtkmm-3.0-doc
```

## How to build

```bash
cd hamster
mkdir build
meson build
ninja -C build
```

### Todo (last stuff)

* to generate translations
* to prepare debian package
* to link mason and cmake (ask on stackoverflow)
* to handle memory leak (ask on stackoverflow)

### Known issues

#### 1. Pinned screenshot from Flameshot app

You cannot paste text if you took a screenshot and pinned to desktop

#### 2. Gsettings schema not installed

```bash
sudo cp data/com.github.slawtul.hamster.gschema.xml /usr/share/glib-2.0/schemas/
sudo /usr/bin/glib-compile-schemas /usr/share/glib-2.0/schemas/
```

#### 3. About mask password
//todo
