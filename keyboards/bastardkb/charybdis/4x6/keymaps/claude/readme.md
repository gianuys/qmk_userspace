# Charybdis 4x6 "claude" keymap

A QWERTY keymap built for seamless switching between macOS (with Rectangle)
and Arch Linux (with Hyprland), with a Neovim-flavoured navigation layer.
Uses QMK's OS Detection so the same physical keys produce the right shortcut
on each OS.

## Smart modifiers (held keys)

| Key       | macOS      | Linux / other | Purpose                                   |
| --------- | ---------- | ------------- | ----------------------------------------- |
| `OS_MOD`  | `Cmd`      | `Ctrl`        | Primary shortcut modifier                 |
| `WIN_MOD` | `Ctrl+Alt` | `Super`       | Window management (Rectangle / Hyprland)  |

`OS_MOD` gives cross-OS continuity for free: `OS_MOD+C/V/X/Z/A/S/F/T/W`
and notably `OS_MOD+L` (browser URL bar) all do the right thing on both OSes.

`WIN_MOD` matches Rectangle's default `Ctrl+Opt` prefix on macOS and acts as
Hyprland's `$mainMod` (`SUPER`) on Linux, so window snapping/focus chords sit
on the same physical key everywhere.

## Layers

- **BASE**: vendor-style QWERTY. Thumbs: `OS_MOD`, `Space`, `NAV` /
  `WIN_MOD`, `Backspace` (left); `SYM`, `Enter` / `Delete` (right).
- **SYM**: symbols on the top row, numpad on the right, RGB controls left.
- **NAV**: Vim-mnemonic navigation (see below).
- **POINTER**: trackball config (DPI, sniping, drag-scroll) and mouse
  buttons, reachable via layer-tap on `Z` and `/`.

## NAV layer: Vim mnemonics that work everywhere

Arrows live on `HJKL`. OS-aware shortcuts sit on the letter Vim uses for the
same motion, so the muscle memory transfers to non-Vim apps:

| NAV + | Vim equivalent | macOS         | Linux / other  |
| ----- | -------------- | ------------- | -------------- |
| `A`   | `A` (line end) | `Cmd+Right`   | `End`          |
| `I`   | `I` (line start)| `Cmd+Left`   | `Home`         |
| `W`   | `w` (word fwd) | `Alt+Right`   | `Ctrl+Right`   |
| `B`   | `b` (word back)| `Alt+Left`    | `Ctrl+Left`    |
| `U`   | `Ctrl-U`       | `Page Up`     | `Page Up`      |
| `D`   | `Ctrl-D`       | `Page Down`   | `Page Down`    |
| `T`   | `gg` (top)     | `Cmd+Up`      | `Ctrl+Home`    |
| `G`   | `G` (bottom)   | `Cmd+Down`    | `Ctrl+End`     |
| `R`   | `Ctrl-R` (redo)| `Cmd+Shift+Z` | `Ctrl+Shift+Z` |
| `Z/X/C/V` | —          | `Cmd+Z/X/C/V` | `Ctrl+Z/X/C/V` |
| `P`   | — (Print)      | `Cmd+Shift+4` | `Print Screen` |

Also on NAV: F1–F12 on the number row, media/volume on the right, and
one-handed clipboard on `ZXCV` (left hand copies while the right hand is on
the trackball). The outer-column `Shift` stays transparent, so
`NAV+Shift+HJKL` selects text.

## macOS terminal caveat

On macOS the line/word motions send `Cmd`/`Alt` arrow combos, which terminals
swallow by default. Enable "natural text editing" in iTerm2 (or map
`Cmd+Arrow` to `Home`/`End` escapes in kitty/alacritty) for these to reach
terminal Neovim. In Neovim itself, plain `Home`/`End`/`PgUp`/`PgDn` work in
all modes.

## Building

```shell
qmk compile -kb bastardkb/charybdis/4x6 -km claude
```
