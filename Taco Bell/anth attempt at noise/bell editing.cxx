/** \file
*   Monophonic sine wave synth with simple envelope.
*   Simple monophonic synthesizer with amplitude and pitch envelope controls.
*/

#include "../scripts/library/Midi.hxx"
#include "../scripts/library/Constants.hxx"

// internal processing properties and functions---------------------
double amplitude=0;
double omega=0;

double currentAmplitude=0;
double currentOmega=0;
double currentPhase=0;
double currentPitchOffset=0;
uint8  currentNote=0;
const double period=2*PI;

double amplitudeAttackCoeff=0;
double amplitudeReleaseCoeff=0;
double omegaCoeff=0;

MidiEvent tempEvent;

void handleMidiEvent(const MidiEvent& evt)
{
    switch(MidiEventUtils::getType(evt))
    {
    case kMidiNoteOn:
        {
            amplitude=double(MidiEventUtils::getNoteVelocity(evt))/127.0;
            currentNote=MidiEventUtils::getNote(evt);
            omega=2*PI*pow(2,((double(currentNote-69.0)+currentPitchOffset)/12.0))*440.0/sampleRate;
            break;
        }
    case kMidiNoteOff:
        {
            if(currentNote==MidiEventUtils::getNote(evt))
                amplitude=0;
            break;
        }
    case kMidiPitchWheel:
        {
            currentPitchOffset=2*double(MidiEventUtils::getPitchWheelValue(evt))/8192.0;
            omega=2*PI*pow(2,((double(currentNote-69.0)+currentPitchOffset)/12.0))*440.0/sampleRate;
            break;
        }
    }
}

// dsp script interface--------------------------

string name="Taco Bell Bong";
string description="Monophonic sine wave synth";

string[] inputParametersNames={"Attack", "Release", "Pitch Attack"};
double[] inputParameters(inputParametersNames.length);
double[] inputParametersDefault={.5,.5,.5};

enum SynthParams
{
    kAttackParam = 0,
    kReleaseParam,
    kPitchSmoothParam
};

/** per-block processing function: called for every sample with updated parameters values.
*
*/
void processBlock(BlockData& data)
{
    uint nextEventIndex=0;

    MidiEventUtils::setType(tempEvent,kMidiPitchWheel);
    for(uint i=0;i<data.samplesToProcess;i++)
    {
        // manage MIDI events
        while(nextEventIndex!=data.inputMidiEvents.length && data.inputMidiEvents[nextEventIndex].timeStamp<=double(i))
        {
            handleMidiEvent(data.inputMidiEvents[nextEventIndex]);
            nextEventIndex++;
        }

        // update amplitude and omega
        if(amplitude>currentAmplitude)
            currentAmplitude+=amplitudeAttackCoeff*(amplitude-currentAmplitude);
        else
            currentAmplitude+=amplitudeReleaseCoeff*(amplitude-currentAmplitude);
        currentOmega+=omegaCoeff*(omega-currentOmega);

        // compute sample value
        double sampleValue=currentAmplitude*sin(currentPhase);

        // update phase
        currentPhase+=currentOmega;

        // copy to all outputs
        for(uint ch=0;ch<audioOutputsCount;ch++)
        {
            data.samples[ch][i]=sampleValue;
        }
    }

    // to avoid overflow
    while(currentPhase>period)
        currentPhase-=period;
}

void updateInputParametersForBlock(const TransportInfo@ info)
{
    amplitudeAttackCoeff=pow(10,1.0/(50+sampleRate*inputParameters[kAttackParam]))-1;
    amplitudeReleaseCoeff=pow(10,1.0/(50+sampleRate*inputParameters[kReleaseParam]))-1;
    omegaCoeff=pow(10,1.0/(10+.15*sampleRate*inputParameters[kPitchSmoothParam]))-1;
}

int getTailSize()
{
    return -1;
}