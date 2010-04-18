/* amSynth
 * (c) 2001-2005 Nick Dowell
 */

#include "Preset.h"

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif

Parameter TimeParameter (const string name, Param id)
{
	return Parameter (name, id, 0, 0, 2.5f, 0, Parameter::PARAM_POWER, 3, 0.0005f, "s");
}

Preset::Preset			(const string name)
:	mName (name)
,	nullparam ("null", kControls_End)
{
	//										name					id					def min max inc		ControlType			base offset label
	mParameters.push_back (TimeParameter	("amp_attack",			kAmpAttack));
	mParameters.push_back (TimeParameter	("amp_decay",			kAmpDecay));
    mParameters.push_back (Parameter		("amp_sustain",			kAmpSustain,		1));
    mParameters.push_back (TimeParameter	("amp_release",			kAmpRelease));
    mParameters.push_back (Parameter		("osc1_waveform",		kOsc1Waveform,		2, 0, 4, 1));
    mParameters.push_back (TimeParameter	("filter_attack",		kFilterAttack));
    mParameters.push_back (TimeParameter	("filter_decay",		kFilterDecay));
    mParameters.push_back (Parameter		("filter_sustain",		kFilterSustain,		1));
    mParameters.push_back (TimeParameter	("filter_release",		kFilterRelease));
    mParameters.push_back (Parameter		("filter_resonance",	kFilterResonance,	0, 0, 0.97f));
	mParameters.push_back (Parameter		("filter_env_amount",	kFilterEnvAmount,	0, -16, 16));
	mParameters.push_back (Parameter		("filter_cutoff",		kFilterCutoff,		1.5, -0.5, 1.5, 0,	Parameter::PARAM_EXP, 16, 0));
    mParameters.push_back (Parameter		("osc2_detune",			kOsc2Detune,		0, -1, 1, 0,		Parameter::PARAM_EXP, 1.25f, 0));
    mParameters.push_back (Parameter		("osc2_waveform",		kOsc2Waveform,		2, 0, 4, 1));
    mParameters.push_back (Parameter		("master_vol",			kMasterVol,			1, 0, 1, 0,			Parameter::PARAM_POWER, 2, 0));
    mParameters.push_back (Parameter		("lfo_freq",			kLFOFreq,			0, 0, 7.5, 0,		Parameter::PARAM_POWER, 2, 0,	"Hz"));
    mParameters.push_back (Parameter		("lfo_waveform",		kLFOWaveform,		0, 0, 4, 1));
    mParameters.push_back (Parameter		("osc2_range",			kOsc2Octave,		0, -1, 2, 1,		Parameter::PARAM_EXP, 2, 0));
	mParameters.push_back (Parameter		("osc_mix",				kOscMix,			0, -1, 1));
	mParameters.push_back (Parameter		("freq_mod_amount",		kFreqModAmount,		0, 0, 1.25992105f,0,Parameter::PARAM_POWER, 3, -1));
	mParameters.push_back (Parameter		("filter_mod_amount",	kFilterModAmount,	-1, -1, 1));
	mParameters.push_back (Parameter		("amp_mod_amount",		kAmpModAmount,		-1, -1, 1));
	mParameters.push_back (Parameter		("osc_mix_mode",		kOscMixRingMod,		0, 0, 1, 1));
	mParameters.push_back (Parameter		("osc1_pulsewidth",		kOsc1Pulsewidth,	1));
	mParameters.push_back (Parameter		("osc2_pulsewidth",		kOsc2Pulsewidth,	1));
	mParameters.push_back (Parameter		("reverb_roomsize",		kReverbRoomsize));
	mParameters.push_back (Parameter		("reverb_damp",			kReverbDamp));
	mParameters.push_back (Parameter		("reverb_wet",			kReverbWet));
	mParameters.push_back (Parameter		("reverb_width",		kReverbWidth,		1));
	mParameters.push_back (Parameter		("distortion_crunch",	kDistortionCrunch,	0, 0, 0.9f));
	mParameters.push_back (Parameter		("osc2_sync",			kOsc2Sync,			0, 0, 1, 1));
}

Preset&
Preset::operator =		(Preset& preset)
{
    for (unsigned i=0; i<preset.ParameterCount(); i++)
    {
		Parameter& p = preset.getParameter (i);
		getParameter (p.getName()).setValue (p.getValue());
    }
    setName (preset.getName());
    return *this;
}

bool
Preset::isEqual(Preset &otherPreset)
{
	for (unsigned i = 0; i < mParameters.size(); i++) {
		if (            getParameter(i).getValue() !=
			otherPreset.getParameter(i).getValue()) {
			return false;
		}
	}
	return true;
}

Parameter & 
Preset::getParameter(const string name)
{
    for (unsigned i = 0; i < mParameters.size(); i++) if (getParameter(i).getName() == name) return mParameters[i];
    return nullparam;
}

void
Preset::randomise()
{
	float master_vol = getParameter("master_vol").getValue ();
	for (unsigned i=0; i<mParameters.size(); i++) getParameter(i).random_val();
	getParameter("master_vol").setValue (master_vol);
}

void
Preset::AddListenerToAll	(UpdateListener* ul)
{
	for (unsigned i=0; i<mParameters.size(); i++) getParameter(i).addUpdateListener (*ul);
}
