/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _ThresholdLib_h
#define _ThresholdLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

typedef  void(*ThresholdAction)();

template <typename T>
class Threshold
{
public:
	Threshold<T>(T threshold) : Threshold<T>(threshold, threshold, false) {}
	Threshold<T>(T threshold, bool state) : Threshold<T>(threshold, threshold, state) {}
	Threshold<T>(T lowThreshold, T highThreshold) : Threshold<T>(lowThreshold, highThreshold, false) {}
	Threshold<T>(T lowThreshold, T highThreshold, bool state);

	bool GetState() const;
	bool AddValue(T);

	T FallThreshold;
	T RiseThreshold;

	ThresholdAction OnChange;
	ThresholdAction OnRising;
	ThresholdAction OnFalling;

private:
	bool _state;
};


#endif

template<typename T>
Threshold<T>::Threshold(T threshold1, T threshold2, bool state)
{
	FallThreshold = threshold1 <= threshold2 ? threshold1 : threshold2;
	RiseThreshold = threshold1 > threshold2 ? threshold1 : threshold2;
	_state = state;
	OnChange = nullptr;
	OnFalling = nullptr;
	OnRising = nullptr;
}

template<typename T>
inline bool Threshold<T>::GetState() const
{
	return _state;
}

template<typename T>
inline bool Threshold<T>::AddValue(T value)
{
	if (_state == false && value > RiseThreshold)
	{
		_state = true;
		if (OnChange != nullptr) OnChange();
		if (OnRising != nullptr) OnRising();
	}
	
	if (_state == true && value < FallThreshold)
	{
		_state = false;
		if (OnChange != nullptr) OnChange();
		if (OnFalling != nullptr) OnFalling();
	}	
	return _state;
}
