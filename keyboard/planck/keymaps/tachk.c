/* planck.h already has the IFDEF/include for BACKLIGHT_ENABLE and backlight.h,
and keymap_common.h */

#include "planck.h"

/* Setting up layers. Base [0] layer is qwerty, Layer 1 [virtual layer -1/lower]
is for function keys, macros, and media mostly, Layer 2 [virtual layer 1/raise]
is for numbers and brackets and such, and Layer 3 [virtual layer 2/raise x2]
is for colemak alphas, but other keys are kept the same as Layer 0. */

#define _BS  0
#define _RS  1
#define _LW  2
#define _CM  3
#define _ZZ  4

/* I'm using an MIT plate, but the keymapping grid remains of the same dimensions
as the default key layout. NOTE: TG() "Only works upwards in the layer stack." */
// TODO: Do something about TG() only working up the stack...

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LW] = { /* LAYER 2: FUNCTIONS 'N' MACROS LAYER */
      {KC_MUTE,     KC_VOLD,    KC_VOLU, M(1),    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_EQL,  KC_DEL },
      {KC_NO,       KC_LCBR,    KC_RCBR, KC_NO,   KC_PLUS, KC_NO,   KC_NO,   KC_MINS, KC_NO,   KC_LBRC, KC_RBRC, KC_CAPS},
      {KC_F1,       KC_F2,      KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
      {KC_NO,       M(0),       KC_NO,   KC_NO,   KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_NO,   KC_NO,   KC_END }
    },
    [_BS] = { /* LAYER 0: QWERTY LAYER */
      {KC_ESC,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
      {KC_TAB,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
      {KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
      {KC_LCTL,     TG(3),   KC_LGUI, KC_LALT, MO(2),   KC_SPC,  KC_SPC,  MO(1),   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT}
    },
    [_RS] = { /* LAYER 1: NUM, BRACKETS, ETC. LAYER */
      {KC_GRV,   KC_1,                   KC_2,           KC_3,       KC_4,       KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC },
      {KC_NO,    KC_NO,                  KC_NO,          KC_NO,      KC_PLUS,    KC_NO,   KC_NO,   KC_MINS,  KC_NO,   KC_NO,   KC_NO,   KC_BSLS },
      {KC_LSFT,  LCTL(LSFT(KC_TAB)),     LCTL(KC_TAB),   KC_COPY,    KC_PASTE,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_ENT  },
      {KC_NO,    KC_NO,                  KC_NO,          KC_NO,      KC_NO,      KC_SPC,  KC_SPC,  KC_TRNS,  KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R }
    },
    [_CM] = { /* LAYER 3: COLEMAK ALPHAS LAYER */
      {KC_ESC,      KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
      {KC_TAB,      KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
      {KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
      {KC_LCTL,     TG(3),   KC_LGUI, KC_LALT, MO(4),   KC_SPC,  KC_SPC,  KC_NO,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT}
    },
    [_ZZ] = { /* LAYER 4: RESET LAYER */
      {M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),   M(2) },
      {M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),   M(2) },
      {M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),    M(2),   M(2) },
      {M(2),    M(2),    M(2),    M(2),    KC_TRNS, M(2),    M(2),    M(2),    M(2),    M(2),    M(2),   RESET}
    }
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    // [Comment from default keymap] MACRODOWN only works in this function
    switch(id) {
        case 0: /* Macro: Step through backlight levels */
          if (record->event.pressed) {
              register_code(KC_RSFT);
              #ifdef BACKLIGHT_ENABLE
                backlight_step();
              #endif
          }
          else {
            unregister_code(KC_RSFT);
          }
          break;

        case 1: /* Macro: Types out git status (was having issues w/other macro getting the parens to come through) */
          if (record->event.pressed) {
              return MACRO( I(25), T(G), T(I), T(T), T(SPC), T(S), T(T), T(A), T(T), T(U), T(S), W(50), END );
          }
          break;

        case 2: /* Macro: Type warning message to help warn when on RESET layer) */
          if (record->event.pressed) {
              return MACRO( I(25), T(N), T(O), T(P), T(E), T(DOT), W(50), END ); // Error when chaining mod keys here...
          }
          break;
    }
    return MACRO_NONE;
};
