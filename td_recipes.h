#include QMK_KEYBOARD_H

// Keycode Routines

/**
 * Emulates key press event(Key up + Key down)
 */
void tap_key(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

// ***********************************************

// Modifire routines
/*
void modifier(void (*f)(uint8_t)) {
  if (mods && MOD_BIT(KC_LCTL)) {
    (*f)(KC_LCTL);
  }

  if (mods && MOD_BIT(KC_LGUI)) {
    (*f)(KC_LGUI);
  }

  if (mods & MOD_BIT(KC_LALT)) {
    (*f)(KC_LALT);
  }
}
*/

void mod_key(
    qk_tap_dance_state_t *state,
    uint16_t keycode,
    uint16_t mods[],
    int size,
    uint16_t combo_key
    ) {
  if (state->count >= 2) {
    /*
     * uint16_t mods_size = sizeof(mods)/sizeof(mods[0]);
     * uint16_t mods_size = sizeof(mods);
     **/

    for (int i = 0; i < size; i++) {
      register_code(mods[i]);
    }

    tap_key(combo_key);
  } else if (state->count == 1) {
    tap_key(keycode);
  } else if (state-> pressed) {
    // For future use.
  }
}

void mod_key_reset(uint16_t mods[], int size) {
  /*
   * uint16_t mods_size = sizeof(mods)/sizeof(mods[0]);
   * uint16_t mods_size = sizeof(mods);
   */

  for (int i = 0; i < size; i++) {
    unregister_code(mods[i]);
  }
}
// ***********************************************

// Layer Togglers
void hold_dbl_tap(qk_tap_dance_state_t *state, uint16_t keycode, uint16_t layer, bool pressShift) {
  if (pressShift == true) {
    register_code(KC_LSFT);
  }

  if (state->count > 2) {
    register_code(keycode);
  } else if (state->count > 1) {
    tap_key(keycode);
  } else if ( state->pressed ) {
    unregister_code(KC_LSFT);

    layer_on(layer);
  }

  unregister_code(KC_LSFT);
}

void tap_reset(uint16_t keycode, uint16_t layer) {
  unregister_code(keycode);
  layer_off(layer);
}
// ***********************************************
