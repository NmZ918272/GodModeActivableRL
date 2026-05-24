# BakkesMod Creative Mode Plugin

Um plugin avançado para BakkesMod que transforma o Rocket League Freeplay em um ambiente criativo completo com controle total sobre câmera, física, objetos e timeline.

## 🎯 Características Principais

### 🎬 Sistema de Timeline
- Editor de vídeo em tempo real
- Keyframes para múltiplos objetos
- Interpolação suave (Hermite/Bezier)
- Auto-keyframe inteligente
- Timeline visual na base da tela

### 🎥 Freecam Avançado
- Câmera livre ativada por P
- Movimentação WASD + Mouse
- Controle de velocidade
- Atravessar paredes
- Spline camera cinematográfica

### 🎮 Ferramentas de Controle
- **Gizmos 3D**: Translate, Rotate, Scale (estilo Blender/Unity)
- **Seleção**: Carro, Bola, Câmera, Boost Pads
- **Física em Tempo Real**: Gravidade, velocidade, força
- **Pausa Absoluta**: Congelar tempo
- **Slow Motion**: Controle de velocidade

### 🎨 Renderização Avançada
- Motion blur falso
- Camera shake
- Depth of field falso
- Trilhas visuais
- Exportação de frames

## 📁 Arquitetura

```
src/
├── CreativeMode/
│   ├── Core/
│   ├── Freecam/
│   ├── Timeline/
│   ├── Animator/
│   ├── Gizmo/
│   ├── Physics/
│   ├── Rendering/
│   ├── GUI/
│   ├── Serialization/
│   ├── Replay/
│   └── Plugin/
```

## 🚀 Status

Em desenvolvimento - Estrutura modular em C++17
