#pragma once

#define ENC_CLK 34
#define ENC_DT 35
#define ENC_SW 32

void encoder_init();
void encoder_update();

int encoder_get_delta();
bool encoder_short_press();
bool encoder_long_press();