# S32K Can Project 🚗

A project tool for automotive systems using CAN protocols comunicating with vehicles.

## 📌 Overview

This project provides a robust implementation of COM stack application over CAN for vehicle diagnostics (through OBD2). It enables functionalities such as ECU communication, and control of vehicle components.

## 🚀 Features

- ✅ Read and clear DTCs (Diagnostic Trouble Codes)
- ✅ ECU communication via UDS on CAN
- ✅ Real-time vehicle diagnostics
- ✅ Secure and optimized CAN communication

## 🫠 Technologies Used

- **Microcontroller**: S32K144
- **Protocol**: UDS (ISO 14229) over CAN
- **Framework**: AUTOSAR-based software architecture

## 👤 Authors

- [Your Name]
- [Team/Company Name]

## 📂 Project Structure

```
/diagnostic-project
│── /src               # Source code files
│── /docs              # Documentation
│── /configs           # Configuration files
│── /tests             # Test scripts and cases
│── README.md          # Project description
│── LICENSE            # License information
```

## ✨ Getting Started

### Prerequisites

- S32 Design Studio
- CAN Interface Hardware
- Vehicle with CAN-enabled ECU

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/your-repo/diagnostic-project.git
   ```
2. Open the project in S32 Design Studio.
3. Configure the CAN interface settings.
4. Compile and flash the firmware.

## 🔄 Usage

1. Connect the CAN interface to the vehicle.
2. Run the diagnostic tool.
3. Use the CLI/GUI to send UDS requests and receive responses.
4. Analyze data and clear fault codes.

## 🛠 Support

For any issues, please open an issue in the repository or contact [[your-email@example.com](mailto\:your-email@example.com)].

## 🌐 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

