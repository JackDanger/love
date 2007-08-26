/* ========================================================================================== */
/* FMOD Ex - C++ header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004.           */
/*                                                                                            */
/* Use this header in conjunction with fmod.h (which contains all the constants / callbacks)  */
/* to develop using C++ classes.                                                              */
/* ========================================================================================== */

#ifndef _FMOD_HPP
#define _FMOD_HPP

#include "fmod.h"

/*
    Constant and defines
*/


/*
    FMOD Namespace
*/
namespace FMOD
{
    class System;
    class Sound;
    class Channel;
    class ChannelGroup;
    class DSP;
    class Geometry;

    /*
        FMOD System memory functions (optional).
    */
    inline FMOD_RESULT Memory_Initialize(void *poolmem, int poollen, FMOD_MEMORY_ALLOCCALLBACK useralloc, FMOD_MEMORY_REALLOCCALLBACK userrealloc, FMOD_MEMORY_FREECALLBACK userfree) { return FMOD_Memory_Initialize(poolmem, poollen, useralloc, userrealloc, userfree); }
    inline FMOD_RESULT Memory_GetStats  (int *currentalloced, int *maxalloced) { return FMOD_Memory_GetStats(currentalloced, maxalloced); }

    /*
        FMOD System factory functions.
    */
    inline FMOD_RESULT System_Create(System **system) { return FMOD_System_Create((FMOD_SYSTEM **)system); }

    /*
       'System' API
    */

    class System
    {
      private:

        System();   /* Constructor made private so user cannot statically instance a System class.  
                       System_Create must be used. */
      public:

        FMOD_RESULT F_API release                ();
                                                 
        // Pre-init functions.
        FMOD_RESULT F_API setOutput              (FMOD_OUTPUTTYPE output);
        FMOD_RESULT F_API getOutput              (FMOD_OUTPUTTYPE *output);
        FMOD_RESULT F_API getNumDrivers          (int *numdrivers);
        FMOD_RESULT F_API getDriverName          (int id, char *name, int namelen);
        FMOD_RESULT F_API getDriverCaps          (int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency, FMOD_SPEAKERMODE *controlpanelspeakermode);
        FMOD_RESULT F_API setDriver              (int driver);
        FMOD_RESULT F_API getDriver              (int *driver);
        FMOD_RESULT F_API setHardwareChannels    (int min2d, int max2d, int min3d, int max3d);
        FMOD_RESULT F_API getHardwareChannels    (int *num2d, int *num3d, int *total);
        FMOD_RESULT F_API setSoftwareChannels    (int numsoftwarechannels);
        FMOD_RESULT F_API getSoftwareChannels    (int *numsoftwarechannels);
        FMOD_RESULT F_API setSoftwareFormat      (int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod);
        FMOD_RESULT F_API getSoftwareFormat      (int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits);
        FMOD_RESULT F_API setDSPBufferSize       (unsigned int bufferlength, int numbuffers);
        FMOD_RESULT F_API getDSPBufferSize       (unsigned int *bufferlength, int *numbuffers);
        FMOD_RESULT F_API setFileSystem          (FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, int buffersize);
        FMOD_RESULT F_API attachFileSystem       (FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek);
        FMOD_RESULT F_API setAdvancedSettings    (FMOD_ADVANCEDSETTINGS *settings);
        FMOD_RESULT F_API getAdvancedSettings    (FMOD_ADVANCEDSETTINGS *settings);
        FMOD_RESULT F_API setSpeakerMode         (FMOD_SPEAKERMODE speakermode);
        FMOD_RESULT F_API getSpeakerMode         (FMOD_SPEAKERMODE *speakermode);
                                                
        // Plug-in support                       
        FMOD_RESULT F_API setPluginPath          (const char *path);
        FMOD_RESULT F_API loadPlugin             (const char *filename, FMOD_PLUGINTYPE *plugintype, int *index);
        FMOD_RESULT F_API getNumPlugins          (FMOD_PLUGINTYPE plugintype, int *numplugins);
        FMOD_RESULT F_API getPluginInfo          (FMOD_PLUGINTYPE plugintype, int index, char *name, int namelen, unsigned int *version);
        FMOD_RESULT F_API unloadPlugin           (FMOD_PLUGINTYPE plugintype, int index);
        FMOD_RESULT F_API setOutputByPlugin      (int index);
        FMOD_RESULT F_API getOutputByPlugin      (int *index);
                                                 
