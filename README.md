# Hamster

Clipboard manager for Debian-based distributions - for elementary OS mostly

## Development

Before running app on you local machine, make sure you have *libgtkmm* lib installed

```bash
sudo apt install libgtkmm-3.0-dev libgtkmm-3.0-doc
```

## How to build

```bash
cd hamster
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release && make -j 8 && ./hamster
```

### Issues

#### gsettings schema not installed

```bash
sudo cp data/com.github.slawtul.hamster.gschema.xml /usr/share/glib-2.0/schemas/
sudo /usr/bin/glib-compile-schemas /usr/share/glib-2.0/schemas/
```
