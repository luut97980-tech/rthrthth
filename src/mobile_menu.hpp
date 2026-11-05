#pragma once
#ifndef VT_FEATURE_KEYS_R59_DEFINED
#define VT_FEATURE_KEYS_R59_DEFINED
namespace vt {
enum Feature {Esp,Line,SpamJump,AutoReady,AutoHammer,SpeedBoost,FeatureCount};
static_assert(FeatureCount==6);
}
#endif
#include "imgui.h"
#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
namespace vt::ios {
struct LicenseInfo {
    bool valid = false;
    std::string key;
    std::string token;
    std::string statusText = "Chưa kích hoạt key";
    std::int64_t expiresAt = 0;
    std::int64_t remainingSeconds = 0;
};
struct Model {
    bool visible = false, connected = false, controlsAllowed = false, suppressActions = false;
    bool sliderActive = false, showDetails = false;
    bool jumpPressed = false;
    ImVec2 jumpButtonPos{-1.f, -1.f};
    bool antiCapture = true; // Hides menu during screen recording & screenshot
    float scale = 1.f, opacity = .96f, scrollDelta = 0.f;
    std::array<bool, FeatureCount> enabled{}, available{};
    ImVec2 windowMin{}, windowMax{}, insetMin{}, insetMax{};
    ImVec2 speedWinMin{}, speedWinMax{}; // Bounds of floating Speed +/- 0.1 widget
    ImVec2 floatingButtonPos{-1.f, -1.f}; // Movable floating Menu button position
    ImVec2 prevFloatingButtonPos{-1.f, -1.f};
    ImVec2 speedWidgetPos{-1.f, -1.f};    // Movable floating Speed +/- 0.1 widget position
    ImVec2 prevSpeedWidgetPos{-1.f, -1.f};
    ImVec2 menuWindowPos{-1.f, -1.f};     // Movable main menu position
    ImVec2 prevMenuWindowPos{-1.f, -1.f};
    std::string toast, player; double time = 0, toastUntil = 0;
    double jumpIntervalMs = 20.;
    double hammerDelayMs = 0.;
    double moveSpeedMultiplier = 1.0;     // Character speed multiplier (step 0.1)
    bool showSpeedWidget = true;          // Show standalone floating Speed +/- 0.1 button bar
    ImVec2 contentMin{}, contentMax{};
    std::string status = "Chưa kết nối game", diagnostic = "PTG iOS R6.6 • Chưa kiểm tra runtime.";
    LicenseInfo license;
    char keyInput[64] = {};
};
struct Actions {
    std::function<void(int)> toggle;
    std::function<void(int, double)> number;
    std::function<void()> stop, save, diagnostic;
    std::function<void(const std::string&)> activateKey;
    std::function<void()> pasteKey;
    std::function<void()> clearKey;
    std::function<void()> promptKeyInput;
    std::function<void(bool)> toggleAntiCapture;
};
void sanitize(Model&);
void style();
void draw(Model&, const Actions&);
bool acceptsPoint(const Model&, ImVec2);
}
