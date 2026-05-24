# Creative Mode Plugin - User Guide

## 🎬 Getting Started

### Installation

1. **Build the plugin** (see BUILD.md)
2. The DLL will be automatically placed in:
   ```
   %APPDATA%/BakkesMod/bakkesmod/plugins/GodModeActivableRL.dll
   ```
3. Restart BakkesMod if needed
4. Plugin appears in BakkesMod console

### Activation

```
creative_mode_toggle    # Ativa/desativa o Creative Mode
```

Or press **Tab** in-game to open the menu.

## 🎮 Controls

### Hotkeys

| Key | Action |
|-----|--------|
| `Tab` | Open/Close Main Menu |
| `P` | Toggle Freecam Mode |
| `K` | Toggle Auto-Keyframe |
| `Space` | Play/Pause Timeline |
| `Esc` | Deselect All |

### Freecam Controls (When enabled)

| Control | Action |
|---------|--------|
| `W` | Move Forward |
| `A` | Move Left |
| `S` | Move Backward |
| `D` | Move Right |
| `Space` | Move Up |
| `Ctrl` | Move Down |
| `Mouse` | Look Around |
| `Scroll` | Adjust Speed |

### Gizmo Controls

| Action | Control |
|--------|---------|
| Click + Drag | Transform Object |
| R | Rotate Mode |
| G | Translate Mode |
| S | Scale Mode |
| T | Toggle Local/World Space |
| Middle Click | Deselect |

## 🎯 Workflows

### Creating a Camera Animation

**Step 1: Activate Freecam**
- Press `P` to enable freecam mode
- Navigate to desired position
- Adjust FOV and camera angle

**Step 2: Create Keyframes**
- Press `K` to toggle auto-keyframe
- Modify camera position/rotation
- System automatically creates keyframes

**Step 3: Playback**
- Press `Space` to play timeline
- View recorded animation
- Adjust timing in timeline panel

**Step 4: Refine**
- Click keyframes in timeline
- Use gizmos to adjust position
- Fine-tune easing functions

### Manipulating Objects

**Step 1: Select Object**
- Open Objects panel
- Click on ball, car, or boost pad
- Object appears highlighted

**Step 2: Transform**
- Use gizmo (G/R/S keys)
- Or manually edit in physics panel
- Changes apply in real-time

**Step 3: Create Keyframe**
- Press `K` with auto-keyframe on
- Or right-click → "Create Keyframe"
- Adjust timing if needed

### Creating Slow Motion Shots

**Step 1: Open Physics Panel**
- Settings → Physics
- Adjust "Game Speed" slider

**Step 2: Record Timeline**
- Record your sequence at 0.5x speed
- This creates smooth slow-motion effect

**Step 3: Export**
- Timeline → Export Frames
- Choose output directory and FPS
- Render final video at normal speed

## 📊 Interface Overview

### Main Menu

```
File
├── New Project
├── Open Project
├── Save Project
├── Save As
└── Exit

Edit
├── Undo / Redo
└── Settings

View
├── Timeline Panel
├── Gizmo Panel
├── Physics Panel
└── Settings Panel
```

### Timeline Panel

- **Scrubber**: Drag to seek to specific time
- **Play/Pause/Stop**: Playback controls
- **FPS Display**: Current frames per second
- **Keyframe List**: All keyframes in current track
- **Add/Delete Keyframe**: Create or remove keyframes

### Gizmo Panel

- **Mode Selector**: Choose transform mode
  - Translate (Move)
  - Rotate (Spin)
  - Scale (Size)
- **Transform Fields**: Precise numeric input
- **Local/World Toggle**: Switch coordinate space
- **Gizmo Size**: Adjust visualization

### Physics Panel

- **Gravity**: Modify gravity (0-1000)
- **Game Speed**: Slow motion/fast forward (0-3x)
- **Ball Force**: Modify ball physics
- **Car Force**: Modify car physics
- **Freeze Ball/Car**: Lock in place
- **Spawn Ball**: Create additional balls
- **Clone Car**: Duplicate player car

### Settings Panel

- **Motion Blur**: Enable/Disable effect
- **Depth of Field**: Focus blur effect
- **Camera Shake**: Add vibration
- **FOV**: Camera field of view
- **Camera Speed**: Movement speed
- **Export**: Save frames/video

## 💾 Saving & Loading

### Save Project

```
File → Save Project (Ctrl+S)
```

Saves:
- Timeline data
- All keyframes
- Settings
- Physics modifications

Project file: `.creative` (JSON format)

### Load Project

```
File → Open Project (Ctrl+O)
```

Restores complete state including:
- Camera positions
- Object transforms
- Keyframe animations
- Custom settings

### Save Preset

```
Settings → Save Preset
```

Saves only settings (reusable for multiple projects)

