/** Me fucking around seeing if i can make it make a noise
 * edited from the preset "bell" and i think stripping all the useless stuff..?
*/

#include "../scripts/library/Midi.hxx"
#include "../scripts/library/Constants.hxx"

string name="Tutorial xD";
string description="me being goofy and silly";

array<double> inputParameters(1);
array<string> inputParametersNames={"Volume"};
array<string> inputParametersUnits={"dB"};
array<double> inputParametersMin={-1};
array<double> inputParametersMax={1};
array<double> inputParametersDefault={0};
double volume = 1;

double amplitude = 0;
double omega = 0;
uint8 currentNote = 0;

double amplitudeAttackCoeff = 0;
double amplitudeReleaseCoeff = 0;
double currentPhase = 0;
double currentAmplitude = 0;
 
/*
double currentOmega = 0;
double omegaCoeff = 0;
*/

MidiEvent tempEvent;

bool initialize() { // checks 4 stereo
    if (audioOutputsCount != 2) {
        print("Stereo Channels Only!");
        return false;
    }
    return true;
}

void handleMidiEvent(const MidiEvent& evt){ // checks for midi on/off
    switch (MidiEventUtils::getType(evt))
    {
    case kMidiNoteOn:
        {
            amplitude = volume;
            currentNote=MidiEventUtils::getNote(evt);
        }
        break;
    case kMidiNoteOff:
        {
            if(currentNote==MidiEventUtils::getNote(evt))
                amplitude = 0;
        }
    }
}

void processBlock(BlockData& data) { //processes midi
    uint nextEventIndex = 0;

    //MidiEventUtils::setType(tempEvent,kMidiPitchWheel); // i have no idea what this does
    for(uint i=0;i<data.samplesToProcess;i++)
    {
        while(nextEventIndex!=data.inputMidiEvents.length && data.inputMidiEvents[nextEventIndex].timeStamp<=double(i))
        {
            handleMidiEvent(data.inputMidiEvents[nextEventIndex]);
            nextEventIndex++;
        }
        if(amplitude>currentAmplitude)
            currentAmplitude+=amplitudeAttackCoeff*(amplitude-currentAmplitude);
        else
            currentAmplitude+=amplitudeReleaseCoeff*(amplitude-currentAmplitude);

        //currentOmega+=omegaCoeff*(omega-currentOmega);  // i think omega is just for pitch wheel so i omitted it  
        double sampleValue=amplitude*volume;

        //currentPhase+=currentOmega;

        for(uint ch=0;ch<audioOutputsCount;ch++)
        {
            data.samples[ch][i]=sampleValue;
        }

    }

}


enum SynthParams{
    kAttackParam = 0, 
    kReleaseParam
}

void updateInputParametersForBlock(){
    amplitudeAttackCoeff=pow(10,1.0/(50+sampleRate*inputParameters[kAttackParam]))-1;
    amplitudeReleaseCoeff=pow(10,1.0/(50+sampleRate*inputParameters[kReleaseParam]))-1;
    volume = inputParameters[0];
   
}

int getTailSize()
{
    return -1;
}