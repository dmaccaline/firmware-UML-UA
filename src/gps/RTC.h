#pragma once

#include "configuration.h"
#include "sys/time.h"
#include <Arduino.h>
#include "nanoSec.h"

enum RTCQuality {

    /// We haven't had our RTC set yet
    RTCQualityNone = 0,

    /// We got time from an onboard peripheral after boot.
    RTCQualityDevice = 1,

    /// Some other node gave us a time we can use
    RTCQualityFromNet = 2,

    /// Our time is based on NTP
    RTCQualityNTP = 3,

    /// Our time is based on our own GPS
    RTCQualityGPS = 4
};

RTCQuality getRTCQuality();

/// If we haven't yet set our RTC this boot, set it from a GPS derived time
bool perhapsSetRTC(RTCQuality q, const struct timeval *tv);
bool perhapsSetRTC(RTCQuality q, struct tm &t);

/// Return time since 1970 in secs.  While quality is RTCQualityNone we will be returning time based at zero
//Note, getTime() used in several places, with output value stored as uint32_t.  these may need updating depending on our needs
uint64_t getTime();

/// Return time since 1970 in secs.  If quality is RTCQualityNone return zero
//Note, getValidTime() used in several places, with output value stored as uint32_t.  these may need updating depending on our needs
uint64_t getValidTime(RTCQuality minQuality);

void readFromRTC();

#define SEC_PER_DAY 86400
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60