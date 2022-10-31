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

#include "kaleidoscope/plugin/LEDEffect-FocusColor.h"

#include "kaleidoscope/KeyAddr.h"            // for KeyAddr
#include "kaleidoscope/device/device.h"      // for CRGB
#include "kaleidoscope/plugin/LEDControl.h"  // for LEDControl
#include "plugins/Kaleidoscope-FocusSerial/src/Kaleidoscope-FocusSerial.h"

namespace kaleidoscope {
namespace plugin {

EventHandlerResult LEDFocusColor::onNameQuery()
{
  return ::Focus.sendName(F("FocusTestCommand"));
}

EventHandlerResult LEDFocusColor::onFocusEvent(const char *input)
{
  const char *colorCmd = PSTR("led.color");

  if (::Focus.inputMatchesHelp(input))
    return ::Focus.printHelp(colorCmd);

  if (!::Focus.inputMatchesCommand(input, colorCmd))
    return EventHandlerResult::OK;

  cRGB color;
  if (::Focus.isEOL()) {
    color.r = this->r_;
    color.g = this->g_;
    color.b = this->b_;
    ::Focus.send(color);
  } else {
    Focus.read(color);
    this->r_ = color.r;
    this->g_ = color.g;
    this->b_ = color.b;
  }
  return EventHandlerResult::EVENT_CONSUMED;
}

void LEDFocusColor::TransientLEDMode::onActivate() {
  ::LEDControl.set_all_leds_to(parent_->r_,
                               parent_->g_,
                               parent_->b_);
}

void LEDFocusColor::TransientLEDMode::refreshAt(KeyAddr key_addr) {
  ::LEDControl.setCrgbAt(key_addr,
                         CRGB(parent_->r_,
                              parent_->g_,
                              parent_->b_));
}

}  // namespace plugin
}  // namespace kaleidoscope
