/**
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU 
 * General Public License as published by the Free Software Foundation, either version 3 of the License, 
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see 
 * <https://www.gnu.org/licenses/>.
 */

#ifndef __MAT_SWITCH_WITH_COVER_2_POS_H__
#define __MAT_SWITCH_WITH_COVER_2_POS_H__

#include <DcsBios.h>

/**
 * This is a modified version of DcsBios::SwitchWithCover2Pos that reads its input from an input
 * matrix.
 */
template <unsigned long pollIntervalMs = POLL_EVERY_TIME, unsigned long coverDelayMs = 200>
class MatSwitchWithCover2PosT : DcsBios::PollingInput, public DcsBios::ResettableInput {
private:
    const char* switchMsg_;
    const char* coverMsg_;
    
    volatile unsigned char* address_;
    
    char lastState_;
    char switchState_;
    bool reverse_;
    
    unsigned long debounceDelay_;
    unsigned long lastDebounceTime = 0;

    enum SwitchCoverStateEnum {
        stOFF_CLOSED = 0,
        stOFF_OPEN = 1,
        stON_OPEN = 2
    };

    SwitchCoverStateEnum switchCoverState_;
    unsigned long lastSwitchStateTime;

    char readState() {
        return *address_;
    }

    void resetState()
    {
        lastState_ = (lastState_==0)?-1:0;

        if (switchState_ && !reverse_) {
            switchCoverState_ = stOFF_CLOSED;
        } else {
            switchCoverState_ = stON_OPEN;
        }
        lastSwitchStateTime = millis();
    }

    void pollInput() {
        char state = readState();
        if (reverse_) { 
            state = !state;
        }
        if (state != lastState_) {
            lastDebounceTime = millis();
        }
        
        if (state != switchState_ && (millis() - lastDebounceTime) > debounceDelay_) {
            // Switch has debounced and changed state
            if(millis() - lastSwitchStateTime > coverDelayMs) {
                // Switch/cover delay has been satisfied.
                if (state) {
                    // Closing/turning off
                    switch(switchCoverState_) {
                        case stON_OPEN:
                            if (DcsBios::tryToSendDcsBiosMessage(switchMsg_, "0")) {
                                switchCoverState_ = stOFF_OPEN;
                                lastSwitchStateTime = millis();
                            }
                            break;

                        case stOFF_OPEN:
                            if (DcsBios::tryToSendDcsBiosMessage(coverMsg_, "0")) {
                                switchCoverState_ = stOFF_CLOSED;
                                lastSwitchStateTime = millis();
                                switchState_ = state;
                            }
                            break;
                            
                        case stOFF_CLOSED:
                            // Converged on steady state.  Good.
                            break;
                    }
                } else {
                    // Opening/turning on
                    switch(switchCoverState_) {
                        case stOFF_CLOSED:
                            if (DcsBios::tryToSendDcsBiosMessage(coverMsg_, "1")) {
                                switchCoverState_ = stOFF_OPEN;
                                lastSwitchStateTime = millis();
                            }
                            break;

                        case stOFF_OPEN:
                            if (DcsBios::tryToSendDcsBiosMessage(switchMsg_, "1")) {
                                switchCoverState_ = stON_OPEN;
                                lastSwitchStateTime = millis();
                                switchState_ = state;
                            }
                            break;

                        case stON_OPEN:
                            // Converged on steady state.  Good.
                            break;

                    }
                }
            }
        }

        lastState_ = state;
    }

public:
    MatSwitchWithCover2PosT(const char* switchMessage, const char* coverMessage, volatile unsigned char* address, bool reverse = false, unsigned long debounceDelay = 50) :
        PollingInput(pollIntervalMs)
    { 
        switchMsg_ = switchMessage;
        coverMsg_ = coverMessage;
        address_ = address;        
        switchState_ = readState();
        lastState_ = switchState_;
        reverse_ = reverse;
        debounceDelay_ = debounceDelay;

        resetState();
    }

    void resetThisState()
    {
        this->resetState();
    }
};
typedef MatSwitchWithCover2PosT<> MatSwitchWithCover2Pos;

#endif