## 🎥 Export & Rendering

### Export Frame Sequence

1. Open Settings Panel
2. Click "Export Frames"
3. Choose output directory
4. Select FPS and resolution
5. Click "Export"

Output: `frame_0000.png`, `frame_0001.png`, etc.

### Create Video

Using exported frames in your video editor:

**FFmpeg Example:**
```bash
ffmpeg -framerate 60 -i frame_%04d.png -c:v libx264 -pix_fmt yuv420p output.mp4
```

**DaVinci Resolve:**
1. File → Import Media
2. Select frame sequence
3. Add to timeline
4. Export as video

## ⚙️ Advanced Settings

### Easing Functions

Available for keyframe interpolation:
- Linear
- Ease In/Out Quad
- Ease In/Out Cubic
- Ease In/Out Back
- Ease In/Out Elastic

Select in Timeline Panel keyframe properties.

### Spline Camera

For smooth cinematic curves:

1. Freecam Panel → "Spline Mode"
2. Position camera at key points
3. Press `K` at each point
4. Timeline automatically interpolates curve

### Motion Paths

Record object movement:

1. Select object in Gizmo Panel
2. Enable "Record Trail"
3. Play timeline
4. Trail shows movement path

## 🐛 Troubleshooting

### Plugin Not Loading

**Error**: DLL not found
- **Solution**: Rebuild and check output path
- Check `%APPDATA%/BakkesMod/bakkesmod/plugins/`

**Error**: "Missing dependency"
- **Solution**: Ensure BakkesMod v0.75+ installed
- Verify Rocket League is up to date

### Freecam Not Working

**Issue**: Camera not moving
- **Solution**: Check if freecam is enabled (check console)
- Verify `P` key is not bound to other command
- Try reloading plugin: `rcon plugin refresh`

**Issue**: Camera jumps around
- **Solution**: Disable raw input in RL settings
- Reduce mouse sensitivity
- Update graphics drivers

### Timeline Issues

**Issue**: Keyframes not creating
- **Solution**: Enable auto-keyframe (press `K`)
- Check timeline is playing
- Ensure object is selected

**Issue**: Jerky animation playback
- **Solution**: Increase timeline FPS
- Check system performance (lower game FPS)
- Reduce number of objects

### Physics Problems

**Issue**: Objects fall through map
- **Solution**: Reset physics (Physics Panel)
- Re-enable collisions
- Teleport object back

**Issue**: Game crashes when spawning balls
- **Solution**: Reduce number of spawn attempts
- Restart plugin
- Check system RAM

## 💡 Tips & Tricks

### Pro Tips

1. **Use Presets**: Save frequently used settings
2. **Keyframe Markers**: Label important keyframes
3. **Multiple Takes**: Save project variations
4. **Auto-Save**: Enable in settings for backups
5. **Reference Footage**: Use ghost replay to check timing

### Performance Optimization

1. Disable motion blur if FPS drops
2. Reduce trail resolution
3. Use fewer keyframes (increase interpolation)
4. Export at lower resolution first
5. Close other BakkesMod mods

### Creative Techniques

1. **Depth of Field**: Focus on ball during plays
2. **Slow Motion**: Capture intense moments
3. **Dolly Zoom**: Combine camera movement + FOV
4. **Fly-Through**: Use spline camera for smooth paths
5. **Multi-Cam**: Combine multiple exports in editor

## 🎓 Tutorial Videos

Recommended learning path:

1. **Basics**: Freecam, Simple Animation (5 min)
2. **Keyframes**: Creating & Editing (10 min)
3. **Gizmos**: Object Manipulation (8 min)
4. **Physics**: Gravity & Speed Modifications (7 min)
5. **Export**: Creating Video Sequences (10 min)

## 📚 Additional Resources

- **Documentation**: See API.md and BUILD.md
- **Source Code**: Well-commented for reference
- **Examples**: Check EXAMPLES.md
- **FAQ**: See FAQ.md for common questions

## 🤝 Getting Help

### Support Channels

1. **GitHub Issues**: Report bugs and request features
2. **Discussion Forum**: Community help and tips
3. **Discord**: Real-time support and chat
4. **Email**: Direct contact for urgent issues

### Reporting Bugs

Include:
- System information (Windows version, GPU)
- BakkesMod version
- Rocket League season/version
- Steps to reproduce
- Screenshots/videos if applicable
- Error log from console

## 📝 Changelog

### Version 0.1-Alpha

Initial release featuring:
- Complete UI with ImGui
- Freecam system
- Timeline & keyframes with easing
- Gizmo system
- Physics controller
- Ghost replay
- Project serialization

---

**Questions?** Check GitHub Issues or contact the developer.

**Enjoy creating amazing Rocket League content!** 🚀
