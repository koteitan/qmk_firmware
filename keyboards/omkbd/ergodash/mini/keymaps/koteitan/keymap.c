#include QMK_KEYBOARD_H


enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define IME LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty */
  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                 KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                 KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,                  KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
    KC_LALT, KC_LGUI, KC_TAB,      RAISE,        IME,     KC_SPC, KC_SPC, KC_BSPC, KC_BSPC, KC_ENT,      LOWER,        KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /* Lower */
  [_LOWER] = LAYOUT(
    KC_GRV , KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                 KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                 KC_RCBR, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_DQT ,
    KC_LSFT, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_SPC,                  KC_DEL,  KC_N,    KC_M,    KC_LT,   KC_GT,   KC_PGUP, KC_BSLS,
    KC_LALT, KC_LGUI, KC_TAB,      RAISE,        IME,     KC_SPC, KC_SPC, KC_DEL , KC_DEL,  KC_ENT,      LOWER,        KC_HOME, KC_PGDN, KC_END
  ),

  /* Raise */
  [_RAISE] = LAYOUT(
    KC_GRV , KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                 KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    KC_TILD, KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_LCBR,                 KC_RCBR, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_DQT ,
    KC_LSFT, KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_SPC,                  KC_DEL , KC_N,    KC_M,    KC_LT,   KC_GT,   KC_PGUP, KC_BSLS,
    KC_LALT, KC_F11 , KC_TAB,      RAISE,        IME,     KC_SPC, KC_SPC, KC_DEL , KC_DEL , KC_ENT,      LOWER,        KC_HOME, KC_PGDN, KC_END
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, QK_BOOT, UG_TOGG, UG_NEXT, UG_HUED, UG_HUEU,_______,                 _______, UG_SATD, UG_SATU, UG_VALD, UG_VALU, _______, _______,
    _______, _______, BL_TOGG, BL_BRTG, BL_UP  , BL_DOWN,_______,                 _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,_______,                 _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______,_______,_______, _______,_______, _______,          _______, _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