        // Init/Close                            
        FMOD_RESULT F_API init                   (int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
        FMOD_RESULT F_API close                  ();
                                                 
        // General post-init system functions    
        FMOD_RESULT F_API update                 ();        /* IMPORTANT! CALL THIS ONCE PER FRAME! */
        FMOD_RESULT F_API updateFinished         ();        /* PlayStation 2 only.  Call this after System::update. */
                                                 
        FMOD_RESULT F_API set3DSettings          (float dopplerscale, float distancefactor, float rolloffscale);
        FMOD_RESULT F_API get3DSettings          (float *dopplerscale, float *distancefactor, float *rolloffscale);
        FMOD_RESULT F_API set3DNumListeners      (int numlisteners);
        FMOD_RESULT F_API get3DNumListeners      (int *numlisteners);
        FMOD_RESULT F_API set3DListenerAttributes(int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
        FMOD_RESULT F_API get3DListenerAttributes(int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);

        FMOD_RESULT F_API setSpeakerPosition     (FMOD_SPEAKER speaker, float x, float y);
        FMOD_RESULT F_API getSpeakerPosition     (FMOD_SPEAKER speaker, float *x, float *y);
        FMOD_RESULT F_API setStreamBufferSize    (unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
        FMOD_RESULT F_API getStreamBufferSize    (unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);
                                                
        // System information functions.        
        FMOD_RESULT F_API getVersion             (unsigned int *version);
        FMOD_RESULT F_API getOutputHandle        (void **handle);
        FMOD_RESULT F_API getChannelsPlaying     (int *channels);
        FMOD_RESULT F_API getCPUUsage            (float *dsp, float *stream, float *update, float *total);
        FMOD_RESULT F_API getSoundRAM            (int *currentalloced, int *maxalloced, int *total);
        FMOD_RESULT F_API getNumCDROMDrives      (int *numdrives);
        FMOD_RESULT F_API getCDROMDriveName      (int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen);
        FMOD_RESULT F_API getSpectrum            (float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
        FMOD_RESULT F_API getWaveData            (float *wavearray, int numvalues, int channeloffset);
                                                
        // Sound/DSP/Channel/FX creation and retrieval.       
        FMOD_RESULT F_API createSound            (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, Sound **sound);
        FMOD_RESULT F_API createStream           (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, Sound **sound);
        FMOD_RESULT F_API createDSP              (FMOD_DSP_DESCRIPTION *description, DSP **dsp);
        FMOD_RESULT F_API createDSPByType        (FMOD_DSP_TYPE type, DSP **dsp);
        FMOD_RESULT F_API createDSPByIndex       (int index, DSP **dsp);
        FMOD_RESULT F_API createChannelGroup     (const char *name, ChannelGroup **channelgroup);
                                                
        FMOD_RESULT F_API playSound              (FMOD_CHANNELINDEX channelid, Sound *sound, bool paused, Channel **channel);
        FMOD_RESULT F_API playDSP                (FMOD_CHANNELINDEX channelid, DSP *dsp, bool paused, Channel **channel);
        FMOD_RESULT F_API getChannel             (int channelid, Channel **channel);
        FMOD_RESULT F_API getMasterChannelGroup  (ChannelGroup **channelgroup);
                                               
        // Reverb API                           
        FMOD_RESULT F_API setReverbProperties    (const FMOD_REVERB_PROPERTIES *prop);
        FMOD_RESULT F_API getReverbProperties    (FMOD_REVERB_PROPERTIES *prop);
                                                  
        // System level DSP access.
        FMOD_RESULT F_API getDSPHead             (DSP **dsp);
        FMOD_RESULT F_API addDSP                 (DSP *dsp);
        FMOD_RESULT F_API lockDSP                ();
        FMOD_RESULT F_API unlockDSP              ();
                                               
        // Recording API.
        FMOD_RESULT F_API setRecordDriver        (int driver);
        FMOD_RESULT F_API getRecordDriver        (int *driver);
        FMOD_RESULT F_API getRecordNumDrivers    (int *numdrivers);
        FMOD_RESULT F_API getRecordDriverName    (int id, char *name, int namelen);
        FMOD_RESULT F_API getRecordPosition      (unsigned int *position);  

        FMOD_RESULT F_API recordStart            (Sound *sound, bool loop);
        FMOD_RESULT F_API recordStop             ();
        FMOD_RESULT F_API isRecording            (bool *recording);

        // Geometry API.
        FMOD_RESULT F_API createGeometry         (int maxpolygons, int maxvertices, Geometry **geometry);
        FMOD_RESULT F_API setGeometrySettings    (float maxworldsize);
        FMOD_RESULT F_API getGeometrySettings    (float *maxworldsize);
        FMOD_RESULT F_API loadGeometry           (const void *data, int datasize, Geometry **geometry);

        // Network functions.
        FMOD_RESULT F_API setNetworkProxy        (const char *proxy);
        FMOD_RESULT F_API getNetworkProxy        (char *proxy, int proxylen);
        FMOD_RESULT F_API setNetworkTimeout      (int timeout);
        FMOD_RESULT F_API getNetworkTimeout      (int *timeout);
                                               
        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };

    /*
        'Sound' API
    */
    class Sound
    {
      private:

        Sound();   /* Constructor made private so user cannot statically instance a Sound class.
                      Appropriate Sound creation or retrieval function must be used. */
      public:

        FMOD_RESULT F_API release                ();
        FMOD_RESULT F_API getSystemObject        (System **system);

        // Standard sound manipulation functions.                                                
        FMOD_RESULT F_API lock                   (unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
        FMOD_RESULT F_API unlock                 (void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
        FMOD_RESULT F_API setDefaults            (float frequency, float volume, float pan, int priority);
        FMOD_RESULT F_API getDefaults            (float *frequency, float *volume, float *pan,  int *priority);
        FMOD_RESULT F_API setVariations          (float frequencyvar, float volumevar, float panvar);
        FMOD_RESULT F_API getVariations          (float *frequencyvar, float *volumevar, float *panvar);
        FMOD_RESULT F_API set3DMinMaxDistance    (float min, float max);
        FMOD_RESULT F_API get3DMinMaxDistance    (float *min, float *max);
        FMOD_RESULT F_API set3DConeSettings      (float insideconeangle, float outsideconeangle, float outsidevolume);
        FMOD_RESULT F_API get3DConeSettings      (float *insideconeangle, float *outsideconeangle, float *outsidevolume);
        FMOD_RESULT F_API set3DCustomRolloff     (FMOD_VECTOR *points, int numpoints);
        FMOD_RESULT F_API get3DCustomRolloff     (FMOD_VECTOR **points, int *numpoints);
        FMOD_RESULT F_API setSubSound            (int index, Sound *subsound);
        FMOD_RESULT F_API getSubSound            (int index, Sound **subsound);
        FMOD_RESULT F_API setSubSoundSentence    (int *subsoundlist, int numsubsounds);
        FMOD_RESULT F_API getName                (char *name, int namelen);
        FMOD_RESULT F_API getLength              (unsigned int *length, FMOD_TIMEUNIT lengthtype);
        FMOD_RESULT F_API getFormat              (FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
        FMOD_RESULT F_API getNumSubSounds        (int *numsubsounds);
        FMOD_RESULT F_API getNumTags             (int *numtags, int *numtagsupdated);
        FMOD_RESULT F_API getTag                 (const char *name, int index, FMOD_TAG *tag);
        FMOD_RESULT F_API getOpenState           (FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, bool *starving);
        FMOD_RESULT F_API readData               (void *buffer, unsigned int lenbytes, unsigned int *read);
        FMOD_RESULT F_API seekData               (unsigned int pcm);

        // Synchronization point API.  These points can come from markers embedded in wav files, and can also generate channel callbacks.        
        FMOD_RESULT F_API getNumSyncPoints       (int *numsyncpoints);
        FMOD_RESULT F_API getSyncPoint           (int index, FMOD_SYNCPOINT **point);
        FMOD_RESULT F_API getSyncPointInfo       (FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
        FMOD_RESULT F_API addSyncPoint           (unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
        FMOD_RESULT F_API deleteSyncPoint        (FMOD_SYNCPOINT *point);

        // Functions also in Channel class but here they are the 'default' to save having to change it in Channel all the time.
        FMOD_RESULT F_API setMode                (FMOD_MODE mode);
        FMOD_RESULT F_API getMode                (FMOD_MODE *mode);
        FMOD_RESULT F_API setLoopCount           (int loopcount);
        FMOD_RESULT F_API getLoopCount           (int *loopcount);
        FMOD_RESULT F_API setLoopPoints          (unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
        FMOD_RESULT F_API getLoopPoints          (unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);
                            
        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };

    /*
        'Channel' API.
    */ 
    class Channel
    {
      private:

        Channel();   /* Constructor made private so user cannot statically instance a Channel class.  
                        Appropriate Channel creation or retrieval function must be used. */
      public:

        FMOD_RESULT F_API getSystemObject        (System **system);

        FMOD_RESULT F_API stop                   ();
        FMOD_RESULT F_API setPaused              (bool paused);
        FMOD_RESULT F_API getPaused              (bool *paused);
        FMOD_RESULT F_API setVolume              (float volume);
        FMOD_RESULT F_API getVolume              (float *volume);
        FMOD_RESULT F_API setFrequency           (float frequency);
        FMOD_RESULT F_API getFrequency           (float *frequency);
        FMOD_RESULT F_API setPan                 (float pan);
        FMOD_RESULT F_API getPan                 (float *pan);
        FMOD_RESULT F_API setDelay               (unsigned int startdelay, unsigned int enddelay);
        FMOD_RESULT F_API getDelay               (unsigned int *startdelay, unsigned int *enddelay);
        FMOD_RESULT F_API setSpeakerMix          (float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
        FMOD_RESULT F_API getSpeakerMix          (float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright);
        FMOD_RESULT F_API setSpeakerLevels       (FMOD_SPEAKER speaker, float *levels, int numlevels);
        FMOD_RESULT F_API getSpeakerLevels       (FMOD_SPEAKER speaker, float *levels, int numlevels);
        FMOD_RESULT F_API setMute                (bool mute);
        FMOD_RESULT F_API getMute                (bool *mute);
        FMOD_RESULT F_API setPriority            (int priority);
        FMOD_RESULT F_API getPriority            (int *priority);
        FMOD_RESULT F_API setPosition            (unsigned int position, FMOD_TIMEUNIT postype);
        FMOD_RESULT F_API getPosition            (unsigned int *position, FMOD_TIMEUNIT postype);
        FMOD_RESULT F_API setReverbProperties    (const FMOD_REVERB_CHANNELPROPERTIES *prop);
        FMOD_RESULT F_API getReverbProperties    (FMOD_REVERB_CHANNELPROPERTIES *prop);
        FMOD_RESULT F_API setChannelGroup        (ChannelGroup *channelgroup);
        FMOD_RESULT F_API getChannelGroup        (ChannelGroup **channelgroup);
        FMOD_RESULT F_API setCallback            (FMOD_CHANNEL_CALLBACKTYPE type, FMOD_CHANNEL_CALLBACK callback, int command);

        // 3D functionality.
        FMOD_RESULT F_API set3DAttributes        (const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
        FMOD_RESULT F_API get3DAttributes        (FMOD_VECTOR *pos, FMOD_VECTOR *vel);
        FMOD_RESULT F_API set3DMinMaxDistance    (float mindistance, float maxdistance);
        FMOD_RESULT F_API get3DMinMaxDistance    (float *mindistance, float *maxdistance);
        FMOD_RESULT F_API set3DConeSettings      (float insideconeangle, float outsideconeangle, float outsidevolume);
        FMOD_RESULT F_API get3DConeSettings      (float *insideconeangle, float *outsideconeangle, float *outsidevolume);
        FMOD_RESULT F_API set3DConeOrientation   (FMOD_VECTOR *orientation);
        FMOD_RESULT F_API get3DConeOrientation   (FMOD_VECTOR *orientation);
        FMOD_RESULT F_API set3DCustomRolloff     (FMOD_VECTOR *points, int numpoints);
        FMOD_RESULT F_API get3DCustomRolloff     (FMOD_VECTOR **points, int *numpoints);
        FMOD_RESULT F_API set3DOcclusion         (float directocclusion, float reverbocclusion);
        FMOD_RESULT F_API get3DOcclusion         (float *directocclusion, float *reverbocclusion);
        FMOD_RESULT F_API set3DSubChannelOffset  (int subchannel, FMOD_VECTOR *offset);
        FMOD_RESULT F_API get3DSubChannelOffset  (int subchannel, FMOD_VECTOR *offset);

        // DSP functionality only for channels playing sounds created with FMOD_SOFTWARE.
        FMOD_RESULT F_API getDSPHead             (DSP **dsp);
        FMOD_RESULT F_API addDSP                 (DSP *dsp);

        // Information only functions.
        FMOD_RESULT F_API isPlaying              (bool *isplaying);
        FMOD_RESULT F_API isVirtual              (bool *isvirtual);
        FMOD_RESULT F_API getAudibility          (float *audibility);
        FMOD_RESULT F_API getCurrentSound        (Sound **sound);
        FMOD_RESULT F_API getSpectrum            (float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
        FMOD_RESULT F_API getWaveData            (float *wavearray, int numvalues, int channeloffset);
        FMOD_RESULT F_API getIndex               (int *index);
                                                
        // Functions also found in Sound class but here they can be set per channel.
        FMOD_RESULT F_API setMode                (FMOD_MODE mode);
        FMOD_RESULT F_API getMode                (FMOD_MODE *mode);
        FMOD_RESULT F_API setLoopCount           (int loopcount);
        FMOD_RESULT F_API getLoopCount           (int *loopcount);
        FMOD_RESULT F_API setLoopPoints          (unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
        FMOD_RESULT F_API getLoopPoints          (unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

        // Userdata set/get.                                                
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };

    /*
        'ChannelGroup' API
    */
    class ChannelGroup
    {
      private:

        ChannelGroup();   /* Constructor made private so user cannot statically instance a ChannelGroup class.  
                             Appropriate ChannelGroup creation or retrieval function must be used. */
      public:

        FMOD_RESULT F_API release                 ();
        FMOD_RESULT F_API getSystemObject         (System **system);

        // Channelgroup scale values.  (changes attributes relative to the channels, doesn't overwrite them)
        FMOD_RESULT F_API setVolume               (float volume);
        FMOD_RESULT F_API getVolume               (float *volume);
        FMOD_RESULT F_API setPitch                (float pitch);
        FMOD_RESULT F_API getPitch                (float *pitch);

        // Channelgroup override values.  (recursively overwrites whatever settings the channels had)
        FMOD_RESULT F_API stop                    ();
        FMOD_RESULT F_API overridePaused          (bool paused);
        FMOD_RESULT F_API overrideVolume          (float volume);
        FMOD_RESULT F_API overrideFrequency       (float frequency);
        FMOD_RESULT F_API overridePan             (float pan);
        FMOD_RESULT F_API overrideMute            (bool mute);
        FMOD_RESULT F_API overrideReverbProperties(const FMOD_REVERB_CHANNELPROPERTIES *prop);
        FMOD_RESULT F_API override3DAttributes    (const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
        FMOD_RESULT F_API overrideSpeakerMix      (float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);

        // Nested channel groups.
        FMOD_RESULT F_API addGroup                (ChannelGroup *group);
        FMOD_RESULT F_API getNumGroups            (int *numgroups);
        FMOD_RESULT F_API getGroup                (int index, ChannelGroup **group);

        // DSP functionality only for channel groups playing sounds created with FMOD_SOFTWARE.
        FMOD_RESULT F_API getDSPHead              (DSP **dsp);
        FMOD_RESULT F_API addDSP                  (DSP *dsp);

        // Information only functions.
        FMOD_RESULT F_API getName                 (char *name, int namelen);
        FMOD_RESULT F_API getNumChannels          (int *numchannels);
        FMOD_RESULT F_API getChannel              (int index, Channel **channel);
        FMOD_RESULT F_API getSpectrum             (float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
        FMOD_RESULT F_API getWaveData             (float *wavearray, int numvalues, int channeloffset);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData             (void *userdata);
        FMOD_RESULT F_API getUserData             (void **userdata);
    };

    /*
        'DSP' API
    */
    class DSP
    {
      private:

        DSP();   /* Constructor made private so user cannot statically instance a DSP class.  
                    Appropriate DSP creation or retrieval function must be used. */
      public:

        FMOD_RESULT F_API release                ();
        FMOD_RESULT F_API getSystemObject        (System **system);

        // Connection / disconnection / input and output enumeration.
        FMOD_RESULT F_API addInput               (DSP *target);
        FMOD_RESULT F_API disconnectFrom         (DSP *target);
        FMOD_RESULT F_API remove                 ();
        FMOD_RESULT F_API getNumInputs           (int *numinputs);
        FMOD_RESULT F_API getNumOutputs          (int *numoutputs);
        FMOD_RESULT F_API getInput               (int index, DSP **input);
        FMOD_RESULT F_API getOutput              (int index, DSP **output);
        FMOD_RESULT F_API setInputMix            (int index, float volume);
        FMOD_RESULT F_API getInputMix            (int index, float *volume);
        FMOD_RESULT F_API setInputLevels         (int index, FMOD_SPEAKER speaker, float *levels, int numlevels);
        FMOD_RESULT F_API getInputLevels         (int index, FMOD_SPEAKER speaker, float *levels, int numlevels);

        // DSP unit control.
        FMOD_RESULT F_API setActive              (bool active);
        FMOD_RESULT F_API getActive              (bool *active);
        FMOD_RESULT F_API setBypass              (bool bypass);
        FMOD_RESULT F_API getBypass              (bool *bypass);
        FMOD_RESULT F_API reset                  ();

        // DSP parameter control.
        FMOD_RESULT F_API setParameter           (int index, float value);
        FMOD_RESULT F_API getParameter           (int index, float *value, char *valuestr, int valuestrlen);
        FMOD_RESULT F_API getNumParameters       (int *numparams);
        FMOD_RESULT F_API getParameterInfo       (int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max);
        FMOD_RESULT F_API showConfigDialog       (void *hwnd, bool show);
        
        // DSP attributes.        
        FMOD_RESULT F_API getInfo                (char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
        FMOD_RESULT F_API setDefaults            (float frequency, float volume, float pan, int priority);
        FMOD_RESULT F_API getDefaults            (float *frequency, float *volume, float *pan, int *priority);
                                                
        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };


    /*
        'Geometry' API
    */
    class Geometry
    {
      private:

        Geometry();   /* Constructor made private so user cannot statically instance a Geometry class.  
                         Appropriate Geometry creation or retrieval function must be used. */

      public:        

        FMOD_RESULT F_API release                ();

        /*
            Polygon manipulation.
        */
        FMOD_RESULT F_API addPolygon             (float directocclusion, float reverbocclusion, bool doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex);
        FMOD_RESULT F_API getNumPolygons         (int *numpolygons); 
        FMOD_RESULT F_API getMaxPolygons         (int *maxpolygons, int *maxvertices);
        FMOD_RESULT F_API getPolygonNumVertices  (int index, int *numvertices);
        FMOD_RESULT F_API setPolygonVertex       (int index, int vertexindex, const FMOD_VECTOR *vertex); 
        FMOD_RESULT F_API getPolygonVertex       (int index, int vertexindex, FMOD_VECTOR *vertex);
        FMOD_RESULT F_API setPolygonAttributes   (int index, float directocclusion, float reverbocclusion, bool doublesided); 
        FMOD_RESULT F_API getPolygonAttributes   (int index, float *directocclusion, float *reverbocclusion, bool *doublesided); 

        /*
            Object manipulation.
        */
        FMOD_RESULT F_API setActive              (bool active);                                                 
        FMOD_RESULT F_API getActive              (bool *active);                                                 
        FMOD_RESULT F_API setRotation            (const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
        FMOD_RESULT F_API getRotation            (FMOD_VECTOR *forward, FMOD_VECTOR *up);
        FMOD_RESULT F_API setPosition            (const FMOD_VECTOR *position);
        FMOD_RESULT F_API getPosition            (FMOD_VECTOR *position);
        FMOD_RESULT F_API setScale               (const FMOD_VECTOR *scale);
        FMOD_RESULT F_API getScale               (FMOD_VECTOR *scale);
        FMOD_RESULT F_API save                   (void *data, int *datasize);

        // Userdata set/get.
        FMOD_RESULT F_API setUserData            (void *userdata);
        FMOD_RESULT F_API getUserData            (void **userdata);
    };
};

#endif
