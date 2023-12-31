// clang-format off
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>

#define HOST_OS 1
#include "helpers.h"
#include "keypos_corne.h"

#define XXX &none
#define ___ &trans

#define DEF 0
#define NUM 1
#define SYM 2
#define MOV 3
#define SYS 4
#define GAM 5


/* Global settings */

#define QUICK_TAP_MS 200

&sk {  // sticky-key config
  release-after-ms = <900>;  // release after 0.6s
  quick-release;             // no double capitalization when rolling keys
};

&sl {  // sticky-layer config
  ignore-modifiers;          // allow chording sticky mods & layers
};

&lt {  // layer-tap config
  flavor = "balanced";
  tapping-term-ms = <200>;
  quick-tap-ms = <QUICK_TAP_MS>;
};


/* Caps-word */

// tap: sticky-shift | shift + tap/ double-tap: caps-word | hold: shift
ZMK_BEHAVIOR(smart_shft, mod_morph,
  bindings = <&sk LSHFT>, <&caps_word>;
  mods = <(MOD_LSFT)>;
)
#define SYM_SHFT &sym_shft SYM 0
ZMK_BEHAVIOR(sym_shft, hold_tap,
  flavor = "balanced";
  tapping-term-ms = <200>;
  quick-tap-ms = <QUICK_TAP_MS>;
  bindings = <&mo>, <&smart_shft>;
)
&caps_word {  // mods deactivate caps-word, requires PR #1451
  /delete-property/ ignore-modifiers;
};


/* Num-word */

// tap: num-word | double-tap: sticky num-layer | hold: num-layer
#define SMART_NUM &smart_num NUM 0
ZMK_BEHAVIOR(smart_num, hold_tap,
  flavor = "balanced";
  tapping-term-ms = <200>;
  quick-tap-ms = <QUICK_TAP_MS>;
  bindings = <&mo>, <&num_dance>;
)
ZMK_BEHAVIOR(num_dance, tap_dance,
  tapping-term-ms = <200>;
  bindings = <&num_word>, <&sl NUM>;  // reverse this for sticky-num on single tap
)
&num_word {  // num-word, requires PR #1451
  layers = <NUM>;
  continue-list = <BSPC DEL DOT COMMA PLUS MINUS STAR FSLH EQUAL>;
};


/* Homerow mods */

#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left hand
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right hand
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumbs

MAKE_HRM(hml, &kp, &kp, KEYS_R THUMBS)  // left-hand HRMs
MAKE_HRM(hmr, &kp, &kp, KEYS_L THUMBS)  // right-hand HRMs


/* Bluetooth stuff */

SIMPLE_MORPH(bt_shft_clr, SFT, ___, &bt BT_CLR)


/* Reset behavior */

SIMPLE_MORPH(reset_morph, SFT, &sys_reset, &bootloader)


/* Unicode */

ZMK_UNICODE_SINGLE(comb_acute, N0, N3, N0, N1)


/* Combos */

// use require-prior-idle-ms for combos
#undef COMBO_HOOK
#define COMBO_HOOK require-prior-idle-ms = <150>;

#define COMBO_TERM_FAST 18
#define COMBO_TERM_SLOW 30

#define COMBO_LAYERS DEF NUM

#define DEFINE_COMBO(name, act, keys) \
  ZMK_COMBO(name, act, keys, COMBO_LAYERS, COMBO_TERM_FAST)

DEFINE_COMBO(xclm_cmb,  &kp EXCL,     LT2 LT3) // we -> !
DEFINE_COMBO(eql_cmb,   &kp EQL,      LT2 LT1) // er -> =
DEFINE_COMBO(grav_cmb,  &kp GRAV,     LT2 LT0) // et -> `
DEFINE_COMBO(acut_cmb,  &comb_acute,  LT1 LT0) // rt -> U+0301 (combining acute)

DEFINE_COMBO(excl_cmb,  &kp PLUS,   RT2 RT3) // io -> +
DEFINE_COMBO(mns_cmb,   &kp MINUS,  RT1 RT2) // ui -> -

DEFINE_COMBO(pipe_cmb,  &kp PIPE,   LT2 LM3) // se -> |
DEFINE_COMBO(amps_cmb,  &kp AMPS,   LT2 LM1) // ef -> &

DEFINE_COMBO(tab_cmb,   &hml LG(LSHFT) TAB,       LM3 LM4) // as -> tab
DEFINE_COMBO(lpar_cmb,  &hml LG(LALT)  LPAR,      LM2 LM3) // sd -> (
DEFINE_COMBO(rpar_cmb,  &hml LC(LALT)  RPAR,      LM1 LM2) // df -> )
DEFINE_COMBO(qstn_cmb,  &hml LC(LGUI)  QUESTION,  LM1 LM3) // sf -> ?

DEFINE_COMBO(undr_cmb,  &hmr LC(LALT) UNDER,  RM1 RM2) // jk -> _
DEFINE_COMBO(dlr_cmb,   &hmr LG(LALT) DLLR,   RM2 RM3) // kl -> $

DEFINE_COMBO(ctlc_cmb,  &kp LC(C),  LB2 LB3) // xc -> ctrl-c
DEFINE_COMBO(ctlv_cmb,  &kp LC(V),  LB1 LB2) // cv -> ctrl-v

DEFINE_COMBO(hsht_cmb,  &kp HASH,   LM2 LB3) // xd -> #
DEFINE_COMBO(perc_cmb,  &kp PRCT,   LM2 LB1) // dv -> %
DEFINE_COMBO(bslh_cmb,  &kp BSLH,   LM3 LB2) // cs -> backslash
DEFINE_COMBO(at_cmb,    &kp AT,     LM1 LB2) // cf -> @

