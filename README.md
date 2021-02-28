
# Hamster

Clipboard manager for Debian-based distributions

## Development

Before running app on you local machine, make sure you have *libgtkmm* lib installed

```bash
sudo apt install libgtkmm-3.0-dev libgtkmm-3.0-doc
```


Application

- [ ] Run automatically on system startup
- [ ] Always on top
- [ ] Place at the current mouse position

Text items

- [ ] Eliminate leading and trailing spaces
- [ ] Clear list on quit
- [ ] Set size: 0 - 100 (scale button)

Text item group

- [ ] Default prefix (empty entry)
- [ ] Default suffix ('\n' entry)

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
/usr/bin/glib-compile-schemas ./data/
```
