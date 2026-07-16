/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};
enum custom_keycodes {
    CMDALT = SAFE_RANGE,
    OPTWIN,
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
    OS_ARRL, // Arrow left:      Opt+Left    / Ctrl+Left
    OS_ARRR, // Arrow right:     Opt+Right   / Ctrl+Right
    OS_ARRD, // Arrow down:      Opt+Down    / Ctrl+Down
    OS_ARRU, // Arrow up:        Opt+Up      / Ctrl+Up
};
/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
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
       LSFT_T(KC_CAPS),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_GRAVE,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_LCTL, KC_ENT,   LOWER,      RAISE,  KC_SPC,
                                            CMDALT, KC_BSPC,     OPTWIN
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_MOD, XXXXXXX, OS_WRDR, XXXXXXX, OS_REDO,  OS_TOP,    KC_LBRC, OS_LSTR,   KC_P8, KC_LBRC, KC_RBRC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT, OS_LEND, XXXXXXX, KC_PGDN, XXXXXXX, OS_BOTM,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      KC_TILDE, OS_UNDO,  OS_CUT, OS_COPY, OS_PSTE, OS_WRDL,    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_LCTL,  KC_ENT, _______,    XXXXXXX, _______,
                                            CMDALT, XXXXXXX,      KC_P0
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPLY, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,    OS_ARRL, OS_ARRR, OS_ARRD, OS_ARRU, XXXXXXX, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______, XXXXXXX,
                                           _______,  KC_DEL,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_RMOD, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           XXXXXXX, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

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
    [OS_ARRL - OS_UNDO] = {A(KC_LEFT), C(KC_LEFT)},
    [OS_ARRR - OS_UNDO] = {A(KC_RGHT), C(KC_RGHT)},
    [OS_ARRD - OS_UNDO] = {A(KC_DOWN), C(KC_DOWN)},
    [OS_ARRU - OS_UNDO] = {A(KC_UP), C(KC_UP)},
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t active_shortcuts[ARRAY_SIZE(os_shortcuts)] = {0};
    static uint16_t cmdalt_key = KC_LALT; // Default to 'Q'
    static uint16_t active_keycode = KC_LWIN; // Default to 'Q'
    switch (keycode) {
        case CMDALT: {
            #if defined(OS_DETECTION_ENABLE)
            os_variant_t host = detected_host_os();
            if (host == OS_MACOS || host == OS_IOS) {
                cmdalt_key = KC_LCMD; // Swap to 'D' on Mac
            }
            #endif

            if (record->event.pressed) {
                register_code16(cmdalt_key);
            } else {
                unregister_code16(cmdalt_key);
            }
            return false; // Handled
        }
        case OPTWIN: {
            #if defined(OS_DETECTION_ENABLE)
            os_variant_t host = detected_host_os();
            if (host == OS_MACOS || host == OS_IOS) {
                active_keycode = KC_LOPT; // Swap to 'D' on Mac
            }
            #endif

            if (record->event.pressed) {
                register_code16(active_keycode);
            } else {
                unregister_code16(active_keycode);
            }
            return false; // Handled
        }
        case OS_UNDO ... OS_ARRU: {
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
        default:
            return true; // Let QMK handle everything else normally
    }
}

