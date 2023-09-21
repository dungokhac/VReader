#include "audio.h"
#include "soc/rtc_io_reg.h"

void play_audio(const void *data, uint32_t len){
    AudioGeneratorWAV *wav;
    AudioFileSourcePROGMEM *file;
    AudioOutputI2S *out;
    file = new AudioFileSourcePROGMEM( data, len);
    out = new AudioOutputI2S(0, 1);
    // out->SetBitsPerSample(16);
    // out->SetRate(8000);
    // out->SetOutputModeMono(true);
    out->SetGain(1.0);
    out->SetLsbJustified(true);
    wav = new AudioGeneratorWAV();
    wav->begin(file, out);
    while (wav->isRunning()) {
        while (!wav->loop()) {
            wav->stop();
            // Disable DAC2
            REG_CLR_BIT(RTC_IO_PAD_DAC2_REG, RTC_IO_PDAC2_XPD_DAC);
            REG_SET_BIT(RTC_IO_PAD_DAC2_REG, RTC_IO_PDAC2_DAC_XPD_FORCE);
            return;
        }
    }
}