#include "RenderingSystem.h"
#include <sstream>
#include <iomanip>

namespace CreativeMode {

RenderingSystem::RenderingSystem() = default;

RenderingSystem::~RenderingSystem() {
    shutdown();
}

void RenderingSystem::initialize(std::shared_ptr<GameWrapper> gameWrapper_) {
    gameWrapper = gameWrapper_;
}

void RenderingSystem::shutdown() {
    stopFrameSequence();
    gameWrapper = nullptr;
}

void RenderingSystem::update(float deltaTime) {
    // Atualizar efeitos de renderização
    
    if (bCameraShake && shakeDuration > 0.0f) {
        shakeDuration -= deltaTime;
    }
}

void RenderingSystem::render() {
    // Renderizar efeitos pós-processamento
}

void RenderingSystem::setMotionBlur(bool enabled) {
    bMotionBlur = enabled;
}

void RenderingSystem::setMotionBlurAmount(float amount) {
    motionBlurAmount = glm::clamp(amount, 0.0f, 1.0f);
}

void RenderingSystem::setCameraShake(bool enabled) {
    bCameraShake = enabled;
}

void RenderingSystem::applyShake(float intensity, float duration) {
    bCameraShake = true;
    shakeIntensity = intensity;
    shakeDuration = duration;
}

void RenderingSystem::setDepthOfField(bool enabled) {
    bDepthOfField = enabled;
}

void RenderingSystem::setFocusDistance(float distance) {
    focusDistance = glm::max(0.0f, distance);
}

void RenderingSystem::setFocusRange(float range) {
    focusRange = glm::max(0.1f, range);
}

bool RenderingSystem::isTrailEnabled(uint32_t objectId) const {
    // Verificar se trilha está ativa para objeto
    return false;
}

void RenderingSystem::enableTrail(uint32_t objectId, bool enabled) {
    // Ativar/desativar trilha para objeto
}

void RenderingSystem::clearTrails() {
    // Limpar todas as trilhas
}

void RenderingSystem::exportFrame(const std::string& filename) {
    if (!gameWrapper) return;
    
    // Capturar frame atual e salvar como PNG/BMP
}

void RenderingSystem::startFrameSequence(const std::string& outputDir, int fps) {
    bRecordingFrames = true;
    frameCounter = 0;
}

void RenderingSystem::stopFrameSequence() {
    bRecordingFrames = false;
    frameCounter = 0;
}

} // namespace CreativeMode
