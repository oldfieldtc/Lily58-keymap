#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef WPM_ENABLE
  #include "wpm.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LAlt/⌥|LGUI/⌘|LOWER | /Space  /       \Enter \  |RAISE | Play |RGUI/⌘|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                         KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                         KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
      KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,                        KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_LBRC, KC_RBRC,   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
      KC_LALT, KC_LGUI, MO(1), KC_SPC,                              KC_ENT, MO(2), KC_MPLY, KC_RGUI
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Mute |Vol - |Vol + | Play |  Rwd |  Fwd |                    |      |      |      |      |      |  DEL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Caps |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /       /       \      \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MRWD, KC_MFFD,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                       KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
  KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO,   KC_NO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  KC_NO, KC_NO, KC_TRNS, KC_NO,                                   KC_NO, KC_TRNS, KC_NO, KC_NO
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |  #   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /       /       \      \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                           KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                       KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO,
  KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,    KC_NO, KC_NO,   KC_PLUS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  KC_NO, KC_NO, KC_TRNS, KC_NO,                                   KC_NO, KC_TRNS, KC_NO, KC_NO
  ),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /       /       \      \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_NO, KC_NO, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO,   KC_NO, KC_NO, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
    KC_NO, KC_NO, KC_TRNS, KC_NO,                                 KC_NO, KC_TRNS, KC_NO, KC_NO)

};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);
char wpm_str[10];

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    // oled_write_ln(read_timelog(), false);
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write_ln(wpm_str, false); 
  } else {
    // oled_write(read_logo(), false);
    render_logo();
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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

static void render_logo(void) {
	static const char PROGEM my_logo[] = {
		// 'punpun', 128x32px
		0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 
		0x00, 0xff, 0x08, 0x00, 0xff, 0x24, 0x00, 0xff, 0xff, 0x00, 0x8f, 0xff, 0xff, 0x00, 0xff, 0xe3, 
		0x00, 0xff, 0x1f, 0x80, 0xf0, 0xf8, 0xfc, 0x0c, 0x8e, 0xce, 0xfe, 0xfc, 0xf9, 0xe1, 0xcf, 0x1f, 
		0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 
		0x1f, 0x5f, 0x5f, 0x7f, 0x7f, 0x3f, 0xbf, 0xff, 0xbf, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 
		0xff, 0xff, 0x7f, 0x7f, 0x7f, 0xbf, 0xbf, 0xbf, 0xdf, 0xdf, 0x5f, 0x6f, 0x6f, 0xaf, 0xbf, 0xb7, 
		0x97, 0xd7, 0xdb, 0xdb, 0xcb, 0xcf, 0xcd, 0xc5, 0xd7, 0xf2, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
		0x63, 0x63, 0x70, 0xe3, 0xf3, 0xf0, 0xe3, 0xf3, 0xf0, 0xe0, 0xe7, 0xe1, 0xe0, 0xe7, 0xe7, 0xe0, 
		0xe0, 0xe7, 0xc0, 0xc0, 0xc7, 0xc2, 0xc0, 0xe7, 0xc7, 0xc0, 0xc1, 0x8f, 0x89, 0x80, 0x8f, 0x88, 
		0x00, 0x80, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xf3, 
		0xfb, 0xfb, 0xfa, 0xfa, 0xfa, 0xf2, 0xf6, 0xe1, 0xf0, 0x71, 0xe3, 0xa3, 0xa3, 0xc3, 0x00, 0xfe, 
		0x07, 0x99, 0x81, 0x81, 0x01, 0x03, 0x03, 0xf2, 0x02, 0x02, 0x06, 0xe6, 0xe7, 0x05, 0x05, 0x04, 
		0x8d, 0x4e, 0x0a, 0xca, 0xcb, 0x1b, 0x19, 0x1c, 0x94, 0x94, 0x17, 0x37, 0x3f, 0x2f, 0x2b, 0x2b, 
		0x6f, 0x7f, 0x7f, 0x57, 0x57, 0xf7, 0x4f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
		0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xc3, 0xc3, 0xe3, 0xe7, 0x03, 
		0xe0, 0xff, 0xff, 0xff, 0x9f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x98, 0xdb, 
		0xdd, 0xcd, 0xed, 0xef, 0xee, 0xe6, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 
		0xfc, 0xfc, 0xfd, 0xfd, 0xfd, 0xf9, 0xf9, 0xfb, 0xfb, 0xfb, 0x7a, 0xb3, 0xc0, 0xe0, 0xf0, 0xf4, 
		0xf7, 0x64, 0x8c, 0xcf, 0xe8, 0xe8, 0xc8, 0xc8, 0xdf, 0xd9, 0xd8, 0x90, 0x90, 0xb7, 0xb0, 0xbf, 
		0x22, 0x20, 0x20, 0x00, 0x3c, 0x07, 0x50, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
		0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xbe, 0xfe, 
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfd, 0x1d, 0xc0, 0xfe, 
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf9, 0xf3, 0xf3, 0xe7, 0x07, 0x80, 0x9e, 0xbc, 
		0x3c, 0x7d, 0x7d, 0x7d, 0xf9, 0xf9, 0xfb, 0xfb, 0xf3, 0xf3, 0xf3, 0xf7, 0xf7, 0xf7, 0xf7, 0xe7, 
		0xe7, 0xe7, 0xef, 0x6f, 0x8f, 0xcf, 0xef, 0xe7, 0xe9, 0xec, 0xe6, 0xf7, 0xf7, 0xfb, 0xfd, 0x7c, 
		0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xfb, 
		0xfb, 0xf3, 0xf3, 0xe7, 0xf7, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
		0xff, 0xcf, 0xcf, 0xcf, 0xdf, 0x5f, 0x5f, 0x9f, 0x9f, 0xdf, 0xdf, 0xff, 0xef, 0x00, 0x00, 0x00
	};
	oled_write_raw_P(my_logo, sizeof(my_logo));
}