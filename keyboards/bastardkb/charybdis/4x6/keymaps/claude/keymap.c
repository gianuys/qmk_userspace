/**
 * Charybdis 4x6 "claude" keymap.
 *
 * A QWERTY keymap built for seamless switching between macOS (Rectangle) and
 * Arch Linux (Hyprland), with a Neovim-flavoured navigation layer.
 *
 * Core ideas:
 *  - OS_MOD: a "smart" primary modifier. Held, it acts as Cmd on macOS and
 *    Ctrl elsewhere. OS_MOD+C/V/X/Z/A/S/F/T/W/L all do the right thing on
 *    both OSes (e.g. OS_MOD+L focuses the browser URL bar everywhere).
 *  - WIN_MOD: a "smart" window-management modifier. Held, it acts as
 *    Ctrl+Alt on macOS (Rectangle's default prefix) and Super elsewhere
 *    (Hyprland's $mainMod).
 *  - LAYER_NAV: Vim-mnemonic navigation. Arrows on HJKL, and OS-aware
 *    shortcuts placed on the letter Vim uses for the same motion:
 *    A = end of line (vim A), I = start of line (vim I), W/B = word
 *    forward/back (vim w/b), T/G = top/bottom of document (vim gg/G),
 *    U/D = page up/down (vim Ctrl-U/Ctrl-D), R = redo (vim Ctrl-R).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "os_detection.h"

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYM,
    LAYER_NAV,
    LAYER_POINTER,
};

// Sniping is NOT auto-enabled on the pointer layer so you get full DPI by
// default (useful for drag-scroll and 3D work). Press SNIPING to toggle it
// when you need precision.

enum custom_keycodes {
    OS_MOD = SAFE_RANGE, // Held: Cmd on macOS, Ctrl elsewhere.
    WIN_MOD,             // Held: Ctrl+Alt on macOS (Rectangle), Super elsewhere (Hyprland).
    // OS-aware shortcuts. Keep this block contiguous: it indexes os_shortcuts[].
    OS_UNDO, // Undo:            Cmd+Z       / Ctrl+Z
    OS_REDO, // Redo:            Cmd+Shift+Z / Ctrl+Shift+Z
    OS_CUT,  // Cut:             Cmd+X       / Ctrl+X
    OS_COPY, // Copy:            Cmd+C       / Ctrl+C
    OS_PSTE, // Paste:           Cmd+V       / Ctrl+V
    OS_WRDL, // Word left:       Alt+Left    / Ctrl+Left
    OS_WRDR, // Word right:      Alt+Right   / Ctrl+Right
    OS_LSTR, // Start of line:   Cmd+Left    / Home
    OS_LEND, // End of line:     Cmd+Right   / End
    OS_TOP,  // Top of doc:      Cmd+Up      / Ctrl+Home
    OS_BOTM, // Bottom of doc:   Cmd+Down    / Ctrl+End
    OS_SSHT, // Screenshot:      Cmd+Shift+4 / Print Screen
};

#define SYM MO(LAYER_SYM)
#define NAV MO(LAYER_NAV)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    OS_MOD,  KC_SPC,     NAV,        SYM,  KC_ENT,
                                            WIN_MOD, KC_BSPC,     KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYM] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,      KC_P0
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, OS_WRDR, XXXXXXX, OS_REDO,  OS_TOP,    XXXXXXX, KC_PGUP, OS_LSTR, XXXXXXX, OS_SSHT, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, OS_LEND, XXXXXXX, KC_PGDN, XXXXXXX, OS_BOTM,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, OS_UNDO,  OS_CUT, OS_COPY, OS_PSTE, OS_WRDL,    XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           XXXXXXX, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

/** \brief True when the detected host OS wants Cmd-style shortcuts. */
static bool is_mac(void) {
    switch (detected_host_os()) {
        case OS_MACOS:
        case OS_IOS:
            return true;
        default:
            return false;
    }
}

/** \brief OS-aware shortcut table, indexed by `keycode - OS_UNDO`. */
static const uint16_t os_shortcuts[][2] = {
    //             {macOS,          other}
    [OS_UNDO - OS_UNDO] = {G(KC_Z), C(KC_Z)},
    [OS_REDO - OS_UNDO] = {S(G(KC_Z)), S(C(KC_Z))},
    [OS_CUT - OS_UNDO]  = {G(KC_X), C(KC_X)},
    [OS_COPY - OS_UNDO] = {G(KC_C), C(KC_C)},
    [OS_PSTE - OS_UNDO] = {G(KC_V), C(KC_V)},
    [OS_WRDL - OS_UNDO] = {A(KC_LEFT), C(KC_LEFT)},
    [OS_WRDR - OS_UNDO] = {A(KC_RGHT), C(KC_RGHT)},
    [OS_LSTR - OS_UNDO] = {G(KC_LEFT), KC_HOME},
    [OS_LEND - OS_UNDO] = {G(KC_RGHT), KC_END},
    [OS_TOP - OS_UNDO]  = {G(KC_UP), C(KC_HOME)},
    [OS_BOTM - OS_UNDO] = {G(KC_DOWN), C(KC_END)},
    [OS_SSHT - OS_UNDO] = {S(G(KC_4)), KC_PSCR},
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Remember what was registered on press so a change in OS detection
    // between press and release can never leave a key stuck.
    static uint8_t  os_mod_bits   = 0;
    static uint8_t  win_mod_bits  = 0;
    static uint16_t active_shortcuts[ARRAY_SIZE(os_shortcuts)] = {0};

    switch (keycode) {
        case OS_MOD:
            if (record->event.pressed) {
                os_mod_bits = is_mac() ? MOD_BIT(KC_LGUI) : MOD_BIT(KC_LCTL);
                register_mods(os_mod_bits);
            } else {
                unregister_mods(os_mod_bits);
                os_mod_bits = 0;
            }
            return false;

        case WIN_MOD:
            if (record->event.pressed) {
                win_mod_bits = is_mac() ? (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)) : MOD_BIT(KC_LGUI);
                register_mods(win_mod_bits);
            } else {
                unregister_mods(win_mod_bits);
                win_mod_bits = 0;
            }
            return false;

        case OS_UNDO ... OS_SSHT: {
            uint8_t idx = keycode - OS_UNDO;
            if (record->event.pressed) {
                active_shortcuts[idx] = os_shortcuts[idx][is_mac() ? 0 : 1];
                register_code16(active_shortcuts[idx]);
            } else if (active_shortcuts[idx]) {
                unregister_code16(active_shortcuts[idx]);
                active_shortcuts[idx] = 0;
            }
            return false;
        }
    }
    return true;
}


