// ProsperoEden - Launcher colours, type sizes and motion constants.
// Copyright (C) 2026 BlackBearReloaded
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "pe/gfx/draw_list.hpp"

#include <algorithm>

namespace pe::ui
{

using gfx::Align;
using gfx::Color;
using gfx::Rect;

namespace theme
{

// Backgrounds
inline const Color kBase = Color::rgb(0x071225);
inline const Color kScrim = Color::rgb(0x030a16);
inline const Color kGlass = Color::rgb(0x102844);  // home panels
inline const Color kPanel = Color::rgb(0x0a1b32);  // screens and dialogs
inline const Color kPanelEdge = Color::rgb(0x517ca6);
inline const Color kRow = Color::rgb(0x132d4b);
inline const Color kRowEdge = Color::rgb(0x456f98);
inline const Color kRowFocus = Color::rgb(0x225082);

// The accent: sky blue to deep blue, left to right.
inline const Color kLime = Color::rgb(0x65c6ff);
inline const Color kLimeDeep = Color::rgb(0x2052a3);
inline const Color kLimePale = Color::rgb(0xc2e9ff);
inline const Color kSun = Color::rgb(0x79ddff);

// Text
inline const Color kText = Color::rgb(0xf1f8ff);
inline const Color kTitle = Color::rgb(0xffffff);
inline const Color kValue = Color::rgb(0xeaf6ff);
inline const Color kBody = Color::rgb(0xdcecff);
inline const Color kCopy = Color::rgb(0xbbd4ef);
inline const Color kMeta = Color::rgb(0xadc8e6);
inline const Color kLabel = Color::rgb(0xa2bddb);
inline const Color kMuted = Color::rgb(0x9eb8d6);
inline const Color kFaint = Color::rgb(0x829cbb);
inline const Color kWarning = Color::rgb(0xe8b39a);
inline const Color kRule = Color::rgb(0x38597a);

// Type sizes (Montserrat Medium)
constexpr float kDisplay = 48.0f;
constexpr float kLead = 40.0f;
constexpr float kBrand = 36.0f;
constexpr float kHeading = 32.0f;
constexpr float kClock = 28.0f;
constexpr float kText24 = 24.0f;
constexpr float kSmall = 20.0f;

// Motion (spring responsiveness in rad/s, durations in seconds)
constexpr float kFocusSpring = 20.0f;
constexpr float kCursorSpring = 26.0f;
constexpr float kScrollSpring = 16.0f;
constexpr float kScreenSeconds = 0.30f;
constexpr float kLaunchSeconds = 0.95f;

} // namespace theme

// How the launcher is shown: Settings > Accessibility.
struct Look
{
    bool large_text = false;    // small text is drawn larger
    bool high_contrast = false; // solid panels, brighter text, an outlined highlight
    bool reduce_motion = false; // nothing drifts, slides or zooms: screens fade
};
inline Look &look()
{
    static Look value;
    return value;
}
// 1 normally, 0 with reduced motion: every slide, zoom and drift is multiplied by it.
inline float motion()
{
    return look().reduce_motion ? 0.0f : 1.0f;
}
// The size text of `size` is drawn at. "Larger text" raises everything under 30 to between 26
// and 30 (26 is the least the console accessibility guidelines ask of text on a 1080p TV).
inline float text_size(float size)
{
    return look().large_text && size < 30.0f ? std::clamp(size * 1.3f, 26.0f, 30.0f) : size;
}

// The baseline that centres text of `size` in a line box of height `line` starting at `top`.
inline float baseline(float top, float line, float size)
{
    return top + line * 0.5f + size * 0.35f;
}

inline bool inside(const Rect &r, float x, float y)
{
    return x >= r.x && y >= r.y && x < r.x + r.w && y < r.y + r.h;
}

} // namespace pe::ui
