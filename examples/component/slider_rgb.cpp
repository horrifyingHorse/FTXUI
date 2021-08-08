#include <memory>  // for allocator, shared_ptr, __shared_ptr_access
#include <string>  // for char_traits, operator+, to_wstring

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/deprecated.hpp"                // for text
#include "ftxui/dom/elements.hpp"  // for separator, operator|, Element, size, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color

using namespace ftxui;

Element ColorTile(int red, int green, int blue) {
  return text(L"") | size(WIDTH, GREATER_THAN, 14) |
         size(HEIGHT, GREATER_THAN, 7) | bgcolor(Color::RGB(red, green, blue));
}

Element ColorString(int red, int green, int blue) {
  return text(L"RGB = (" +                     //
              std::to_wstring(red) + L"," +    //
              std::to_wstring(green) + L"," +  //
              std::to_wstring(blue) + L")"     //
  );
}

int main(int argc, const char* argv[]) {
  int red = 128;
  int green = 25;
  int blue = 100;
  auto slider_red = Slider(L"Red  :", &red, 0, 255, 1);
  auto slider_green = Slider(L"Green:", &green, 0, 255, 1);
  auto slider_blue = Slider(L"Blue :", &blue, 0, 255, 1);

  auto container = Container::Vertical({
      slider_red,
      slider_green,
      slider_blue,
  });

  auto renderer = Renderer(container, [&] {
    return hbox({
               ColorTile(red, green, blue),
               separator(),
               vbox({
                   slider_red->Render(),
                   separator(),
                   slider_green->Render(),
                   separator(),
                   slider_blue->Render(),
                   separator(),
                   ColorString(red, green, blue),
               }) | xflex,
           }) |
           border | size(WIDTH, LESS_THAN, 80);
  });
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
