# kaladont

[Kaladont](https://en.wikipedia.org/wiki/Kaladont) is South Slavic word game popular in BiH, Croatia, Montenegro, North Macedonia, Serbia and Slovenia.

## Rules

- Players say word which begins with the last two letters of previous word.
  - word must have atleast `3` letters
  - word cannot be made-up
  - previous word cannot be repeated
  - names are not allowed
- Winner is who says word ending on `nt`
  - in some house rules, you are not allowed to say word `kaladont`; however, house rules are possible to modify in `settings.json`

## TODO

- [x] Settings
- [x] Gameplay
  - [x] Local
  - [ ] Networking
- [ ] Computer

## Compile

### Installing dependencies

| Package: | Command:                                                                                                                                |
| -------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| git      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install git`</td><td>`pacman -S git`</td></tr></table>                   |
| make     | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install make`</td><td>`pacman -S make`</td></tr></table>                 |
| gcc      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install gcc`</td><td>`pacman -S gcc`</td></tr></table>                   |
| json-c   | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install libjson-c-dev`</td><td>`sudo pacman -S json-c`</td></tr></table> |

#### External stand-alone dependencies

- [c-vector](https://github.com/eteran/c-vector)
- [CString](https://github.com/C-STD/CString)

### Compiling & running

| Number: | Step:                    | Command:                                                |
| ------- | ------------------------ | ------------------------------------------------------- |
| 1       | Cloning repository       | `git clone https://github.com/Andrej123456789/kaladont` |
| 2       | Entering `src` directory | `cd kaladont/src`                                       |
| 3       | Compiling                | `make`                                                  |
| 4       | Running the program      | `make run`                                              |

## How to change settings?

- `kaladont_allowed` - is it allowed to say word `kaladont`
- `players` - number of players
- `words_path` - list of .txt files containing words

## Credits

- [Rječnik hrvatskih jezika](https://github.com/gigaly/rjecnik-hrvatskih-jezika)
- [spisak-srpskih-reci](https://github.com/turanjanin/spisak-srpskih-reci)
