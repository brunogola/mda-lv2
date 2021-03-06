/*
  Copyright 2008-2011 David Robillard <http://drobilla.net>
  Copyright 1999-2000 Paul Kellett (Maxim Digital Audio)

  This is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License,
  or (at your option) any later version.

  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this software. If not, see <http://www.gnu.org/licenses/>.
*/

#define NPARAMS  8  ///number of parameters
#define NPROGS   5  ///number of programs
#define NBANDS  16  ///max vocoder bands

#ifndef __mdaVocoder_H
#define __mdaVocoder_H

#include "audioeffectx.h"


class mdaVocoderProgram
{
public:
  mdaVocoderProgram();
private:
  friend class mdaVocoder;
  float param[NPARAMS];
  char name[32];
};


class mdaVocoder : public AudioEffectX
{
public:
  mdaVocoder(audioMasterCallback audioMaster);
  ~mdaVocoder();

  virtual void  process(float **inputs, float **outputs, int32_t sampleFrames);
  virtual void  processReplacing(float **inputs, float **outputs, int32_t sampleFrames);
  virtual void  setProgram(int32_t program);
  virtual void  setProgramName(char *name);
  virtual void  getProgramName(char *name);
	virtual bool getProgramNameIndexed (int32_t category, int32_t index, char* name);
  virtual void  setParameter(int32_t index, float value);
  virtual float getParameter(int32_t index);
  virtual void  getParameterLabel(int32_t index, char *label);
  virtual void  getParameterDisplay(int32_t index, char *text);
  virtual void  getParameterName(int32_t index, char *text);
  virtual void  suspend();
  virtual void  resume();

	virtual bool getEffectName(char *name);
	virtual bool getVendorString(char *text);
	virtual bool getProductString(char *text);
	virtual int32_t getVendorVersion() { return 1000; }
  
protected:
  mdaVocoderProgram *programs;

  ///global internal variables
  int32_t  swap;       //input channel swap
  float gain;       //output level
  float thru, high; //hf thru              
  float kout; //downsampled output
  int32_t  kval; //downsample counter
  int32_t  nbnd; //number of bands
  
  //filter coeffs and buffers - seems it's faster to leave this global than make local copy 
  float f[NBANDS][13]; //[0-8][0 1 2 | 0 1 2 3 | 0 1 2 3 | val rate]
};                     //  #   reson | carrier |modulator| envelope

#endif
