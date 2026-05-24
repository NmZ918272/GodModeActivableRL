#pragma once

#include "bakkesmod/plugin/bakkesmod.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include <memory>
#include <vector>
#include <map>

namespace CreativeMode {

// Forward declarations
class FreecamController;
class TimelineManager;
class Animator;
class GizmoSystem;
class PhysicsController;
class RenderingSystem;
class ImGuiManager;
class ProjectSerializer;
class GhostReplay;
class ObjectManager;

/**
 * @class CreativeMode
 * @brief Gerenciador central do plugin Creative Mode
 * 
 * Coordena todos os subsistemas e gerencia o ciclo de vida do plugin.
 * Implementa padrão Singleton para acesso global.
 */
class CreativeMode {
public:
    static CreativeMode& getInstance();
    
    // Lifecycle
    void initialize(std::shared_ptr<GameWrapper> gameWrapper);
    void update(float deltaTime);
    void render();
    void shutdown();
    
    // State management
    bool isActive() const { return bIsActive; }
    void setActive(bool active);
    
    bool isInFreeplay() const;
    bool isGamePaused() const { return bIsGamePaused; }
    
    // Subsystem access
    FreecamController* getFreecamController() const { return freecamController.get(); }
    TimelineManager* getTimelineManager() const { return timelineManager.get(); }
    Animator* getAnimator() const { return animator.get(); }
    GizmoSystem* getGizmoSystem() const { return gizmoSystem.get(); }
    PhysicsController* getPhysicsController() const { return physicsController.get(); }
    RenderingSystem* getRenderingSystem() const { return renderingSystem.get(); }
    ImGuiManager* getImGuiManager() const { return imguiManager.get(); }
    ObjectManager* getObjectManager() const { return objectManager.get(); }
    
    // Game wrapper
    std::shared_ptr<GameWrapper> getGameWrapper() const { return gameWrapper; }
    
    // Pause control
    void pauseGame();
    void resumeGame();
    void setGameSpeed(float speed);
    float getGameSpeed() const { return gameSpeed; }
    
private:
    CreativeMode();
    ~CreativeMode();
    
    // Delete copy/move
    CreativeMode(const CreativeMode&) = delete;
    CreativeMode& operator=(const CreativeMode&) = delete;
    
    // Subsystems
    std::unique_ptr<FreecamController> freecamController;
    std::unique_ptr<TimelineManager> timelineManager;
    std::unique_ptr<Animator> animator;
    std::unique_ptr<GizmoSystem> gizmoSystem;
    std::unique_ptr<PhysicsController> physicsController;
    std::unique_ptr<RenderingSystem> renderingSystem;
    std::unique_ptr<ImGuiManager> imguiManager;
    std::unique_ptr<ProjectSerializer> projectSerializer;
    std::unique_ptr<GhostReplay> ghostReplay;
    std::unique_ptr<ObjectManager> objectManager;
    
    std::shared_ptr<GameWrapper> gameWrapper;
    
    bool bIsActive = false;
    bool bIsGamePaused = false;
    float gameSpeed = 1.0f;
    float accumulatedDeltaTime = 0.0f;
};

} // namespace CreativeMode
