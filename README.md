# ESP32 Sonar Radar — WebSonar System

A 12-week foundational robotics project aiming to build a real-time radar visualization system using ESP32, moving from basic embedded control to a complete Autonomous Mobile Robot (AMR) architecture.

* **Current Project Status:** 🟢 Phase 1 (Week 2) — Foundation & Connectivity
* **Target Architecture:** Two-tier Finite State Machine (FSM)

---

## 📊 Project Roadmap & Current Progress

### Phase 1: Foundation (Weeks 1–2) — [CURRENT PHASE]
* [x] **Week 1:** Environment setup, firmware flashing, and hardware "Hello World" (LED Blink).
* [ ] **Week 2:** Wi-Fi provisioning, Local Web Server initialization, and implementing **Structured Logging Protocol** via Serial Monitor.

### Phase 2: Hardware Integration (Weeks 3–6)
* [ ] **Week 3-5:** Ultrasonic sensor (HC-SR04) calibration and Servo MG90S sweep synchronization.
* [ ] **Week 6:** Chassis assembly, implementing the **Hardware Safety Layer** (Toggle Switch + 5A Fuse + LM2596), and deploying the *Stop & Scan* FSM algorithm.

### Phase 3: Software & Web UI (Weeks 7–10)
* [ ] WebSocket JSON telemetry streaming.
* [ ] HTML Canvas real-time radar rendering with fading trail effects.
* [ ] Fail-safe trigger execution upon connection timeout.

### Phase 4: Validation & Portfolio (Weeks 11–12)
* [ ] System stress-testing, power consumption audit, and final GitHub portfolio packaging.

---

## ⚙️ Implemented Logging Standards (Week 2)
To ensure system maintainability, all telemetry and debug data follow a strict structured tagging format:
* `[SYS]` : System boot, memory allocation, and hardware initialization logs.
* `[WIFI]`: Network scanning, connection states, and IP allocation telemetry.
* `[ERROR]`: Fail-safe triggers and critical runtime warnings.

---

## 📜 License
This project is licensed under the MIT License - see the LICENSE file for details.
