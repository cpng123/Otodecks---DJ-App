## Otodecks – DJ App 🎧

Otodecks is a DJ application built with C++ and the JUCE framework, offering an intuitive interface and powerful tools for music mixing.
This project was developed for the Object-Oriented Programming module and demonstrates advanced audio programming, GUI customization, and event-driven design.

---

### 🎥 Demo Video

[Video](https://youtu.be/vC2NXYRrknU)

---

### ✨ Features

* **Dual Deck Players**: Load, play, pause, stop, and mix two tracks simultaneously .

* **Waveform Visualization**: Real-time waveform with draggable position slider for scrubbing .

* **Custom Controls**:

    * Volume sliders

    * Speed rotary sliders (0.0x – 3.0x)

    * Image-based play/pause buttons

* **Crossfader**: Smooth transitions between Deck A and Deck B .

* **Playlist Component**: Import tracks, manage metadata, search library, and load tracks to decks .

* **Disc DJ Component**: Interactive rotating disc for enhanced realism .

* **Sound Effects**: Pre-loaded effects (claps, sweeps, alarms, etc.) with volume and speed controls .

* **Custom GUI Design**: Gradient themes, stylized buttons, and tailored components for a professional look.

---

### 🖥️ Screens & Components

* **DeckGUI**: Core player interface with waveform, controls, and progress bar.

* **Playlist**: Track library with add, remove, and search features.

* **Crossfader**: Central slider to balance output between decks.

* **SoundEffect Panel**: Buttons to trigger and manipulate effects in real time.
 
---

### 📂 Project Structure
```
Otodecks-DJ-App/
│── Source/              # C++ source code (DeckGUI, MainComponent, Playlist, etc.)
│── Resources/           # Fonts, icons, and images
│── SoundEffect/         # Preloaded sound effects (mp3/wav)
│── DJ.jucer             # Projucer project file
│── README.md            # Project documentation
```

----

### 🚀 How to Build
**Requirements**
* **JUCE 6/7**

* **Visual Studio 2022** (Desktop C++ workload installed)

**Steps**

1. Clone this repository:
```
git clone https://github.com/<your-username>/Otodecks---DJ-App.git
cd Otodecks---DJ-App
```

2. Open `DJ.jucer` in **Projucer**.

    * Set your **JUCE modules path**.

    * Export to **Visual Studio 2022**.

3. Build the generated solution (`.sln`) in Visual Studio.

4. Run the application.

---

### 🎹 How to Use

**1. Import Tracks**

* Use the playlist panel to add songs (`.mp3` / `.wav`).

* Double-click or press **Load A** / **Load B** to send tracks to decks.

**2. Play & Mix**

* Use play/pause buttons on each deck.

* Adjust **volume** and **speed** with sliders.

* Crossfade smoothly between decks with the central slider.

**3. Waveform Navigation**

* Drag the waveform progress bar to jump through tracks.

**4. Sound Effects**

* Trigger effects (clap, sweep, heartbeat, etc.) from the **SoundEffect** panel.

* Adjust effect **volume** and **speed** in real time.

**5. Search**

* Use the playlist search bar to quickly find tracks.