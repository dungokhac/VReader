#ifndef __AUDIO_H__
#define __AUDIO_H__

// #include "main.h"
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

// #include "AudioFileSourceICYStream.h"
// #include "AudioFileSourceBuffer.h"
// #include "AudioGeneratorMP3.h"

#include "wav/khong_thanh_cong.h"
#include "wav/moi_dat_the.h"
#include "wav/moi_dat_van_tay.h"
#include "wav/thanh_cong.h"
#include "wav/xin_cam_on.h"

void play_audio(const void *data, uint32_t len);
// void play_audio_fpt(String name);

#endif