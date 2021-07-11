
#include QMK_KEYBOARD_H
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"
#include "td_recipes.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _RAISE  1
#define _LOWER  2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE,
  LOWER,
  BACKLIT,
  PR_LOWER,
  CHROME_ONLY,
  CHROME_DEBUG,
  PAUSE_SCRIPT,
  DEBUG_STEP_OVER,
  DEBUG_STEP_IN,
  DEBUG_STEP_OUT,
  DISABLE_DEBUGER,
  PWD
};

// Tap Dance Declarations
void raise_at(qk_tap_dance_state_t *state, void *user_data) {
  hold_dbl_tap(state, KC_AT, _RAISE, true);
}

void raise_at_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_reset(KC_AT, _RAISE);
}

void f_tmux_prefix(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t mods[] = { KC_LCTL };
  int size = 1;

  mod_key(state, KC_F, mods, size,  KC_A);
}

void f_tmux_prefix_reset(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t mods[] = { KC_LCTL };
  int size = 1;

  mod_key_reset(mods, size);
}

enum {
  TD_NXT_PREV = 0,
  TD_RCMD_RSHFT,
  TD_RAISE_AT,
  TD_SEMI_COLON,
  F_TMUX_PREFIX
  /* TD_RAISE_CAPS */
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_NXT_PREV]  = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_MPRV),
  [TD_RCMD_RSHFT] = ACTION_TAP_DANCE_DOUBLE(KC_RGUI, KC_RSFT),
  [TD_RAISE_AT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raise_at, raise_at_reset),
  [F_TMUX_PREFIX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_tmux_prefix, f_tmux_prefix_reset),
  [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  /* [TD_RAISE_CAPS] = ACTION_TAP_DANCE_DUAL_ROLE(RAISE, KC_CAPS) */
  /*TD(TD_RAISE_AT),*/
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
  * ,---------------------------------------------------------------------------------------------------------.
  * |  `   |   Q  |   W  |   E  |      R      |   T  |   Y  |     U     |      I    |   O  |   P  |    Bksp   |
  * |------+------+------+------+-------------+------+------+-----------+-----------+------+------+-----------|
  * | esc  |   A  |   S  |   D  |   F/ctrl+a  |   G  |   H  |     J     |      K    |   L  |  ; : |   Enter   |
  * |------+------+------+------+-------------+------|------+-----------+-----------+------+------+-----------|
  * | shift|   Z  |   X  |   C  |      V      |   B  |   N  |     M     |      ,    |   .  |   /  |    ' "    |
  * |------+------+------+------+-------------+------+------+-----------+-----------+------+------+-----------|
  * | ctrl |  alt | cmd  |Lower |    Raise    | tab  | Space|  Raise/@  |   Lower   | cmd  | alt  | ctrl/shft |
  * `---------------------------------------------------------------------------------------------------------'
  */
  [_QWERTY] = LAYOUT_ortho_4x12( \
    KC_GRV,  KC_Q,    KC_W,    KC_E,  KC_R,              KC_T,     KC_Y,   KC_U,            KC_I,    KC_O,    KC_P,              KC_BSPC, \
    KC_ESC,  KC_A,    KC_S,    KC_D,  TD(F_TMUX_PREFIX), KC_G,     KC_H,   KC_J,            KC_K,    KC_L,    TD(TD_SEMI_COLON), KC_ENT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,              KC_B,     KC_N,   KC_M,            KC_COMM, KC_DOT,  KC_SLSH,           KC_QUOT, \
    KC_LCTL, KC_LALT, KC_LGUI, LOWER, RAISE,             KC_TAB,   KC_SPC, TD(TD_RAISE_AT), LOWER,   KC_RCTL, KC_RALT,           TD(TD_RCMD_RSHFT)\
  ),


  /* Raise
  * ,-----------------------------------------------------------------------------------.
  * |      |  1   |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |      |  !   |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  \ | |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * |      |  -   |  +   |  =   |  _   |  xxx |  xxx |  xxx |Shift |  [ { |  ] } |Enter |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |      |      |      |      |  del | bksp |      |      |      |      |      |
  * `-----------------------------------------------------------------------------------'
  */
  [_RAISE] = LAYOUT_ortho_4x12( \
  _______, KC_1,       KC_2,    KC_3,    KC_4,          KC_5,       KC_6,          KC_7,         KC_8,        KC_9,          KC_0,           _______, \
  _______, KC_EXCLAIM, KC_AT,   KC_HASH, KC_DOLLAR,     KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_BSLS, \
  _______, KC_MINS,    KC_PLUS, KC_EQL,  KC_UNDERSCORE, XXXXXXX,    XXXXXXX,       KC_RSFT,      XXXXXXX,     KC_LBRC,       KC_RBRC,        KC_ENT, \
  _______, _______,    _______, _______, _______,       KC_DELETE,  KC_BSPC,       _______,      _______,     _______,       _______,        PR_LOWER \
  ),


  /* Lower   (switched to # because KP# were weird in terminal emulators)
  * ,--------+-------------+-------------+---------+---------+--------------+-----------------+---------------+----------------+-------+-----------------+-------.
  * |        | brightness- | brightness+ |   mute  | volume- |    volume+   |     scroll-l    |    l-click    |    scroll-r    |  xxx  |       xxx       |       |
  * +--------+-------------+-------------+---------+---------+--------------+-----------------+---------------+----------------+-------+-----------------+-------+
  * |        |   scroll-u  |   r-click   | mouse-u | l-click |  CHROME_ONLY |       left      |      down     |       up       | right |       xxx       | Enter |
  * +--------+-------------+-------------+---------+---------+--------------+-----------------+---------------+----------------+-------+-----------------+-------+
  * |        |   scroll-d  |   mouse-l   | mouse-d | mouse-r | CHROME_DEBUG | DEBUG_STEP_OVER | DEBUG_STEP_IN | DEBUG_STEP_OUT |  xxx  | DISABLE_DEBUGER |  xxx  |
  * +--------+-------------+-------------+---------+---------+--------------+-----------------+---------------+----------------+-------+-----------------+-------+
  * | QWERTY |             |             |         |         |              |   PAUSE_SCRIPT  |               |                |       |                 |       |
  * `--------+-------------+-------------+---------+---------+--------------+-----------------+---------------+----------------+-------+-----------------+-------'
  */
  [_LOWER] = LAYOUT_ortho_4x12( \
    _______, KC_F14,  KC_F15,  KC__MUTE, KC__VOLDOWN, KC__VOLUP,    KC_WH_L,         KC_BTN1,          KC_WH_R,        XXXXXXX, XXXXXXX,         _______, \
    _______, KC_WH_U, KC_BTN2, KC_MS_U,  KC_BTN1,     CHROME_ONLY,  KC_LEFT,         KC_DOWN,          KC_UP,          KC_RGHT, XXXXXXX,         KC_ENT, \
    _______, KC_WH_D, KC_MS_L, KC_MS_D,  KC_MS_R,     CHROME_DEBUG, DEBUG_STEP_OVER, DEBUG_STEP_IN,    DEBUG_STEP_OUT, XXXXXXX, DISABLE_DEBUGER, XXXXXXX, \
    QWERTY,  _______, _______, _______,  _______,     _______,      PAUSE_SCRIPT,    _______,          _______,        _______,  _______,        _______ \
  ),



  /* Adjust (Lower + Raise)
  * ,------+--------+----------+--------------+-------------+------------+-----------+-----+-----+-----+-----+-----.
  * |  xxx | QWERTY | Audio on |   Audio off  |    RESET    |     xxx    |    xxx    | xxx | xxx | xxx | xxx | xxx |
  * +------+--------+----------+--------------+-------------+------------+-----------+-----+-----+-----+-----+-----+
  * | Caps |   xxx  |    xxx   | CHROME_DEBUG | CHROME_ONLY |     xxx    |    xxx    | xxx | xxx | xxx | xxx | xxx |
  * +------+--------+----------+--------------+-------------+------------+-----------+-----+-----+-----+-----+-----+
  * |  xxx | Voice- |  Voice+  |   Music on   |  Music off  |  Next Song | Prev Song | xxx | xxx | xxx | xxx | xxx |
  * +------+--------+----------+--------------+-------------+------------+-----------+-----+-----+-----+-----+-----+
  * |  xxx |   xxx  |    xxx   |              |             | Play/Pause | Next/Prev |     |     | xxx | xxx | PWD |
  * `------+--------+----------+--------------+-------------+------------+-----------+-----+-----+-----+-----+-----'
  */
  [_ADJUST] = LAYOUT_ortho_4x12( \
    XXXXXXX, QWERTY,  AU_ON,   AU_OFF,       RESET,       XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_CAPS, XXXXXXX, XXXXXXX, CHROME_DEBUG, CHROME_ONLY, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,        MU_OFF,      KC_MPRV, KC_MNXT,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, _______,      _______,     KC_MPLY, TD(TD_NXT_PREV), _______, _______, XXXXXXX, XXXXXXX, PWD \
  )
};


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float guitar_song[][2]     = SONG(GUITAR_SOUND);
float mu_on_scale[][2]     = SONG(MUSIC_ON_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;

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

    case PR_LOWER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(music_scale);
        #endif
        persistant_default_layer_set(1UL<<_LOWER);
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

    case PWD:
      if (record->event.pressed) {
        wait_ms(500);
        send_string_with_delay_P("***********", 100);
      }

      return false;
      break;

    case CHROME_DEBUG:
    case CHROME_ONLY:
      if (record->event.pressed) {
        wait_ms(500);
        send_string_with_delay_P(SS_LGUI(" "), 200);
        wait_ms(500);
        SEND_STRING("google chrome");
        SEND_STRING(SS_TAP(X_ENT));

        if (keycode == CHROME_DEBUG) {
          wait_ms(500);
          send_string_with_delay_P(PSTR(SS_LGUI(SS_LALT("j"))), 244);
        }

        #ifdef AUDIO_ENABLE
          PLAY_SONG(guitar_song);
        #endif
      }
      return false;
      break;

      case DEBUG_STEP_OVER:
        if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_F10));

          #ifdef AUDIO_ENABLE
            PLAY_SONG(guitar_song);
          #endif
        }
        return false;
        break;

    case DEBUG_STEP_IN:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(";"));

        #ifdef AUDIO_ENABLE
          PLAY_SONG(guitar_song);
        #endif
      }
      return false;
      break;

    case DEBUG_STEP_OUT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LSFT(";")));

        #ifdef AUDIO_ENABLE
          PLAY_SONG(guitar_song);
        #endif
      }
      return false;
      break;

    case DISABLE_DEBUGER:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_F8)));

        #ifdef AUDIO_ENABLE
          PLAY_SONG(guitar_song);
        #endif
      }
      return false;
      break;

    case PAUSE_SCRIPT:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(mu_on_scale);
        #endif
        SEND_STRING(SS_TAP(X_F8));
      }
      return false;
      break;
  }

  return true;
}

void matrix_init_user(void) {
}
