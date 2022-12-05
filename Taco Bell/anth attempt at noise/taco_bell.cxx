/** \file
* Based on examples of simple additive synths
* Uses hard coded params to emulate the sound of the taco bell bong, which is actually a preset of a yamaha dx7
* Anthony Eckert and Isaac Kraus
*/

#include "../scripts/library/Midi.hxx"       // Included libraries within Blue Cat Audio's script creation 
#include "../scripts/library/Constants.hxx"

// internal processing properties and functions---------------------
double amplitude=0;
double omega=0;

double currentAmplitude=0;
double currentOmega=0;
double currentPhase=0;
double currentPitchOffset=0;
uint8  currentNote=0;
uint8  octaveNote = 0;
const double period=2*PI;

double amplitudeAttackCoeff = pow(10, 1.0 / (50 + .5 * sampleRate * 0.1)) - 1; //hard formula for attack
double amplitudeReleaseCoeff= pow(10, 1.0 / (50 + .5 * sampleRate * 40)) - 1; // hard formula for release
double omegaCoeff=0.5; // no clue what this does but it cannot be 0 or 1

MidiEvent tempEvent;

uint activeVoicesCount=0;
array<SynthVoice> voices(24); // this chunk of stuff stolen from "sin synth poly" preset if u wanna help incorporating
// The poly one has the ability to do like 24 voices, we only need two and they can be set by the script (e and then E up an octave)
// w two different amplitudes/releases. Gonna keep working at it idk if that makes sense
SynthVoice tempVoice;

class SynthVoice
{
    double amplitude = 0;
    double omega = 0;

    double currentAmplitude = 0;
    double currentPhase = 0;

    int    currentNote = -1;
    bool   waitingForPedalRelease;

    // handle note on operation
    void NoteOn(const MidiEvent& evt)
    {
        amplitude = double(MidiEventUtils::getNoteVelocity(evt)) / 127.0;
        currentNote = MidiEventUtils::getNote(evt);
        omega = 2 * PI * pow(2, ((double(currentNote - 69.0) + currentPitchOffset) / 12.0)) * 440.0 / sampleRate;
    }

    void NoteOff()
    {
        if (!pedalIsDown)
            // set amplitude to zero. Voice will be freed only when amplitude gets close to zero
            amplitude = 0;
        else
            // remember that note off has been called - will actually release the note later, when the pedal is released
            waitingForPedalRelease = true;
    }

    void ForcePitch()
    {
        omega = 2 * PI * pow(2, ((double(currentNote - 69.0) + currentPitchOffset) / 12.0)) * 440.0 / sampleRate;
    }

    // returns true if voice ended
    double ProcessSample()
    {
        double sampleValue = 0;

        // update amplitude
        currentAmplitude += amplitudeCoeff * (amplitude - currentAmplitude);
        if (amplitude == 0 && currentAmplitude < .0001)
        {
            // value below threshold => the voice ended

            // if not the last voice in the list
            if (voices[activeVoicesCount - 1] != this)
            {
                // swap with last voice in the list
                this = voices[activeVoicesCount - 1];
                voices[activeVoicesCount - 1].CancelNote();

                // decrease voices count
                activeVoicesCount--;

                // process swaped voice instead of this one
                return ProcessSample();
            }
            else
            {
                // cancel current note
                CancelNote();

                // decrease voices count
                activeVoicesCount--;
                return 0;
            }
        }

        // compute sample value
        sampleValue = currentAmplitude * (4 * sin(currentPhase * .5) + 5 * sin(currentPhase) + 5 * sin(currentPhase * 1.5) + 5 * sin(currentPhase * 2) + 5 * sin(currentPhase * 3));

        // update phase
        currentPhase += omega;
        return sampleValue;
    }
}

void handleMidiEvent(const MidiEvent& evt)
{
    switch(MidiEventUtils::getType(evt))
    {
    case kMidiNoteOn:
        {
            amplitude=0.1; // SETS VOLUME OF NOTE
            currentNote=MidiEventUtils::getNote(evt); 
            activeVoicesCount++;
            //voices[activeVoicesCount].NoteOn(evt);
            octaveNote = currentNote + 3; // I think we can use this eventually to make a second noise? i dunno im confusd
            omega=2*PI*pow(2,((double(currentNote-69.0)+currentPitchOffset)/12.0))*440.0/sampleRate;
            break;
        }
    case kMidiNoteOff:
        {
            if(currentNote==MidiEventUtils::getNote(evt))
                amplitude=0;
            break;
        }
        
    /*case kMidiPitchWheel:
        {
            currentPitchOffset=2*double(MidiEventUtils::getPitchWheelValue(evt))/8192.0;
            omega=2*PI*pow(2,((double(currentNote-69.0)+currentPitchOffset)/12.0))*440.0/sampleRate;
            break;
        }*/
    }
}

// dsp script interface--------------------------

string name="Taco Bell Synth";
string description="Created by Isaac Kraus and Anthony Eckert";

/*
string[] inputParametersNames={"Attack", "Release", "Pitch Attack"};
double[] inputParameters(inputParametersNames.length);
double[] inputParametersDefault={.5,.5,.5};
*/



enum SynthParams
{
    kAttackParam = 0,
    kReleaseParam, 
};



/** per-block processing function: called for every sample with updated parameters values.
*
*/
void processBlock(BlockData& data)
{
    // smooth gain update: use begin and end values
    // since the actual gain is exponential, we can use the ratio between begin and end values
    // as an incremental multiplier for the actual gain
   // double gainDiff = data.endParamValues[kGainParam] - data.beginParamValues[kGainParam];
    //double gainRatio = 1;
   // if (gainDiff != 0)
   //     gainRatio = pow(10, gainDiff / double(data.samplesToProcess) * 2);

    uint nextEventIndex = 0;
    for (uint i = 0; i < data.samplesToProcess; i++)
    {
        // manage MIDI events
        while (nextEventIndex != data.inputMidiEvents.length && data.inputMidiEvents[nextEventIndex].timeStamp <= double(i))
        {
            handleMidiEvent(data.inputMidiEvents[nextEventIndex]);
            nextEventIndex++;
        }

        // compute sample value
        double sampleValue = 0;
        for (uint v = 0; v < activeVoicesCount; v++)
        {
            sampleValue += voices[v].ProcessSample();
        }
        sampleValue *= gain;

        // copy value to all outputs
        for (uint ch = 0; ch < audioOutputsCount; ch++)
        {
            data.samples[ch][i] = sampleValue;
        }

        // update the gain
        gain *= gainRatio;
    }

    // to avoid overflow, reduce phase for all active voices
    for (uint i = 0; i < activeVoicesCount; i++)
    {
        voices[i].ReducePhase();
    }
}

/*
void updateInputParametersForBlock(const TransportInfo@ info)
{
    //amplitudeAttackCoeff=pow(10,1.0/(50+sampleRate*inputParameters[kAttackParam]))-1;
    //amplitudeReleaseCoeff=pow(10,1.0/(50+sampleRate*inputParameters[kReleaseParam]))-1;
    omegaCoeff=pow(10,1.0/(10+.15*sampleRate*inputParameters[kPitchSmoothParam]))-1;
}
*/

int getTailSize()
{
    return -1;
}