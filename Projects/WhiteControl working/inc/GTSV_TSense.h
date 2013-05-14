#ifndef __GTSV_TSENSE_H_INCLUDED
#define __GTSV_TSENSE_H_INCLUDED

#include "main.h"
#include "stm32_tsl_api.h"

#define TS_KEY01	sSCKeyInfo[0]
#define TS_KEY02	sSCKeyInfo[1]
#define TS_KEY03	sSCKeyInfo[2]
#define TS_KEY04	sSCKeyInfo[3]
#define TS_KEY05	sSCKeyInfo[4]

#define TS_KEY01_DETECTED (TS_KEY01.Setting.b.DETECTED)
#define TS_KEY02_DETECTED (TS_KEY02.Setting.b.DETECTED)
#define TS_KEY03_DETECTED (TS_KEY03.Setting.b.DETECTED)
#define TS_KEY04_DETECTED (TS_KEY04.Setting.b.DETECTED)
#define TS_KEY05_DETECTED (TS_KEY05.Setting.b.DETECTED)

#define KEY_MINUS_DETECTED	(TS_KEY01_DETECTED)
#define KEY_AUTO_DETECTED	(TS_KEY02_DETECTED)
#define KEY_TIMER_DETECTED	(TS_KEY03_DETECTED)
#define KEY_PLUS_DETECTED	(TS_KEY04_DETECTED)
#define KEY_LIGHT_DETECTED	(TS_KEY05_DETECTED)


enum Tsense_key_enum_t {
	TSENSE_KEY_MINUS=0,
	TSENSE_KEY_AUTO=1,
	TSENSE_KEY_TIMER=2,
	TSENSE_KEY_PLUS=3,
	TSENSE_KEY_LIGHT=4
};

//call this to initialize Touch Sense
void Tsense_to_default_config(void);

//call this in a loop to process touch sense actions
void Tsense_action(void);

void Tsense_key_detect_first(void);

uint8_t Tsense_check_rising_edge(enum Tsense_key_enum_t key);
uint8_t Tsense_check_high_level(enum Tsense_key_enum_t key);
uint8_t Tsense_check_key_hold(enum Tsense_key_enum_t key);

void Tsense_key_detect_last(void);



#endif /* __GTSV_TSENSE_H_INCLUDED */
/******************* (C) COPYRIGHT 2013 Global Tech Solution Co., Ltd. *****END OF FILE****/