/* Kaleidoscope-LEDEffect-FocusColor - Solid-color LED effect configurable via FocusSerial
 * Copyright (C) 2022  Ben Merritt et al.
 * Originally based on Kaleidoscope-LEDEffect-SolidColor 
 * Copyright (C) 2017  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>  // for uint8_t

#include "Kaleidoscope.h"
#include "kaleidoscope/KeyAddr.h"                  // for KeyAddr
#include "kaleidoscope/plugin.h"                   // for Plugin
#include "kaleidoscope/plugin/LEDMode.h"           // for LEDMode
#include "kaleidoscope/plugin/LEDModeInterface.h"  // for LEDModeInterface

namespace kaleidoscope {
namespace plugin {
class LEDFocusColor : public Plugin,
                      public LEDModeInterface {
 public:
  LEDFocusColor(uint8_t r, uint8_t g, uint8_t b)
    : r_(r), g_(g), b_(b) {}

  EventHandlerResult onNameQuery();
  EventHandlerResult onFocusEvent(const char *input);

  // This class' instance has dynamic lifetime
  //
  class TransientLEDMode : public LEDMode {
   public:
    explicit TransientLEDMode(const LEDFocusColor *parent)
      : parent_(parent) {}

   protected:
    void onActivate() final;
    void refreshAt(KeyAddr key_addr) final;

   private:
    const LEDFocusColor *parent_;
  };

 private:
  uint8_t r_, g_, b_;
};

}  // namespace plugin
}  // namespace kaleidoscope
