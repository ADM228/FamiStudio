/* emu2149.h */
#ifndef _EMU2149_H_
#define _EMU2149_H_

#include <stdint.h>

#define PSG_MASK_CH(x) (1<<(x))

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct __PSG
  {

    /* Volume Table */
    uint32_t *voltbl;

    uint8_t reg[0x20];
    int32_t out;

    uint32_t clk, rate, base_incr;
    uint8_t quality;
    uint8_t clk_div;

    uint16_t count[3];
    uint8_t volume[3];
    uint16_t freq[3];
    uint8_t edge[3];
    uint8_t tmask[3];
    uint8_t nmask[3];
    uint32_t mask;

    uint32_t base_count;

    uint8_t env_ptr;
    uint8_t env_face;

    uint8_t env_continue;
    uint8_t env_attack;
    uint8_t env_alternate;
    uint8_t env_hold;
    uint8_t env_pause;

    uint16_t env_freq;
    uint32_t env_whole_period;
    uint32_t env_count;

    uint32_t noise_seed;
    uint8_t noise_scaler;
    uint8_t noise_count;
    uint8_t noise_freq;

    /* rate converter */
    uint32_t realstep;
    uint32_t psgtime;
    uint32_t psgstep;

    uint32_t freq_limit;

    /* I/O Ctrl */
    uint8_t adr;

    /* FamiStudio : triggering related */
    uint8_t trigger_mask;   // Tells us which channels have had an edge this step.
    uint32_t audible_width; // The boundary of audible notes
    uint32_t trigger_width; // Width of 1 frame
    uint8_t env_changed;
    uint8_t env_change_acknowledge;
    uint32_t time_since_last_trigger[3]; // For making a trigger in long absence of one

    /* output of channels */
    int16_t ch_out[3];

  } PSG;

  void PSG_setQuality (PSG * psg, uint8_t q);
  void PSG_setClock(PSG *psg, uint32_t clk);
  void PSG_setClockDivider(PSG *psg, uint8_t enable);
  void PSG_setRate (PSG * psg, uint32_t rate);
  void PSG_setTriggering(PSG *psg, uint32_t width, uint8_t format);
  PSG *PSG_new (uint32_t clk, uint32_t rate);
  void PSG_reset (PSG *);
  void PSG_delete (PSG *);
  void PSG_writeReg (PSG *, uint32_t reg, uint32_t val);
  void PSG_writeIO (PSG * psg, uint32_t adr, uint32_t val);
  uint8_t PSG_readReg (PSG * psg, uint32_t reg);
  uint8_t PSG_readIO (PSG * psg);
  int16_t PSG_calc (PSG *);
  void PSG_setVolumeMode (PSG * psg, int type);
  uint32_t PSG_setMask (PSG *, uint32_t mask);
  uint32_t PSG_toggleMask (PSG *, uint32_t mask);

  enum PSG_triggeringFormat : uint8_t {
    EMU2149_TRIG_FMT_TICKS = 0,
    EMU2149_TRIG_FMT_MILLISECONDS,
    EMU2149_TRIG_FMT_SECONDS,
    EMU2149_TRIG_FMT_HZ
  };

  enum PSG_volumeTable : uint8_t {
    EMU2149_VOL_YM2149 = 0,
    EMU2149_VOL_AY_3_8910,

    EMU2149_VOL_COUNT
  };

  #ifndef EMU2149_VOL_DEFAULT
    #define EMU2149_VOL_DEFAULT EMU2149_VOL_YM2149
  #endif
    
#ifdef __cplusplus
}
#endif

#endif
