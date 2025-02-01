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

#ifndef __MAT_SWITCH_3_POS_H__
#define __MAT_SWITCH_3_POS_H__

#include <DcsBios.h>

/**
 * This is a modified version of DcsBios::Switch3Pos that reads its input from an input
 * matrix. It is also modified to use active HIGH.
 */
template <unsigned long pollIntervalMs = POLL_EVERY_TIME>
class MatSwitch3PosT : DcsBios::PollingInput, public DcsBios::ResettableInput {
    private:
        const char* msg_;

        volatile unsigned char* downPosAddress;
        volatile unsigned char* upPosAddress;

        char lastState_;
        char switchState_;
        char debounceSteadyState_;

        unsigned long debounceDelay_;
        unsigned long lastDebounceTime = 0;

        char readState() {
            if (*downPosAddress == HIGH) return 0;
            if (*upPosAddress == HIGH) return 2;
            return 1;
        }

        void resetState() {
            lastState_ = (lastState_ == 0) ? -1 : 0;
        }

        void pollInput() {
            char state = readState();

            unsigned long now = millis();
            if (state != debounceSteadyState_) {
                lastDebounceTime = now;
                debounceSteadyState_ = state;
            }

            if ((now - lastDebounceTime) >= debounceDelay_) {
                if (state != lastState_) {
                    switch (state) {
                        case 0:
                            while (!DcsBios::tryToSendDcsBiosMessage(msg_, "0")); 
                            break;
                        case 1: 
                            while (!DcsBios::tryToSendDcsBiosMessage(msg_, "1")); 
                            break;
                        case 2:
                            while (!DcsBios::tryToSendDcsBiosMessage(msg_, "2")); 
                            break;
                    }

                    lastState_ = state;
                }
            }
        }

    public:
        MatSwitch3PosT(const char* msg, volatile unsigned char* argDownPosAddress, volatile unsigned char* argUpPosAddress, unsigned long debounceDelay = 50) :
            PollingInput(pollIntervalMs)
        {
            msg_ = msg;
            downPosAddress = argDownPosAddress;
            upPosAddress = argUpPosAddress;
            
            lastState_ = readState();
            debounceSteadyState_ = lastState_;
            debounceDelay_ = debounceDelay;
        }

        void resetThisState() {
            this->resetState();
        }
};
typedef MatSwitch3PosT<> MatSwitch3Pos;

#endif
