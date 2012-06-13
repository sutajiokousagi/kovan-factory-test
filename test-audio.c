#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "harness.h"

int test_audio(void) {
	int i;
	int err;
	short buf[128];
	unsigned int rate;

	snd_pcm_t *playback_handle;
	snd_pcm_hw_params_t *hw_params;

	if ((err = snd_pcm_open (&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		harness_error(0, "Cannot open default audio device (%s)",
			 snd_strerror(err));
		return 1;
	}
	   
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		harness_error(1, "Cannot allocate hardware parameter structure (%s)",
			 snd_strerror(err));
		return 1;
	}
			 
	if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0) {
		harness_error(2, "cannot initialize hardware parameter structure (%s)",
			 snd_strerror(err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		harness_error(3, "cannot set access type (%s)",
			 snd_strerror(err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		harness_error(4, "cannot set sample format (%s)",
			 snd_strerror(err));
		return 1;
	}

	rate = 44100;
	if ((err = snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &rate, 0)) < 0) {
		harness_error(5, "cannot set sample rate (%s)",
			 snd_strerror(err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, 2)) < 0) {
		harness_error(6, "cannot set channel count (%s)",
			 snd_strerror(err));
		return 1;
	}

	if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0) {
		harness_error(7, "cannot set parameters (%s)",
			 snd_strerror(err));
		return 1;
	}

	snd_pcm_hw_params_free (hw_params);

	if ((err = snd_pcm_prepare (playback_handle)) < 0) {
		harness_error(8, "cannot prepare audio interface for use (%s)",
			 snd_strerror(err));
		return 1;
	}

	for (i = 0; i < 10; ++i) {
		if ((err = snd_pcm_writei (playback_handle, buf, 128)) != 128) {
			harness_error(9, "write to audio interface failed (%s)",
				 snd_strerror(err));
			return 1;
		}
	}

	snd_pcm_close (playback_handle);
	return 0;
}
