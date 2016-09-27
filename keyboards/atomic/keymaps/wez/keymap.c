#include "atomic.h"
#include "action_layer.h"
#include "mousekey.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum layer_id {
  BASE = 0,
  MDIA,
  FUNC
};

// Tap dance function ids
enum tap_action_id {
  TD_SFT_CAPS,
};

enum function_id {
  FN_MDIA_TOG,
};

#define ____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap BASE: (Base Layer) Default Layer
   */
[BASE] = {
  {KC_GRV,         KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS, KC_EQL, KC_BSPC, KC_BSPC},
  {KC_TAB,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_LBRC, KC_RBRC,KC_BSLS, KC_DEL},
  {CTL_T(KC_ESC),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   LT(MDIA, KC_SCLN),KC_QUOT, KC_ENT, KC_ENT,  KC_PGUP},
  {TD(TD_SFT_CAPS),KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT, KC_RSFT,KC_UP,   KC_PGDN},
  {F(FN_MDIA_TOG), KC_LCTL,KC_NO,  KC_LALT,KC_LGUI,KC_SPC, KC_SPC, KC_RGUI,KC_RALT,KC_NO,  KC_RCTL,          F(FN_MDIA_TOG),KC_LEFT, KC_DOWN,KC_RIGHT},
},
  /* Keymap MDIA: Media and mouse keys
   * ,--------------------------------------------------------------------------.
   * |    | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10| VDn| VUp| Br-|Br+ |
   * |--------------------------------------------------------------------------|
   * |      |    |MsUp|    |ScDn|    |    |    |    |    |    | BL-| BL+| BL    |
   * |--------------------------------------------------------------------------|
   * |        |MsL |MsDn|MsRt|ScUp|    |     |    |Lclk|Rclk|    |Play|         |
   * |--------------------------------------------------------------------------|
   * |     |RST |    |    |    |    |    |    |    |Prev|Next|    |PgUp|        |
   * |--------------------------------------------------------------------------|
   * |     |     |     |                                |     | Home| PgDn| End |
   * `--------------------------------------------------------------------------'
   */
[MDIA] = {
  {____, KC_F1,  KC_F2,   KC_F3,   KC_F4,         KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_VOLD, KC_VOLU, ____, ____},
  {____, ____,   KC_MS_U, ____,    KC_MS_WH_DOWN, ____,  ____,  ____,  ____,    ____,    ____,    ____,    ____,    ____, KC_F15},
  {____, KC_MS_L,KC_MS_D, KC_MS_R, KC_MS_WH_UP,   ____,  ____,  ____,  KC_BTN1, KC_BTN2, ____,    KC_MPLY, ____,    ____, KC_F14},
  {____, RESET,  ____,    ____,    ____,          ____,  ____,  ____,  ____,    KC_MPLY, KC_MNXT, ____,    ____,    KC_PGUP, ____},
  {____, ____,   ____,    ____,    ____,          ____,  ____,  ____,  ____,    ____,    ____,    ____,    KC_HOME, KC_PGDN, KC_END},
},
};

// Using TD(n) causes the firmware to lookup the tapping action here
qk_tap_dance_action_t tap_dance_actions[] = {
  // Double tap shift to turn on caps lock
  [TD_SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  // mousekey: A bit faster by default, use accel keys for fine control
  mk_max_speed = 10;
  // accelerate a bit faster than usual
  mk_time_to_max = 15;
  // Slightly slower mouse wheel speed than the default
  mk_wheel_max_speed = 4;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
}

// Using F(n) causes the firmware to lookup what to do from this table
const uint16_t PROGMEM fn_actions[] = {
  // See also TAPPING_TOGGLE in our config.h
  [FN_MDIA_TOG] = ACTION_LAYER_TAP_TOGGLE(MDIA),
};
