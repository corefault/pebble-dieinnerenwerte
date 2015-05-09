#include <pebble.h>
#include "main.h"

static char  s_tspo[5];
static char  s_tbeat[5];

enum {
  KEY_OXYGEN = 0,
  KEY_BEAT = 1,
};

//-----------------------------------------------------------------------
static void check_boundaries(int val, int low, int up) {
   //APP_LOG(APP_LOG_LEVEL_INFO, "value is %d", val);
   if (val < low || val > up) {
      vibes_long_pulse();
   }
}
//-----------------------------------------------------------------------
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
   // Read first item
   Tuple *t = dict_read_first(iterator);

   // For all items
   while(t != NULL) {
     // Which key was received?
     switch(t->key) {
     case KEY_OXYGEN:
        if (strlen(t->value->cstring) == 0) {
           strcpy(s_tspo, "n/a");   
        } else {
          snprintf(s_tspo, 5, "%s", t->value->cstring);
          check_boundaries(atoi(t->value->cstring), 80,100);
        }
       break;
     case KEY_BEAT:
        if (strlen(t->value->cstring) == 0) {
           strcpy(s_tbeat, "n/a");   
        } else {
          snprintf(s_tbeat, 5, "%s", t->value->cstring);
          check_boundaries(atoi(t->value->cstring), 62,140);
        }
       break;
     default:
       APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
       break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  update_main(s_tspo, s_tbeat);
}
//-----------------------------------------------------------------------
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}
//-----------------------------------------------------------------------
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}
//-----------------------------------------------------------------------
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}
//-----------------------------------------------------------------------
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
   // each 5 seconds
   if (tick_time->tm_sec % 5 == 0) {
      // just send. it does not have parameters      
      app_message_outbox_send();
   }
} 
//-----------------------------------------------------------------------
static void init() {
   show_main();
   
   // Register callbacks
   app_message_register_inbox_received(inbox_received_callback);
   app_message_register_inbox_dropped(inbox_dropped_callback);
   app_message_register_outbox_failed(outbox_failed_callback);
   app_message_register_outbox_sent(outbox_sent_callback);
   
   // Open AppMessage
   app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
   
   // Register with TickTimerService
   tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}
//-----------------------------------------------------------------------
static void deinit() {
   tick_timer_service_unsubscribe();
   hide_main();
}
//-----------------------------------------------------------------------
int main(void) {
  init();
  app_event_loop();
  deinit();
}
//-----------------------------------------------------------------------