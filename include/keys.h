/*
 * Part of roku-remote
 *
 * Copyright (c) 2009 Thomas Spurden
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef KEYS_H__
#define KEYS_H__

#define KEYS \
	KEY(CK_SELECT), \
	KEY(CK_NORTH), \
	KEY(CK_SOUTH), \
	KEY(CK_WEST), \
	KEY(CK_EAST), \
	KEY(CK_PLAY), \
	KEY(CK_PAUSE), \
	KEY(CK_STOP), \
	KEY(CK_NEXT), \
	KEY(CK_PREVIOUS), \
	KEY(CK_MENU), \
	KEY(CK_EXIT), \
	KEY(CK_POWER), \
	KEY(CK_POWER_ON), \
	KEY(CK_POWER_OFF), \
	KEY(CK_SEARCH), \
	KEY(CK_ADD), \
	KEY(CK_SHUFFLE), \
	KEY(CK_REPEAT), \
	KEY(CK_VOLUME_UP), \
	KEY(CK_VOLUME_DOWN), \
	KEY(CK_BRIGHTNESS), \
	KEY(CK_ROTARY_CLOCKWISE), \
	KEY(CK_ROTARY_COUNTERCLOCKWISE), \
	KEY(CK_ROTARY_SWITCH), \
	KEY(CK_PRESET1), \
	KEY(CK_PRESET2), \
	KEY(CK_PRESET3), \
	KEY(CK_PRESET4), \
	KEY(CK_PRESET5), \
	KEY(CK_PRESET6), \
	KEY(CK_SNOOZE), \
	KEY(CK_SOURCE), \
	KEY(CK_SCAN_UP), \
	KEY(CK_SCAN_DOWN), \
	KEY(CK_GROUP), \
	KEY(CK_ALARM), \
	KEY(CK_PLAYLISTS), \
	KEY(CK_BROWSE_ARTISTS), \
	KEY(CK_BROWSE_ALBUMS), \
	KEY(CK_BROWSE_SONGS), \
	KEY(CK_BROWSE_GENRES), \
	KEY(CK_BROWSE_COMPOSERS), \
	KEY(CK_PRESET_A1), \
	KEY(CK_PRESET_A2), \
	KEY(CK_PRESET_A3), \
	KEY(CK_PRESET_A4), \
	KEY(CK_PRESET_A5), \
	KEY(CK_PRESET_A6), \
	KEY(CK_PRESET_B1), \
	KEY(CK_PRESET_B2), \
	KEY(CK_PRESET_B3), \
	KEY(CK_PRESET_B4), \
	KEY(CK_PRESET_B5), \
	KEY(CK_PRESET_B6), \
	KEY(CK_PRESET_C1), \
	KEY(CK_PRESET_C2), \
	KEY(CK_PRESET_C3), \
	KEY(CK_PRESET_C4), \
	KEY(CK_PRESET_C5), \
	KEY(CK_PRESET_C6), \
	KEY(CK_INTERNET_RADIO), \
	KEY(CK_FM_RADIO), \
	KEY(CK_AM_RADIO), \
	KEY(CK_LAST_MUSIC_SERVER), \
	KEY(CK_VOLUME_50), \
	KEY(CK_BROWSE), \
	KEY(CK_PURPLE), \
	KEY(CK_PRESET1_IR), \
	KEY(CK_PRESET2_IR), \
	KEY(CK_PRESET3_IR), \
	KEY(CK_PRESET4_IR), \
	KEY(CK_PRESET5_IR), \
	KEY(CK_PRESET6_IR)

#define KEY(k) k
enum Key {
	KEYS,
	Key_NumKeys_
};

#undef KEY
#define KEY(k) #k
char const *keySym[] = {
	KEYS
};

#undef KEY

#endif
