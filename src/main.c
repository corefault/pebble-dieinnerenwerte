#include "main.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_30_black;
static GFont s_res_droid_serif_28_bold;
static TextLayer *s_spo;
static TextLayer *s_beat;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
#ifdef PBL_PLATFORM_APLITE
  window_set_fullscreen(s_window, true);
#endif 

  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_droid_serif_28_bold = fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD);
  // s_spo
  s_spo = text_layer_create(GRect(0, 60, 64, 35));
  text_layer_set_background_color(s_spo, GColorBlack);
  text_layer_set_text_color(s_spo, GColorWhite);
  text_layer_set_text(s_spo, "-");
  text_layer_set_text_alignment(s_spo, GTextAlignmentRight);
  text_layer_set_font(s_spo, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_spo);
  
  // s_beat
  s_beat = text_layer_create(GRect(77, 60, 63, 35));
  text_layer_set_background_color(s_beat, GColorBlack);
  text_layer_set_text_color(s_beat, GColorWhite);
  text_layer_set_text(s_beat, "-");
  text_layer_set_text_alignment(s_beat, GTextAlignmentRight);
  text_layer_set_font(s_beat, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_beat);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(64, 62, 16, 30));
  text_layer_set_background_color(s_textlayer_1, GColorBlack);
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  text_layer_set_text(s_textlayer_1, "/");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_droid_serif_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_spo);
  text_layer_destroy(s_beat);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main(void) {
  window_stack_remove(s_window, true);
}

void update_main(char* spo, char* pulse) {
   text_layer_set_text(s_spo, spo);
   text_layer_set_text(s_beat, pulse);
}

