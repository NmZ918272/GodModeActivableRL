#include "ImGuiManager.h"
#include "Panels/TimelinePanel.h"
#include "Panels/GizmoPanel.h"
#include "Panels/PhysicsPanel.h"
#include "Panels/SettingsPanel.h"
#include <imgui.h>

namespace CreativeMode {

ImGuiManager::ImGuiManager() = default;

ImGuiManager::~ImGuiManager() {
    shutdown();
}

void ImGuiManager::initialize() {
    timelinePanel = std::make_unique<TimelinePanel>();
    gizmoPanel = std::make_unique<GizmoPanel>();
    physicsPanel = std::make_unique<PhysicsPanel>();
    settingsPanel = std::make_unique<SettingsPanel>();
    
    applyUnrealEngineTheme();
}

void ImGuiManager::shutdown() {
    timelinePanel = nullptr;
    gizmoPanel = nullptr;
    physicsPanel = nullptr;
    settingsPanel = nullptr;
}

void ImGuiManager::update(float deltaTime) {
    // Atualizar painéis
}

void ImGuiManager::render() {
    if (!bMenuVisible) return;
    
    renderDockspace();
    renderMainMenu();
    renderPanels();
}

void ImGuiManager::setMenuVisible(bool visible) {
    bMenuVisible = visible;
}

void ImGuiManager::toggleMenu() {
    bMenuVisible = !bMenuVisible;
}

void ImGuiManager::applyUnrealEngineTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    
    // Dark gray background
    colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    
    // Blue accent
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    
    colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    
    colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    
    style.FrameRounding = 3.0f;
    style.WindowRounding = 3.0f;
}

void ImGuiManager::applyDarkTheme() {
    ImGui::StyleColorsDark();
}

void ImGuiManager::applyLightTheme() {
    ImGui::StyleColorsLight();
}

void ImGuiManager::renderMainMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project", "Ctrl+N")) {
                // Novo projeto
            }
            if (ImGui::MenuItem("Open Project", "Ctrl+O")) {
                // Abrir projeto
            }
            if (ImGui::MenuItem("Save Project", "Ctrl+S")) {
                // Salvar projeto
            }
            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S")) {
                // Salvar como
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                // Sair
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Settings")) {}
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Timeline", nullptr, &timelinePanel->isVisible);
            ImGui::MenuItem("Gizmo", nullptr, &gizmoPanel->isVisible);
            ImGui::MenuItem("Physics", nullptr, &physicsPanel->isVisible);
            ImGui::MenuItem("Settings", nullptr, &settingsPanel->isVisible);
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
}

void ImGuiManager::renderDockspace() {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
}

void ImGuiManager::renderPanels() {
    if (timelinePanel) timelinePanel->render();
    if (gizmoPanel) gizmoPanel->render();
    if (physicsPanel) physicsPanel->render();
    if (settingsPanel) settingsPanel->render();
}

} // namespace CreativeMode
