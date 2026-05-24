#include "Animator.h"

namespace CreativeMode {

Animator::Animator() = default;

Animator::~Animator() {
    shutdown();
}

void Animator::initialize() {
    clearCache();
}

void Animator::shutdown() {
    clearCache();
}

void Animator::update(float deltaTime) {
    // Lógica de atualização do animador
}

void Animator::applyAnimationToObject(uint32_t objectId, double time) {
    // Aplicar animação de um objeto específico
    // Obter track do timeline
    // Interpolar keyframes
    // Aplicar transformação ao objeto
}

void Animator::applyAllAnimations(double time) {
    if (bIsCacheValid && cachedTime == time) {
        return; // Usar cache
    }
    
    // Aplicar todas as animações
    
    bIsCacheValid = true;
    cachedTime = time;
}

void Animator::clearCache() {
    bIsCacheValid = false;
    cachedTime = -1.0;
}

void Animator::invalidateCache() {
    bIsCacheValid = false;
}

} // namespace CreativeMode