DEFINE_COMBO(star_cmb,  &kp STAR,  RB2 RB3) // ,. -> *


/* Macros */

/ {
  macros {
    rst_mod_tg: rst_mod_tg {
      compatible = "zmk,behavior-macro";
      wait-ms = <0>;
      tap-ms = <0>;
      #binding-cells = <0>;
      bindings =
        <&macro_press   &kp LSHFT &kp LGUI &kp LALT &kp LCTRL>,
        <&macro_tap     &kt LSHFT &kt LGUI &kt LALT &kt LCTRL>,
        <&macro_release &kp LSHFT &kp LGUI &kp LALT &kp LCTRL>;
    };
  };
};


/* layers */

#define DEFINE_LAYER(name, l1, l2, l3, r1, r2, r3, last6) \
  ZMK_LAYER(name, l1 r1 l2 r2 l3 r3 last6)
#define HML(k1, k2, k3, k4) \
  &hml LSHIFT k1  &hml LGUI k2  &hml LALT k3  &hml LCTRL k4
#define HMR(k1, k2, k3, k4) \
  &hmr LCTRL k1  &hmr LALT k2  &hmr LGUI k3  &hmr LSHIFT k4

// DEFINE_LAYER(name,
//   ___  ___  ___  ___  ___  ___,
//   ___  ___  ___  ___  ___  ___,
//   ___  ___  ___  ___  ___  ___,
//
//   ___  ___  ___  ___  ___  ___,
//   ___  ___  ___  ___  ___  ___,
//   ___  ___  ___  ___  ___  ___,
//
//   ___  ___  ___  ___  ___  ___
// )

DEFINE_LAYER(def,
  &kp TAB      &kp Q   &kp W  &kp E  &kp R  &kp T,
  &kp ESC      HML(A,  S,     D,     F)     &kp G,
  &smart_shft  &kp Z   &kp X  &kp C  &kp V  &kp B,

  &kp Y  &kp U   &kp I      &kp O    &kp P     &kp LBKT,
  &kp H  HMR(J,  K,         L,       SEMI)     &kp SQT,
  &kp N  &kp M   &kp COMMA  &kp DOT  &kp FSLH  &kp RBKT,

  SMART_NUM  SYM_SHFT  &kp SPACE   &kp RET  &lt MOV BSPC  &kp BSPC
)

DEFINE_LAYER(num,
  ___ ___     &kp N7  &kp N8  &kp N9  ___,
  ___ &kp N0  &kp N4  &kp N5  &kp N6  ___,
  ___ ___     &kp N1  &kp N2  &kp N3  ___,

  ___ ___ ___ ___ ___ ___,
  ___ ___ ___ ___ ___ ___,
  ___ ___ ___ ___ ___ ___,

  ___ ___ ___ ___ ___ ___
)

DEFINE_LAYER(sym,
  ___       &kp AT     &kp PIPE   &kp MINUS  &kp EQL   &kp GRAV,
  &tog SYM  &kp EXCL   &kp AMPS   &kp LPAR   &kp RPAR  &kp QUESTION,
  &kp LCTL  &kp DLLR   &kp PRCNT  &kp BSLH   &kp HASH  ___,

  ___       &kp PLUS  &kp MINUS  &kp EQL    ___        ___,
  &kp DLLR  &kp LBRC  &kp RBRC   &kp UNDER  &kp CARET  ___,
  &kp STAR  &kp LBKT  &kp RBKT   &kp STAR   &kp BSLH   ___,

  &tog MOV  &smart_shft  ___   ___  &sl SYS  &kp DEL
)

DEFINE_LAYER(mov,
  ___       ___           ___           ___           ___           &kp TAB,
  &tog MOV  ___           ___           ___           ___           &kp K_CANCEL,
  ___       &bt BT_SEL 0  &bt BT_SEL 1  &bt BT_SEL 2  &bt BT_SEL 3  &bt_shft_clr,

  ___       ___       &kp INS   ___        ___  ___,
  &kp LEFT  &kp DOWN  &kp UP    &kp RIGHT  ___  ___,
  &kp HOME  &kp PGDN  &kp PGUP  &kp END    ___  ___,

  ___  ___  ___   ___  &kp BSPC  ___
)

DEFINE_LAYER(sys,
  &reset_morph  &kp F10  &kp F7  &kp F8  &kp F9  ___,
  &tog SYS      &kp F11  &kp F4  &kp F5  &kp F6  &kp LS(LG(ESC)),
  &kp CAPS      &kp F12  &kp F1  &kp F2  &kp F3  ___,

  &rst_mod_tg  &kt LCTRL     &kt LALT      &kt LGUI  &kt LSHFT  &to SYM,
  &kp C_MUTE   &kp C_VOL_DN  &kp C_VOL_UP  &kp PRSC  ___        &to MOV,
  &kp C_STOP   &kp C_PREV    &kp C_NEXT    &kp C_PP  ___        &to GAM,

  ___  ___  ___  ___  ___  ___
)

DEFINE_LAYER(gam,
  ___    &kp T      &kp Q  &kp W  &kp E  &kp R,
  ___    &kp LSHFT  &kp A  &kp S  &kp D  &kp F,
  &kp Z  &kp LCTRL  ___  ___  ___  ___,

  ___  ___  ___  ___  ___  ___,
  ___  ___  ___  ___  ___  ___,
  ___  ___  ___  ___  ___  &tog GAM,

  &kp LALT  ___  ___  ___  ___  ___
)
