#include "Keyframe.h"
#include <algorithm>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

namespace CreativeMode {

// Easing functions
static float easeLinear(float t) {
    return t;
}

static float easeInQuad(float t) {
    return t * t;
}

static float easeOutQuad(float t) {
    return 1.0f - (1.0f - t) * (1.0f - t);
}

static float easeInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 2.0f) / 2.0f;
}

static float easeInCubic(float t) {
    return t * t * t;
}

static float easeOutCubic(float t) {
    return 1.0f - std::pow(1.0f - t, 3.0f);
}

static float easeInOutCubic(float t) {
    return t < 0.5f ? 4.0f * t * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
}

static float easeInBack(float t) {
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;
    return c3 * t * t * t - c1 * t * t;
}

static float easeOutBack(float t) {
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;
    return 1.0f + c3 * std::pow(t - 1.0f, 3.0f) + c1 * std::pow(t - 1.0f, 2.0f);
}

static float easeInOutBack(float t) {
    const float c1 = 1.70158f;
    const float c2 = c1 * 1.525f;
    return t < 0.5f
        ? (std::pow(2.0f * t, 2.0f) * ((c2 + 1.0f) * 2.0f * t - c2)) / 2.0f
        : (std::pow(2.0f * t - 2.0f, 2.0f) * ((c2 + 1.0f) * (t * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
}

static float easeInElastic(float t) {
    const float c4 = (2.0f * 3.14159265359f) / 3.0f;
    return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : -std::pow(2.0f, 10.0f * t - 10.0f) * std::sin((t * 10.0f - 10.75f) * c4);
}

static float easeOutElastic(float t) {
    const float c4 = (2.0f * 3.14159265359f) / 3.0f;
    return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : std::pow(2.0f, -10.0f * t) * std::sin((t * 10.0f - 0.75f) * c4) + 1.0f;
}

static float easeInOutElastic(float t) {
    const float c5 = (2.0f * 3.14159265359f) / 4.5f;
    return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : t < 0.5f
        ? -(std::pow(2.0f, 20.0f * t - 10.0f) * std::sin((20.0f * t - 11.125f) * c5)) / 2.0f
        : (std::pow(2.0f, -20.0f * t + 10.0f) * std::sin((20.0f * t - 11.125f) * c5)) / 2.0f + 1.0f;
}

KeyframeTrack::KeyframeTrack(uint32_t objectId_) : objectId(objectId_) {}

KeyframeTrack::~KeyframeTrack() {
    deleteAllKeyframes();
}

Keyframe* KeyframeTrack::createKeyframe(double time) {
    // Verificar se já existe keyframe neste tempo
    auto it = std::find_if(keyframes.begin(), keyframes.end(),
        [time](const Keyframe& kf) { return std::abs(kf.time - time) < 0.001; });
    
    if (it != keyframes.end()) {
        return &(*it);
    }
    
    keyframes.emplace_back();
    Keyframe& newKf = keyframes.back();
    newKf.time = time;
    
    sort();
    
    return &keyframes[std::find_if(keyframes.begin(), keyframes.end(),
        [time](const Keyframe& kf) { return std::abs(kf.time - time) < 0.001; }) - keyframes.begin()];
}

void KeyframeTrack::deleteKeyframe(double time) {
    auto it = std::find_if(keyframes.begin(), keyframes.end(),
        [time](const Keyframe& kf) { return std::abs(kf.time - time) < 0.001; });
    
    if (it != keyframes.end()) {
        keyframes.erase(it);
    }
}

void KeyframeTrack::deleteAllKeyframes() {
    keyframes.clear();
}

Keyframe* KeyframeTrack::getKeyframe(double time) {
    auto it = std::find_if(keyframes.begin(), keyframes.end(),
        [time](const Keyframe& kf) { return std::abs(kf.time - time) < 0.001; });
    
    return it != keyframes.end() ? &(*it) : nullptr;
}

Keyframe* KeyframeTrack::getKeyframeAt(size_t index) {
    return index < keyframes.size() ? &keyframes[index] : nullptr;
}

Keyframe* KeyframeTrack::getPreviousKeyframe(double time) {
    Keyframe* result = nullptr;
    for (auto& kf : keyframes) {
        if (kf.time < time && (result == nullptr || kf.time > result->time)) {
            result = &kf;
        }
    }
    return result;
}

Keyframe* KeyframeTrack::getNextKeyframe(double time) {
    Keyframe* result = nullptr;
    for (auto& kf : keyframes) {
        if (kf.time > time && (result == nullptr || kf.time < result->time)) {
            result = &kf;
        }
    }
    return result;
}

Keyframe KeyframeTrack::interpolate(double time) const {
    if (keyframes.empty()) {
        return Keyframe();
    }
    
    // Encontrar keyframes anterior e próximo
    Keyframe result;
    result.time = time;
    
    auto nextIt = std::find_if(keyframes.begin(), keyframes.end(),
        [time](const Keyframe& kf) { return kf.time >= time; });
    
    if (nextIt == keyframes.begin()) {
        // Antes do primeiro keyframe
        result = keyframes.front();
        return result;
    }
    
    if (nextIt == keyframes.end()) {
        // Depois do último keyframe
        result = keyframes.back();
        return result;
    }
    
    auto prevIt = nextIt - 1;
    const Keyframe& prevKf = *prevIt;
    const Keyframe& nextKf = *nextIt;
    
    // Calcular t normalizado [0, 1]
    double duration = nextKf.time - prevKf.time;
    float t = static_cast<float>((time - prevKf.time) / duration);
    t = easeValue(t, nextKf.easingType);
    
    // Interpolar posição
    if (prevKf.bHasPosition && nextKf.bHasPosition) {
        result.position = glm::mix(prevKf.position, nextKf.position, t);
        result.bHasPosition = true;
    } else if (prevKf.bHasPosition) {
        result.position = prevKf.position;
        result.bHasPosition = true;
    } else if (nextKf.bHasPosition) {
        result.position = nextKf.position;
        result.bHasPosition = true;
    }
    
    // Interpolar rotação (slerp)
    if (prevKf.bHasRotation && nextKf.bHasRotation) {
        result.rotation = glm::slerp(prevKf.rotation, nextKf.rotation, t);
        result.bHasRotation = true;
    } else if (prevKf.bHasRotation) {
        result.rotation = prevKf.rotation;
        result.bHasRotation = true;
    } else if (nextKf.bHasRotation) {
        result.rotation = nextKf.rotation;
        result.bHasRotation = true;
    }
    
    // Interpolar escala
    if (prevKf.bHasScale && nextKf.bHasScale) {
        result.scale = glm::mix(prevKf.scale, nextKf.scale, t);
        result.bHasScale = true;
    } else if (prevKf.bHasScale) {
        result.scale = prevKf.scale;
        result.bHasScale = true;
    } else if (nextKf.bHasScale) {
        result.scale = nextKf.scale;
        result.bHasScale = true;
    }
    
    // Interpolar FOV
    if (prevKf.bHasFOV && nextKf.bHasFOV) {
        result.fov = glm::mix(prevKf.fov, nextKf.fov, t);
        result.bHasFOV = true;
    } else if (prevKf.bHasFOV) {
        result.fov = prevKf.fov;
        result.bHasFOV = true;
    } else if (nextKf.bHasFOV) {
        result.fov = nextKf.fov;
        result.bHasFOV = true;
    }
    
    return result;
}

double KeyframeTrack::getDuration() const {
    if (keyframes.empty()) return 0.0;
    return keyframes.back().time - keyframes.front().time;
}

double KeyframeTrack::getStartTime() const {
    return keyframes.empty() ? 0.0 : keyframes.front().time;
}

double KeyframeTrack::getEndTime() const {
    return keyframes.empty() ? 0.0 : keyframes.back().time;
}

void KeyframeTrack::sort() {
    std::sort(keyframes.begin(), keyframes.end(),
        [](const Keyframe& a, const Keyframe& b) { return a.time < b.time; });
}

float KeyframeTrack::easeValue(float t, EasingType type) const {
    switch (type) {
        case EasingType::LINEAR: return easeLinear(t);
        case EasingType::EASE_IN_QUAD: return easeInQuad(t);
        case EasingType::EASE_OUT_QUAD: return easeOutQuad(t);
        case EasingType::EASE_IN_OUT_QUAD: return easeInOutQuad(t);
        case EasingType::EASE_IN_CUBIC: return easeInCubic(t);
        case EasingType::EASE_OUT_CUBIC: return easeOutCubic(t);
        case EasingType::EASE_IN_OUT_CUBIC: return easeInOutCubic(t);
        case EasingType::EASE_IN_BACK: return easeInBack(t);
        case EasingType::EASE_OUT_BACK: return easeOutBack(t);
        case EasingType::EASE_IN_OUT_BACK: return easeInOutBack(t);
        case EasingType::EASE_IN_ELASTIC: return easeInElastic(t);
        case EasingType::EASE_OUT_ELASTIC: return easeOutElastic(t);
        case EasingType::EASE_IN_OUT_ELASTIC: return easeInOutElastic(t);
        default: return easeLinear(t);
    }
}

} // namespace CreativeMode
