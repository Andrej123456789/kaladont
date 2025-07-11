# kaladont

[Kaladont](https://en.wikipedia.org/wiki/Kaladont) is a South Slavic word game popular in BiH, Croatia, Montenegro, North Macedonia, Serbia and Slovenia.

## Rules

- Players say a word which begins with the last two letters of a previous word.
- The word:
  - must have at least `3` letters,
  - cannot be made-up,
  - cannot be repeated,
  - and must not be a name.
- Winner is who says a word ending on `nt`,
  - in some house rules, you are not allowed to say word `kaladont`; however, house rules are possible to modify in `settings.json`

## TODO

- [x] Settings
- [x] Gameplay
  - [x] Local
  - [x] Network
- [x] Computer

## Compile

### Installing dependencies

| Package: | Command:                                                                                                                                |
| -------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| git      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install git`</td><td>`pacman -S git`</td></tr></table>                   |
| make     | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install make`</td><td>`pacman -S make`</td></tr></table>                 |
| gcc      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install gcc`</td><td>`pacman -S gcc`</td></tr></table>                   |
| json-c   | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install libjson-c-dev`</td><td>`sudo pacman -S json-c`</td></tr></table> |

### Compiling & running

| Number: | Step:                        | Command:                                                |
| ------- | ---------------------------- | ------------------------------------------------------- |
| 1       | Clone a repository           | `git clone https://github.com/Andrej123456789/kaladont` |
| 2       | Enter the `src` directory    | `cd kaladont/src`                                       |
| 3       | Compile                      | `make`                                                  |
| 4       | Run the program              | `make run`                                              |
| 5       | Enter the `client` directory | `cd ../client`                                          |
| 6       | Compile and run the client   | `gcc client.c -o client && ./client <ip> <port>`        |

## settings.json
```json
{
    "players": 2, // number of players
    "players_sequence": "00", // 0 - local player, 1 - computer player, 2 - network player

    "kaladont_allowed": true, // is it allowed to say word `kaladont`
    "wait_for_correct_word": false, // should we wait for player to say correct word

    "words_path": ["settings/words.txt"], // paths to the text files containing words, every line contains one word

    "computer": [{
        "depth": 1 // depth of minmax search
    }],

    "network": [{
        "enabled": false, // are network players enabled
        "port": 5555 // server's port
    }]
}

```

## Credits

- [Algorithms Explained – minimax and alpha-beta pruning - Sebastian Lague](https://www.youtube.com/watch?v=l-hh51ncgDI)
- [Coding Adventure: Chess - Sebastian Lague](https://www.youtube.com/watch?v=U4ogK0MIzqk)
- [c-vector](https://github.com/eteran/c-vector)
- [Rječnik hrvatskih jezika](https://github.com/gigaly/rjecnik-hrvatskih-jezika)
- [spisak-srpskih-reci](https://github.com/turanjanin/spisak-srpskih-reci)
